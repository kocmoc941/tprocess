// ShellExt.h: interface for the CShellExt class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHELLEXT_H__38EFB68B_5591_485A_9E50_409E8CDE10E2__INCLUDED_)
#define AFX_SHELLEXT_H__38EFB68B_5591_485A_9E50_409E8CDE10E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShellExt : public IShellExtInit, IContextMenu
{
protected:
	DWORD m_ObjRefCount;
public:
	CShellExt();
	virtual ~CShellExt();

	// IUnknown methods
	STDMETHOD (QueryInterface) (REFIID riid, LPVOID * ppvObj);
	STDMETHOD_ (ULONG, AddRef) (void);
	STDMETHOD_ (ULONG, Release) (void);
	

    // IShellExtInit
    STDMETHODIMP Initialize(LPCITEMIDLIST, LPDATAOBJECT, HKEY);

    // IContextMenu
    STDMETHODIMP GetCommandString(UINT_PTR, UINT, UINT*, LPSTR, UINT);
    STDMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO);
    STDMETHODIMP QueryContextMenu(HMENU, UINT, UINT, UINT, UINT);
protected:
    TCHAR m_szFile [MAX_PATH];
};

#endif // !defined(AFX_SHELLEXT_H__38EFB68B_5591_485A_9E50_409E8CDE10E2__INCLUDED_)
