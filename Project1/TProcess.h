#pragma once


#include <map>
#include <stdint.h>

class TProcess {
	public:
		TProcess();
        TProcess(const TProcess&) = default;
        uint32_t findProcessByName(const char *name, bool case_insens = 0);
        std::string findProcessByID(uint32_t ID);
        std::map<std::string, int> enumProcess();
    private:
};
