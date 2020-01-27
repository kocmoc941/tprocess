/******************************************************************
*
*  Project.....:  Windows View (Namespace Extension)
*
*  Application.:  WINVIEW.dll
*  Module......:  Utility.cpp
*  Description.:  Helper functions (implementation)
*
*  Compiler....:  MS Visual C++ 
*  Written by..:  D. Esposito
*
*  Environment.:  Windows 9x/NT
*
*******************************/

#include <windows.h>
#include <shlobj.h>

/*---------------------------------------------------------------*/
//                        INCLUDE section
/*---------------------------------------------------------------*/
#include "Utility.h"
//#include "ShellFolder.h"
//#include "resource.h"
//#include "HwndProc.h"


extern HIMAGELIST g_himlSmall;

#define MAIN_KEY_STRING        (TEXT("Software\\ShellExtNoAtl"))
#define VALUE_STRING           (TEXT("Display Settings"))

#define INITIAL_COLUMN1_SIZE   100	// state
#define INITIAL_COLUMN2_SIZE   100	// class
#define INITIAL_COLUMN3_SIZE   60	// hwnd
#define INITIAL_COLUMN4_SIZE   100	// title



/*---------------------------------------------------------------*/
// Registry utility
/*---------------------------------------------------------------*/

// GetKeyName
DWORD GetKeyName( HKEY hKeyRoot, LPCTSTR pszSubKey, DWORD dwIndex, 
                  LPTSTR pszOut, DWORD dwSize )
{
	HKEY hKey;
	LONG lResult;
	FILETIME ft;

	if( !pszOut )
	   return 0;

	if( !pszSubKey )
	   pszSubKey = TEXT("");

	// open the specified key
	lResult = RegOpenKeyEx( hKeyRoot, pszSubKey, 0,
							KEY_ENUMERATE_SUB_KEYS, &hKey);

	if( lResult != ERROR_SUCCESS )
	   return 0;

	// get the specified subkey
	lResult = RegEnumKeyEx( hKey, dwIndex, pszOut, &dwSize,
							NULL, NULL, NULL, &ft );
	RegCloseKey(hKey);

	if( lResult == ERROR_SUCCESS )
	   return dwSize;

	return 0;
}


// GetValueName
BOOL GetValueName( HKEY hKeyRoot, LPCTSTR pszSubKey, DWORD dwIndex, 
    LPTSTR pszOut, DWORD dwSize )
{
	HKEY hKey;
	LONG lResult;
	DWORD dwType;

	if( !pszOut )
	   return 0;

	if( !pszSubKey )
	   pszSubKey = TEXT("");

	// open the specified key
	lResult = RegOpenKeyEx( hKeyRoot, pszSubKey, 0,
				KEY_QUERY_VALUE, &hKey );

	if( lResult != ERROR_SUCCESS )
	   return 0;

	// get the specified subkey
	lResult = RegEnumValue( hKey, dwIndex, pszOut, &dwSize, NULL,
         &dwType, NULL, NULL );

	RegCloseKey(hKey);

	return (lResult==ERROR_SUCCESS );
}



// SaveGlobalSettings
BOOL SaveGlobalSettings( VOID )
{
	HKEY hKey;
	LONG lResult;
	DWORD dwDisp;

	lResult = RegCreateKeyEx(  HKEY_CURRENT_USER,
                     MAIN_KEY_STRING, 
					 0,
                     NULL,
                     REG_OPTION_NON_VOLATILE, 
                     KEY_ALL_ACCESS,
                     NULL, 
                     &hKey,
                     &dwDisp );

	if(lResult != ERROR_SUCCESS)
		return FALSE;

	// create an array to put our data in
	DWORD dwArray[4];
	//dwArray[0] = g_nColumn1;
	//dwArray[1] = g_nColumn2;
	//dwArray[2] = g_nColumn3;
	//dwArray[3] = g_nColumn4;
	dwArray[4] = 0;

	lResult = RegSetValueEx( hKey, VALUE_STRING, 0, 
                  REG_BINARY, (LPBYTE) dwArray, sizeof(dwArray) );

	RegCloseKey( hKey );

	if( lResult != ERROR_SUCCESS )
		return FALSE;

	return TRUE;
}


