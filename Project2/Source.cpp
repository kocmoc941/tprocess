
#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE app, DWORD reas, LPVOID res)
{
    switch (reas) {
    case DLL_PROCESS_ATTACH: {
        if(GetModuleHandleA("User32")) {
            MessageBoxA(NULL, "process attached", "DLL", MB_OK);
        }
            break;
    }
        case DLL_PROCESS_DETACH: {
            if (GetModuleHandleA("User32")) {
                MessageBoxA(NULL, "process detached", "DLL", MB_OK);
            }
            break;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            return TRUE;
    }
    return FALSE;
}
