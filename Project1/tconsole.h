#pragma once

#include <windows.h>
#include <stdint.h>

enum e_color {
    COLOR_WHITE,
    COLOR_R,
    COLOR_G,
    COLOR_B,
    COLOR_BLUE,
    COLOR_PUPRLE,
    COLOR_YELLOW,
    COLOR_INTENSITY,
};

enum e_mode {
    MODE_BACKGROUD,
    MODE_TEXT,
    MODE_ALL_TEXT,
};

class TConsole {
public:
    TConsole();
    TConsole(const TConsole&) = delete;

    void setScreenColor(e_color color, e_mode mode, short x = 0, short y = 0, uint16_t len = 0);
    void setScreenColor(e_color color, e_mode mode, COORD pos, uint16_t len = 0);
    const INPUT_RECORD *readConsole(void);
    void printf(const char *fmt, ...);
    void setCodePage(uint32_t CP);
    void setCursorPos(uint16_t x, uint16_t y);
    void printGetLastError(LPCSTR fName);

private:
    HANDLE m_outHandle = NULL;
    HANDLE m_inHandle = NULL;
    DWORD m_numInputs = 0;
    DWORD m_inputsRead = 0;
    INPUT_RECORD m_irInput;
};
