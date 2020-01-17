
#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE app, DWORD reas, LPVOID res)
{
    switch (reas) {
    case DLL_PROCESS_ATTACH: {
            MessageBoxA(NULL, "DLL", "process attach", MB_OK);
            break;
        }
        case DLL_PROCESS_DETACH: {
            MessageBoxA(NULL, "DLL", "process detach", MB_OK);
            break;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            return TRUE;
    }
    return FALSE;
}
