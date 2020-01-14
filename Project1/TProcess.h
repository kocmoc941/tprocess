#pragma once


#include <map>
#include <windows.h>

class TProcess {
	public:
		TProcess();
        TProcess(const TProcess&) = default;
        DWORD findProcessByName(CCHAR *name, BOOL case_insens = 0);
        std::string findProcessByID(DWORD ID);
        std::map<std::string, DWORD> enumProcess();
        BOOL setAdjustPrivileges(HANDLE token, LPCSTR priv_name, BOOL enablePriv);
    private:
};
