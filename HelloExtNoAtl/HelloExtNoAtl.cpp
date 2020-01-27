// HelloExtNoAtl.cpp: implementation of the CHelloExtNoAtl class.
//
//////////////////////////////////////////////////////////////////////
#include <windows.h>
#include <shlobj.h>

#include "HelloExtNoAtl.h"

#include "ClassFactory.h"
#include "Utility.h"

#include <olectl.h>

// data
HINSTANCE   g_hInst;
UINT        g_DllRefCount;

#pragma data_seg(".text")
#define INITGUID
#include <initguid.h>
#include <shlguid.h>
#include "Guid.h"
#pragma data_seg()

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    switch (ul_reason_for_call)
	{
		case DLL_PROCESS_ATTACH:
			g_hInst = (HINSTANCE)hModule;
		case DLL_THREAD_ATTACH:
		case DLL_THREAD_DETACH:
		case DLL_PROCESS_DETACH:
			break;
    }
    return TRUE;
}

/*---------------------------------------------------------------*/
// DllCanUnloadNow()
/*---------------------------------------------------------------*/
STDAPI DllCanUnloadNow( VOID )
{
	return (g_DllRefCount ? S_FALSE : S_OK);
}


/*---------------------------------------------------------------*/
// DllGetClassObject()
/*---------------------------------------------------------------*/
STDAPI DllGetClassObject( REFCLSID rclsid, REFIID riid, LPVOID *ppReturn )
{
	*ppReturn = NULL;

	// do we support the CLSID?
	if( !IsEqualCLSID(rclsid, CLSID_HelloExtNoAtl) )
	   return CLASS_E_CLASSNOTAVAILABLE;
   
	// call the factory
	CClassFactory *pClassFactory = new CClassFactory();
	if( pClassFactory==NULL )
	   return E_OUTOFMEMORY;
   
	// query interface for the a pointer
	HRESULT hResult = pClassFactory->QueryInterface(riid, ppReturn);
	pClassFactory->Release();
	return hResult;
}


/*---------------------------------------------------------------*/
// DllGetRegisterServer()
/*---------------------------------------------------------------*/

typedef struct{
   HKEY  hRootKey;
   LPTSTR lpszSubKey;
   LPTSTR lpszValueName;
   LPTSTR lpszData;
}REGSTRUCT, *LPREGSTRUCT;

STDAPI DllRegisterServer( VOID )
{
	INT i;
	HKEY hKey;
	LRESULT lResult;
	DWORD dwDisp;
	TCHAR szSubKey[MAX_PATH];
	TCHAR szCLSID[MAX_PATH];
	TCHAR szModule[MAX_PATH];
	LPWSTR pwsz;

	// get the CLSID in string form
	StringFromIID( CLSID_HelloExtNoAtl, &pwsz );

	if( pwsz )
	{
		WideCharToLocal( szCLSID, pwsz, ARRAYSIZE(szCLSID) );
        LPMALLOC pMalloc;
        CoGetMalloc(1, &pMalloc);
		if( pMalloc )
		{
	      pMalloc->Free(pwsz);
		  pMalloc->Release();
		}
    }

	// get this DLL's path and file name
	GetModuleFileName( g_hInst, szModule, ARRAYSIZE(szModule) );

	// CLSID entries
	REGSTRUCT ClsidEntries[] = {  
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s"),                  NULL,                   TEXT("HelloExtNoAtl"),
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s"),                  TEXT("InfoTip"),        TEXT("HelloExtNoAtl."),
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\InprocServer32"),  NULL,                   TEXT("%s"),
        HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\InprocServer32"),  TEXT("ThreadingModel"), TEXT("Apartment"),
        HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\DefaultIcon"),     NULL,                   TEXT("%s,0"),
        NULL,              NULL,                               NULL,                   NULL};

	for( i=0; ClsidEntries[i].hRootKey; i++ )
    {
		// create the sub key string.
		wsprintf( szSubKey, ClsidEntries[i].lpszSubKey, szCLSID );
        lResult = RegCreateKeyEx(  ClsidEntries[i].hRootKey,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp );
   
		if( lResult==NOERROR )
		{
			 TCHAR szData[MAX_PATH];
			 wsprintf(szData, ClsidEntries[i].lpszData, szModule);
			 lResult = RegSetValueEx( hKey,
                            ClsidEntries[i].lpszValueName,
                            0,
                            REG_SZ,
                            (LPBYTE)szData,
                            lstrlen(szData) + 1);
      
			 RegCloseKey(hKey);
		}
		else {
			return SELFREG_E_CLASS;
        }
    }

	// Context Menu
	lstrcpy( szSubKey, TEXT("txtfile\\ShellEx\\ContextMenuHandlers\\HelloExtNoAtl"));
	lResult = RegCreateKeyEx(HKEY_CLASSES_ROOT,
		szSubKey,
		0,
		NULL,
		REG_OPTION_NON_VOLATILE,
		KEY_WRITE,
		NULL,
		&hKey,
		&dwDisp);

	if( lResult==NOERROR )
	{
		TCHAR szData[MAX_PATH];
		lstrcpy(szData, szCLSID);
		lResult = RegSetValueEx( hKey,
			NULL,
			0,
			REG_SZ,
			(LPBYTE)szData,
			lstrlen(szData) + 1);

		RegCloseKey(hKey);
	}
	else {
		return SELFREG_E_CLASS;
    }

   // register the extension as approved by NT
   OSVERSIONINFO  osvi;
   osvi.dwOSVersionInfoSize = sizeof(osvi);
   GetVersionEx( &osvi );

   if( VER_PLATFORM_WIN32_NT == osvi.dwPlatformId )
   {
	   lstrcpy( szSubKey, TEXT("Software\\Microsoft\\Windows\\CurrentVersion\\Shell Extensions\\Approved"));
	   lResult = RegCreateKeyEx(  HKEY_LOCAL_MACHINE,
                              szSubKey,
                              0,
                              NULL,
                              REG_OPTION_NON_VOLATILE,
                              KEY_WRITE,
                              NULL,
                              &hKey,
                              &dwDisp);

       if( lResult==NOERROR )
       {
		   TCHAR szData[MAX_PATH];
	       lstrcpy(szData, TEXT("HelloExtNoAtl"));
           lResult = RegSetValueEx( hKey,
                                 szCLSID,
                                 0,
                                 REG_SZ,
                                 (LPBYTE)szData,
                                 lstrlen(szData) + 1);
      
	      RegCloseKey(hKey);
      }
	  else {
		  return SELFREG_E_CLASS;
       }
   }

   return S_OK;
}

