
#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE app, DWORD reas, LPVOID res)
{
    switch (reas) {
    case DLL_PROCESS_ATTACH: {
            MessageBoxA(NULL, "process attached", "DLL", MB_OK);
            break;
        }
        case DLL_PROCESS_DETACH: {
            MessageBoxA(NULL, "process detached", "DLL", MB_OK);
            break;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            return TRUE;
    }
    return FALSE;
}
