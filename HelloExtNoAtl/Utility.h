/******************************************************************
*
*  Project.....:  Windows View (Namespace Extension)
*
*  Application.:  WINVIEW.dll
*  Module......:  Utility.h
*  Description.:  Helper functions (header)
*
*  Compiler....:  MS Visual C++ 
*  Written by..:  D. Esposito
*
*  Environment.:  Windows 9x/NT
*
*******************************/


#ifndef UTILITY_H
#define UTILITY_H


#include <windows.h>
#include <shlobj.h>
#include <Regstr.h>

#ifdef _cplusplus
extern "C" {
#endif   //_cplusplus


//extern int  g_nColumn1;
//extern int  g_nColumn2;
//extern int  g_nColumn3;
//extern int  g_nColumn4;


typedef struct WNDINFO {
	CHAR pszInfo[1024];
	CHAR szCaption[100];
	HICON hIcon;
} WNDINFO, FAR*LPWNDINFO;

// registry utility functions
DWORD GetKeyName(HKEY, LPCTSTR, DWORD, LPTSTR, DWORD);
BOOL GetValueName(HKEY, LPCTSTR, DWORD, LPTSTR, DWORD);

// utility functions
BOOL SaveGlobalSettings( VOID );
BOOL GetGlobalSettings( VOID );
INT CALLBACK CompareItems( LPARAM, LPARAM, LPARAM );
VOID CreateImageLists( VOID );
VOID DestroyImageLists( VOID );
INT WideCharToLocal( LPTSTR, LPWSTR, DWORD );
INT LocalToWideChar( LPWSTR, LPTSTR, DWORD );
VOID ClipboardCopy( LPSTR );
VOID GetWindowProperties( HWND, LPWNDINFO );
HICON GetWindowIcon( HWND, BOOL );








#ifdef _cplusplus
}
#endif   //_cplusplus

#ifndef ARRAYSIZE
#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))
#endif

#endif   //UTILITY_H
