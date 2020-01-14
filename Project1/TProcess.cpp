#include "tprocess.h"

#include <windows.h>
#include <tlhelp32.h>
#include <stdint.h>
#include <winbase.h>
#include <algorithm>

TProcess::TProcess()
{
}

BOOL setAdjustPrivileges(HANDLE token, LPCSTR priv_name, BOOL enablePriv)
{
    TOKEN_PRIVILEGES tp;
    LUID lu;
    HANDLE hToken;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        printf("OpenProcessToken error: %u\r\n", GetLastError());
        return FALSE;
    }
    if (!LookupPrivilegeValue(NULL, priv_name, &lu)) {
        printf("LookupPrivileges error: %u\r\n", GetLastError());
        return FALSE;
    }
    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = lu;
    if(enablePriv) {
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    } else {
        tp.Privileges[0].Attributes = 0;
    }
    if (!AdjustTokenPrivileges(token, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), (PTOKEN_PRIVILEGES)NULL, (PDWORD)NULL)) {
        printf("AdjustPrivileges error: %u\r\n", GetLastError());
        return FALSE;
    }
    if(GetLastError() == ERROR_NOT_ALL_ASSIGNED) {
        printf("The token does not have the specified privilege. \r\n");
        return FALSE;
    }
    return TRUE;
}

uint32_t TProcess::findProcessByName(const char *name, bool case_insens)
{
    uint32_t found_prc = 0;
    std::map<std::string, int> prc = enumProcess();
    for (auto it : prc) {
        std::string tmp1(it.first);
        std::string tmp2(name);
        if (case_insens) {
            std::transform(tmp1.begin(), tmp1.end(), tmp1.begin(),
                ::toupper);
            std::transform(tmp2.begin(), tmp2.end(), tmp2.begin(),
                ::toupper);
        }
        if (tmp1.find(tmp2) != std::string::npos) {
            found_prc = it.second;
            break;
        }
    }
    return found_prc;
}

std::string TProcess::findProcessByID(uint32_t ID)
{
    std::string found_prc;
    std::map<std::string, int> prc = enumProcess();
    for (auto it : prc) {
        if (it.second == ID) {
            found_prc = it.first;
            break;
        }
    }
    return found_prc;
}

std::map<std::string, int> TProcess::enumProcess()
{
    HANDLE hSnapshot;
    PROCESSENTRY32 Entry;
    std::map<std::string, int> processes;

    hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (hSnapshot == INVALID_HANDLE_VALUE) {
        return processes;
    }

    Entry.dwSize = sizeof(Entry);
    if (!Process32First(hSnapshot, &Entry)) {
        return processes;
    }

    do
    {
        if (Entry.dwSize > offsetof(PROCESSENTRY32, szExeFile))
        {
            processes[Entry.szExeFile] = Entry.th32ProcessID;
        }
        Entry.dwSize = sizeof(Entry);
    }
    while (Process32Next(hSnapshot, &Entry));

    CloseHandle(hSnapshot);
    return processes;
}
