#pragma once


#include <set>
#include <stdint.h>

class TProcess {
	public:
		TProcess();
        TProcess(const TProcess&) = default;
        uint32_t findProcessByName(const char *name);
        uint32_t findProcessByID(uint32_t ID);
        std::set<std::string, int> enumProcess();
    private:
};