/*---------------------------------------------------------------*/
// DllUnregisterServer()
/*---------------------------------------------------------------*/
STDAPI DllUnregisterServer( VOID )
{
	INT i;
	//HKEY hKey;
	LRESULT lResult;
	//DWORD dwDisp;
	TCHAR szSubKey[MAX_PATH];
	TCHAR szCLSID[MAX_PATH];
	TCHAR szModule[MAX_PATH];
	LPWSTR pwsz;

	// get the CLSID in string form
	StringFromIID( CLSID_HelloExtNoAtl, &pwsz );

	if( pwsz )
	{
		WideCharToLocal( szCLSID, pwsz, ARRAYSIZE(szCLSID) );
        LPMALLOC pMalloc;
        CoGetMalloc(1, &pMalloc);
		if( pMalloc )
		{
	      pMalloc->Free(pwsz);
		  pMalloc->Release();
		}
    }

	// get this DLL's path and file name
	GetModuleFileName( g_hInst, szModule, ARRAYSIZE(szModule) );

	// CLSID entries
	REGSTRUCT ClsidEntries[] = {  
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s"),                  NULL,                   TEXT("HelloExtNoAtl"),
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s"),                  TEXT("InfoTip"),        TEXT("HelloExtNoAtl."),
		HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\InprocServer32"),  NULL,                   TEXT("%s"),
        HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\InprocServer32"),  TEXT("ThreadingModel"), TEXT("Apartment"),
        HKEY_CLASSES_ROOT, TEXT("CLSID\\%s\\DefaultIcon"),     NULL,                   TEXT("%s,0"),
        NULL,              NULL,                               NULL,                   NULL};

	for( i=0; ClsidEntries[i].hRootKey; i++ )
    {
		// create the sub key string.
		wsprintf( szSubKey, ClsidEntries[i].lpszSubKey, szCLSID );
		lResult = RegDeleteKey(ClsidEntries[i].hRootKey, szSubKey);
    }


	// Context Menu
	lstrcpy( szSubKey, TEXT("txtfile\\ShellEx\\ContextMenuHandlers\\HelloExtNoAtl"));
	lResult = RegDeleteKey(HKEY_CLASSES_ROOT, szSubKey);


   // register the extension as approved by NT
   OSVERSIONINFO  osvi;
   osvi.dwOSVersionInfoSize = sizeof(osvi);
   GetVersionEx( &osvi );

   if( VER_PLATFORM_WIN32_NT == osvi.dwPlatformId )
   {
	   lResult = RegDeleteKey(HKEY_LOCAL_MACHINE, szSubKey);
   }

	return S_OK;
}