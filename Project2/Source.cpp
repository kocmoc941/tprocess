
#include <Windows.h>

BOOL WINAPI DllMain(HINSTANCE app, DWORD reas, LPVOID res)
{
    switch (reas) {
        case DLL_PROCESS_ATTACH: {
            if(GetModuleHandleA("kernel32")) {
                OutputDebugStringA("DLL process attached");

            }
            return FALSE;
        }
        case DLL_PROCESS_DETACH: {
            if (GetModuleHandleA("kernel32")) {
                OutputDebugStringA("DLL process detached");
            }
            return TRUE;
        }
        case DLL_THREAD_ATTACH:
        case DLL_THREAD_DETACH:
            return TRUE;
    }
    return FALSE;
}