// GetGlobalSettings
BOOL GetGlobalSettings( VOID )
{
	HKEY hKey;
	LONG lResult;

	// set up the default data
	//g_nColumn1 = INITIAL_COLUMN1_SIZE;
	//g_nColumn2 = INITIAL_COLUMN2_SIZE;
	//g_nColumn3 = INITIAL_COLUMN3_SIZE;
	//g_nColumn4 = INITIAL_COLUMN4_SIZE;

	lResult = RegOpenKeyEx( HKEY_CURRENT_USER,
                        MAIN_KEY_STRING,
                        0,
                        KEY_ALL_ACCESS,
                        &hKey);

	if( lResult != ERROR_SUCCESS )
		return FALSE;

	// create an array to put our data in
	DWORD dwArray[5];
	DWORD dwType;
	DWORD dwSize = sizeof(dwArray);

	// retrieve settings
	lResult = RegQueryValueEx( hKey,
                           VALUE_STRING,
                           NULL,
                           &dwType,
                           (LPBYTE)dwArray,
                           &dwSize);

	RegCloseKey( hKey );

	if( lResult != ERROR_SUCCESS )
		return FALSE;

	//g_nColumn1 = dwArray[0];
	//g_nColumn2 = dwArray[1];
	//g_nColumn3 = dwArray[2];
	//g_nColumn4 = dwArray[3];
	//g_bShowIDW = dwArray[4];

	return TRUE;
}



// CompareItems (sort listview by PIDL/HWND)
int CALLBACK CompareItems(LPARAM lParam1, LPARAM lParam2, LPARAM lpData)
{
   //CShellFolder* pFolder = reinterpret_cast<CShellFolder*>(lpData);
   //if(!pFolder)
   //   return 0;

   //return pFolder->CompareIDs(0, reinterpret_cast<LPITEMIDLIST>(lParam1),
   //                              reinterpret_cast<LPITEMIDLIST>(lParam2));
	return 0;
}


// create imagelists for the listview
VOID CreateImageLists( VOID )
{
	//if( g_himlSmall )
	//   ImageList_Destroy( g_himlSmall );

	//// set the small image list
	//g_himlSmall = ImageList_Create( 16, 16, ILC_COLORDDB|ILC_MASK, 4, 0 );
	//if( g_himlSmall )
	//{
	//	HICON hIcon;
	//    hIcon = (HICON) LoadImage( g_hInst, 
	//		MAKEINTRESOURCE(IDI_WINDOW), IMAGE_ICON, 
	//		16, 16, LR_DEFAULTCOLOR );
	//   ImageList_AddIcon( g_himlSmall, hIcon );

	//   hIcon = (HICON) LoadImage( g_hInst, 
	//	   MAKEINTRESOURCE(IDI_PARWND), IMAGE_ICON, 
	//	   16, 16, LR_DEFAULTCOLOR );
	//   ImageList_AddIcon( g_himlSmall, hIcon );

	//   hIcon = (HICON) LoadImage( g_hInst, 
	//	   MAKEINTRESOURCE(IDI_WND), IMAGE_ICON, 
	//	   16, 16, LR_DEFAULTCOLOR );
	//   ImageList_AddIcon( g_himlSmall, hIcon );
	//
	//}
}

// DestroyImageLists
VOID DestroyImageLists( VOID )
{
	//if( g_himlSmall )
	//	ImageList_Destroy( g_himlSmall );
}


// WideCharToLocal
INT WideCharToLocal( LPTSTR pLocal, LPWSTR pWide, DWORD dwChars )
{
	*pLocal = 0;
	WideCharToMultiByte( CP_ACP, 0, pWide, -1, pLocal, dwChars, 
		NULL, NULL );
	return lstrlen(pLocal);
}



// LocalToWideChar
INT LocalToWideChar( LPWSTR pWide, LPTSTR pLocal, DWORD dwChars )
{
	*pWide = 0;
	MultiByteToWideChar( CP_ACP, 0, pLocal, -1, pWide, dwChars ); 
	return lstrlenW( pWide );
}


// ClipboardCopy
VOID ClipboardCopy( LPSTR szText )
{
	OpenClipboard( NULL );

	HANDLE hmem = GlobalAlloc( GHND, MAX_PATH );
	LPSTR p = (LPSTR) GlobalLock( hmem ); 
	lstrcpy( p, (LPSTR) szText );
	GlobalUnlock( hmem );
	SetClipboardData( CF_TEXT, hmem );

	CloseClipboard();
}


