#include "tconsole.h"
#include "tprocess.h"
#include "stdio.h"

#include <map>
#include <vector>
#include <algorithm>
#include <functional>
#include <psapi.h>

#pragma comment(lib, "Psapi.lib")

int main()
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

    con.setScreenColor(COLOR_INTENSITY, MODE_ALL_TEXT);
    DWORD hacker = proc.findProcessByName("project", 1);
    con.printf("FOUNDED by name\r\n%u\r\n", hacker);
    con.printf("FOUNDED by id\r\n%s\r\n", proc.findProcessByID(0).c_str());
    con.setScreenColor(COLOR_G, MODE_ALL_TEXT);

    proc.setAdjustPrivileges(NULL, SE_DEBUG_NAME, TRUE);
    HANDLE po = OpenProcess(PROCESS_ALL_ACCESS, 0, hacker);
    MODULEINFO mi;
    HMODULE mods[1024];
    DWORD cb;
    EnumProcessModules(po, mods, sizeof(HMODULE), &cb);

    for (uint16_t i = 0; i < (cb / sizeof(HMODULE)); ++i) {
        char mname[MAX_PATH]{};
        GetModuleFileNameEx(po, mods[i], mname, MAX_PATH);
        if(*mname && mods[i]) {
            con.printf("handle:%08X info %s\n", mods[i], mname);
        }
    }

    CloseHandle(po);
    return 0;
}
