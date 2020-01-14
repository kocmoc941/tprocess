#include "tconsole.h"
#include "tprocess.h"
#include "stdio.h"

#include <map>
#include <vector>
#include <algorithm>
#include <functional>

int main()
{
    TConsole con;

    TProcess proc;

    std::map<std::string,int> all_prc = proc.enumProcess();

    std::map<std::string, int>::const_iterator it = all_prc.begin();
    std::map<std::string, int>::const_iterator it_end = all_prc.end();

    std::function<bool(std::pair<std::string, int>,
        std::pair<std::string, int>)> cmp = [](std::pair<std::string, int> &a, std::pair<std::string, int> &b)->bool {
        return a.second < b.second;
    };

    std::vector<std::pair<std::string, int>> vec;

    for (auto el : all_prc) {
        vec.push_back(std::make_pair(el.first, el.second));
    }

    std::sort(vec.begin(), vec.end(), cmp);

    std::vector<std::pair<std::string, int>>::const_iterator vit = vec.begin();
    std::vector<std::pair<std::string, int>>::const_iterator vit_end = vec.end();

    for(vit; vit != vit_end; ++vit) {
        con.printf("%s %u\r\n", vit->first.c_str(), vit->second);
    }

    con.setScreenColor(COLOR_INTENSITY, MODE_ALL_TEXT);
    con.printf("FOUNDED by name\r\n%u\r\n", proc.findProcessByName("syst", 1));
    con.printf("FOUNDED by id\r\n%s\r\n", proc.findProcessByID(0).c_str());
    con.setScreenColor(COLOR_G, MODE_ALL_TEXT);
    return 0;
}
