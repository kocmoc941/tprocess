#include "tconsole.h"
#include "stdio.h"

int main()
{
    TConsole con;

    for(uint16_t i = 0; i <= 72; ++i) {
        con.setCursorPos(100, 0+i);
        con.printf("|");
        con.setScreenColor(COLOR_R, MODE_TEXT, 100, 0+i, 1);
    }

    con.setScreenColor(COLOR_WHITE, MODE_ALL_TEXT);
    con.setCursorPos(102, 10);
    con.printf("some txt");
    con.setScreenColor(COLOR_G, MODE_ALL_TEXT);
    con.setCursorPos(102, 30);
    con.printf("data 1");
    con.setCursorPos(102, 40);
    con.printf("data 1");
    con.setScreenColor(COLOR_R, MODE_TEXT, 102, 40, 6);
    con.setScreenColor(COLOR_WHITE, MODE_BACKGROUD, 102, 40, 6);
    con.setCursorPos(0, 0);

    return 0;
}