// GetWindowProperties
VOID GetWindowProperties( HWND hwnd, LPWNDINFO lpwi )
{
	//ZeroMemory( lpwi, sizeof(WNDINFO) );

	//// get class name and title
	//CHAR szClass[120], szTitle[MAX_PATH];
	//GetClassName( hwnd, szClass, 120 );
	//GetWindowText( hwnd, szTitle, MAX_PATH );
	//if( !lstrlen(szTitle) )
	//	wsprintf( szTitle, "The window has no title" );
	//else
	//{
	//	CHAR temp[MAX_PATH];
	//	lstrcpy( temp, szTitle );
	//	wsprintf( szTitle, "Title is '%s'", temp );
	//}

	//// get the rectangle
	//RECT rc;
	//GetWindowRect( hwnd, &rc );

	//// get the ID
	//UINT uID;
	//uID = GetWindowLong( hwnd, GWL_ID );

	//// get process and thread
	//DWORD dwThread, dwProcess;
	//dwThread = GetWindowThreadProcessId( hwnd, &dwProcess );
	//CHAR szExeFile[MAX_PATH];
	//GetProgramFromHwnd( hwnd, szExeFile, MAX_PATH );


	//// format the return string
	//CHAR s1[100], s2[100], s3[300];
	//wsprintf( s1, "Handle is 0x%04X.\r\nID is 0x%04X.\r\nClass is '%s'.\r\n%s.\r\nParent Window is 0x%04X, Owner is 0x%04X.",
	//		hwnd, uID, szClass, szTitle, 
	//		GetParent(hwnd), GetWindow(hwnd, GW_OWNER) ); 
	//wsprintf( s2, "\r\nIt occupies an area that goes from %d,%d to %d,%d.\r\nWidth=%d, Height=%d.",
	//		rc.left, rc.top, rc.right, rc.bottom, 
	//		rc.right-rc.left, rc.bottom-rc.top );
	//wsprintf( s3, "\r\n\r\nCreated by: %s\r\nProcess ID is 0x%08X, Thread ID is 0x%08X.",
	//		szExeFile, dwProcess, dwThread );
	//lstrcat( s1, s2 );
	//lstrcat( s1, s3 );
	//lstrcpy( lpwi->pszInfo, s1 );

	//// set a possible caption
	//GetClassName( hwnd, szClass, 120 );
	//GetWindowText( hwnd, szTitle, MAX_PATH );
	//if( lstrlen(szTitle) )
	//	wsprintf( lpwi->szCaption, "Info: '%s' [%s]", szTitle, szClass );
	//else
	//	wsprintf( lpwi->szCaption, "Info: <No title> [%s]", szClass );

	//// get the icon (if any)
	//lpwi->hIcon = GetWindowIcon( hwnd, TRUE );
}


// GetWindowIcon
// Returns a copy of the large/small icon for the specified window, or a
//  standard icon if there's no icon for the window class it belongs to.
HICON GetWindowIcon(HWND hwnd, BOOL fBig)
{
   HICON hIcon = NULL;

   //// First search for the icon assigned to the window class. If no icon is
   ////  found, then I try to get the icon assigned to the specific window via
   ////  WM_SETICON. In case of further failure, a standard icon is returned.
   //if(fBig)
   //{
   //   // A large icon is required
   //   hIcon = reinterpret_cast<HICON>(GetClassLong(hwnd, GCLP_HICON));
   //   if(hIcon == NULL)
   //      hIcon = reinterpret_cast<HICON>(SendMessage(hwnd, WM_GETICON, ICON_BIG, 0));
   //}
   //else
   //{
   //   hIcon = reinterpret_cast<HICON>(GetClassLong(hwnd, GCLP_HICONSM));
   //   if(hIcon == NULL)
   //      hIcon = reinterpret_cast<HICON>(SendMessage(hwnd, WM_GETICON, ICON_SMALL, 0));
   //}

   //if(hIcon == NULL)
   //   hIcon = LoadIcon(g_hInst, MAKEINTRESOURCE(IDI_PARWND));

   // Return a copy of the icon
   return CopyIcon(hIcon);
}


/*  End of file: Utility.cpp  */

