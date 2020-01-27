#include "tconsole.h"
#include "tprocess.h"
#include "stdio.h"

#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <psapi.h>
#include <sys/stat.h>

#pragma comment(lib, "Psapi.lib")

int main(int argc, char **argv, char **arge)
{
    TConsole con;

    TProcess proc;

    std::map<std::string, DWORD> all_prc = proc.enumProcess();

    std::map<std::string, DWORD>::const_iterator it = all_prc.begin();
    std::map<std::string, DWORD>::const_iterator it_end = all_prc.end();

    std::function<bool(std::pair<std::string, DWORD>,
        std::pair<std::string, DWORD>)> cmp = [](std::pair<std::string, DWORD> &a, std::pair<std::string, DWORD> &b)->bool {
        return a.second < b.second;
    };

    std::vector<std::pair<std::string, DWORD>> vec;

    for (auto el : all_prc) {
        vec.push_back(std::make_pair(el.first, el.second));
    }

    std::sort(vec.begin(), vec.end(), cmp);

    std::vector<std::pair<std::string, DWORD>>::const_iterator vit = vec.begin();
    std::vector<std::pair<std::string, DWORD>>::const_iterator vit_end = vec.end();

    for(vit; vit != vit_end; ++vit) {
        con.printf("%s %u\r\n", vit->first.c_str(), vit->second);
    }

    char *pName = "explorer";

    con.setScreenColor(COLOR_INTENSITY, MODE_ALL_TEXT);
    DWORD hacker = proc.findProcessByName(pName, 1);
    con.printf("FOUNDED %s by name\r\n%u\r\n", pName, hacker);
    con.printf("FOUNDED %s by id\r\n%s\r\n", pName, proc.findProcessByID(hacker).c_str());
    con.setScreenColor(COLOR_G, MODE_ALL_TEXT);

    proc.setAdjustPrivileges(NULL, SE_DEBUG_NAME, TRUE);
    HANDLE po = OpenProcess(PROCESS_ALL_ACCESS, 0, hacker);
    char *dll_path = "C:\\Users\\godd\\Documents\\Visual Studio 2015\\Projects\\Project1\\Debug\\Project2.dll";
    struct stat f;
    con.printf("DLL IS EXIST: %s\r\n", !stat(dll_path, &f) ? "TRUE" : "FALSE");

    DWORD dll_size = strlen(dll_path) + 1;
    LPVOID dll_addr = VirtualAllocEx(po, NULL, dll_size, MEM_COMMIT, PAGE_EXECUTE_READWRITE);

    if (!dll_addr) {
        con.printf("error alloc for dll path\r\n");
        return -1;
    }
    else {
        con.printf("VirtualAllocEx ok\r\n");
    }
    SIZE_T written = 0;
    BOOL writeOk = WriteProcessMemory(po, dll_addr, dll_path, dll_size, &written);
    if (!writeOk) {
        con.printf("error WriteProcessMemory for dll path\r\n");
        return -1;
    }
    else {
        con.printf("WriteProcessMemory ok written(%u)\r\n", written);
    }

    written = 0;
    LPTHREAD_START_ROUTINE addrLoadLibrary = (LPTHREAD_START_ROUTINE)GetProcAddress(LoadLibrary("kernel32"), "LoadLibraryA");
    if (!addrLoadLibrary) {
        con.printf("error addrLoadLibrary for inject dll\r\n");
        return -1;
    }
    else {
        con.printf("addrLoadLibrary ok %08X\r\n", addrLoadLibrary);
    }

    HANDLE thread_proc = CreateRemoteThread(po, NULL, 0, addrLoadLibrary, dll_addr, 0, &written);
    if (!thread_proc) {
        con.printf("error CreateRemoteThread for inject dll\r\n");
        con.printGetLastError("CreateRemoteThread");
        return -1;
    }
    else {
        con.printf("CreateRemoteThread ok\r\n");
    }
    con.printf("Inject ok\r\n");

    //MODULEINFO mi;
    HMODULE mods[1024];
    DWORD cb;
    EnumProcessModules(po, mods, sizeof(HMODULE), &cb);

    for (uint16_t i = 0; i < (cb / sizeof(HMODULE)); ++i) {
        char mname[MAX_PATH]{};
        GetModuleFileNameEx(po, mods[i], mname, MAX_PATH);
        if(*mname && mods[i]) {
            //con.printf("handle:%08X info %s\n", mods[i], mname);
        }
    }

    CloseHandle(po);
    return 0;
}
