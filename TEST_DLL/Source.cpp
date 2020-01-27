
#include <windows.h>

extern "C" BOOL WINAPI DllMain (HINSTANCE hst, DWORD reason, LPVOID reserved)
{
    switch(reason) {
        case DLL_PROCESS_ATTACH: {
            OutputDebugString("DLL attach");
            return TRUE;
        }
        case DLL_PROCESS_DETACH: {
            OutputDebugString("DLL detach");
            return TRUE;
        }
    }
    return TRUE;
}

STDAPI DllCanUnloadNow()
{
    return S_OK;
}

STDAPI DllInstall(VOID)
{
    return S_OK;
}

extern "C" __declspec(dllexport) HRESULT DllRegisterServer(VOID)
{
    OutputDebugString("DLL regsvr");
    return S_OK;
}

extern "C" __declspec(dllexport) HRESULT DllUnregisterServer(VOID)
{   
    OutputDebugString("DLL unregsvr");
    return S_OK;
}
