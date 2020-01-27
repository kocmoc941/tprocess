// ShellExt.cpp: implementation of the CShellExt class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <tchar.h>
#include <shlobj.h>

#include "ShellExt.h"
#include "Guid.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShellExt::CShellExt()
{

}

CShellExt::~CShellExt()
{

}

STDMETHODIMP_(DWORD) CShellExt::Release(void)
{
	if(--m_ObjRefCount == 0)
	{
		delete this;
		return 0;
	}

	return m_ObjRefCount;
}

STDMETHODIMP_(DWORD) CShellExt::AddRef(void)
{
	return ++m_ObjRefCount;
}

STDMETHODIMP CShellExt::QueryInterface(REFIID riid, LPVOID *ppReturn )
{
	*ppReturn = NULL;

	if( IsEqualIID(riid, IID_IUnknown) )
		*ppReturn = this;
	else if( IsEqualIID(riid, IID_IClassFactory) )
		*ppReturn = (IClassFactory*)this;
	else if ( IsEqualIID(riid, IID_IShellExtInit))
		*ppReturn = (IShellExtInit*)this;
	else if ( IsEqualIID(riid, IID_IContextMenu))
		*ppReturn = (IContextMenu*)this;


	if( *ppReturn )
    {
        LPUNKNOWN pUnk = (LPUNKNOWN)(*ppReturn);
		pUnk->AddRef();
		return S_OK;
    }

    return E_NOINTERFACE;
}

STDMETHODIMP CShellExt::Initialize (
	LPCITEMIDLIST pidlFolder, LPDATAOBJECT pDataObj, HKEY hProgID )
{
	FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	HDROP     hDrop;

	// Look for CF_HDROP data in the data object.
	if ( FAILED( pDataObj->GetData ( &fmt, &stg ) ))
	{
		// Nope! Return an "invalid argument" error back to Explorer.
		return E_INVALIDARG;
	}

	// Get a pointer to the actual data.
	hDrop = (HDROP) GlobalLock ( stg.hGlobal );

	// Make sure it worked.
	if ( NULL == hDrop )
		return E_INVALIDARG;

	// Sanity check - make sure there is at least one filename.
	UINT uNumFiles = DragQueryFile ( hDrop, 0xFFFFFFFF, NULL, 0 );
	HRESULT hr = S_OK;

	if ( 0 == uNumFiles )
	{
		GlobalUnlock ( stg.hGlobal );
		ReleaseStgMedium ( &stg );
		return E_INVALIDARG;
	}

	// Get the name of the first file and store it in our member variable m_szFile.
	if ( 0 == DragQueryFile ( hDrop, 0, m_szFile, MAX_PATH ) )
		hr = E_INVALIDARG;

	GlobalUnlock ( stg.hGlobal );
	ReleaseStgMedium ( &stg );

	return hr;
}

STDMETHODIMP CShellExt::QueryContextMenu (
	HMENU hmenu, UINT uMenuIndex, UINT uidFirstCmd,
	UINT uidLastCmd, UINT uFlags )
{
	// If the flags include CMF_DEFAULTONLY then we shouldn't do anything.
	if ( uFlags & CMF_DEFAULTONLY )
		return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 0 );

	InsertMenu ( hmenu, uMenuIndex, MF_BYPOSITION, uidFirstCmd, _T("HelloExtNoAtl Test Item") );

	return MAKE_HRESULT ( SEVERITY_SUCCESS, FACILITY_NULL, 1 );
}

STDMETHODIMP CShellExt::GetCommandString (
	UINT_PTR idCmd, UINT uFlags, UINT* pwReserved, LPSTR pszName, UINT cchMax )
{
	//USES_CONVERSION;

	// Check idCmd, it must be 0 since we have only one menu item.
	if ( 0 != idCmd )
		return E_INVALIDARG;




	// If Explorer is asking for a help string, copy our string into the
	// supplied buffer.
	if ( uFlags & GCS_HELPTEXT )
	{
		LPCTSTR szText = _T("This is the simple shell extension's help");

		if ( uFlags & GCS_UNICODE )
		{	
			DWORD len;
			// Get the length (in wide chars) of the UNICODE buffer we'll need to
			// convert MyString to UNICODE.
			len = MultiByteToWideChar(CP_ACP, 0, szText, -1, 0, 0);
			
			BSTR  strptr;

			strptr = SysAllocStringLen(0, len);
			
			// Convert MyString to UNICODE in the buffer allocated by SysAllocStr
			MultiByteToWideChar(CP_ACP, 0, szText, -1, strptr, len);

			// We need to cast pszName to a Unicode string, and then use the
			// Unicode string copy API.
			lstrcpynW ( (LPWSTR) pszName, (LPWSTR)(strptr), cchMax );

			SysFreeString(strptr);
		}
		else
		{
			// Use the ANSI string copy API to return the help string.
			lstrcpynA ( pszName, (LPSTR)szText, cchMax );
		}

		return S_OK;
	}

	return E_INVALIDARG;
}

STDMETHODIMP CShellExt::InvokeCommand ( LPCMINVOKECOMMANDINFO pCmdInfo )
{
	// If lpVerb really points to a string, ignore this function call and bail out.
	if ( 0 != HIWORD( pCmdInfo->lpVerb ) )
		return E_INVALIDARG;

	// Get the command index - the only valid one is 0.
	switch ( LOWORD( pCmdInfo->lpVerb) )
	{
	case 0:
		{
			TCHAR szMsg [MAX_PATH + 32];

			wsprintf ( szMsg, _T("The selected file was:\n\n%s"), m_szFile );

			MessageBox ( pCmdInfo->hwnd, szMsg, _T("HelloShlExt"),
				MB_ICONINFORMATION );

			return S_OK;
		}
		break;

	default:
		return E_INVALIDARG;
		break;
	}
}