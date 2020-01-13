#include <stdio.h>

#include "tconsole.h"

TConsole::TConsole()
{
    m_outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    m_inHandle = GetStdHandle(STD_INPUT_HANDLE);
}

void TConsole::printf(const char *fmt, ...)
{
    char buf[1024]{};
    va_list li;
    va_start(li, fmt);
    vsnprintf(buf, sizeof(buf), fmt, li);
    va_end(li);
    WriteConsole(m_outHandle, buf, strlen(buf), 0, 0);
}

const INPUT_RECORD *TConsole::readConsole(void)
{
    GetNumberOfConsoleInputEvents(m_inHandle, &m_numInputs);
    ReadConsoleInput(m_inHandle, &m_irInput, 1, &m_inputsRead);
    return &m_irInput;
}

void TConsole::setScreenColor(e_color color, e_mode mode, COORD pos, uint16_t len)
{
    setScreenColor(color, mode, pos.X, pos.Y, len);
}

void TConsole::setScreenColor(e_color color, e_mode mode, short x, short y, uint16_t len)
{
    uint32_t col = 0x00;
    switch (color) {
    case COLOR_R: {
        col = mode ? FOREGROUND_RED : BACKGROUND_RED;
        break;
    }
    case COLOR_G: {
        col = mode ? FOREGROUND_GREEN : BACKGROUND_GREEN;
        break;
    }
    case COLOR_B: {
        col = mode ? FOREGROUND_BLUE : BACKGROUND_BLUE;
        break;
    }
    case COLOR_WHITE: {
        col = mode ? (FOREGROUND_RED
            | FOREGROUND_GREEN
            | FOREGROUND_BLUE) : (BACKGROUND_RED
                | BACKGROUND_GREEN
                | BACKGROUND_BLUE);
        break;
    }
    case COLOR_INTENSITY: {
        col = mode ? FOREGROUND_INTENSITY : BACKGROUND_INTENSITY;
        break;
    }
    case COLOR_BLUE: {
        col = mode ? (FOREGROUND_GREEN | FOREGROUND_BLUE)
            : (BACKGROUND_GREEN | BACKGROUND_BLUE);
        break;
    }
    case COLOR_PUPRLE: {
        col = mode ? (FOREGROUND_RED
            | FOREGROUND_BLUE) : (BACKGROUND_RED
                | BACKGROUND_BLUE);
        break;
    }
    case COLOR_YELLOW: {
        col = mode ? (FOREGROUND_RED
            | FOREGROUND_GREEN) : (BACKGROUND_RED
                | BACKGROUND_GREEN);
        break;
    }
    }
    const COORD c = { x,y };
    DWORD dd;
    if (mode != MODE_ALL_TEXT) {
        FillConsoleOutputAttribute(m_outHandle, col, len, c, &dd);
    } else {
        SetConsoleTextAttribute(m_outHandle, col);
    }
}

void TConsole::setCursorPos(uint16_t x, uint16_t y)
{
    SetConsoleCursorPosition(m_outHandle, COORD{(short)x,(short)y});
}

void TConsole::setCodePage(uint32_t CP)
{
    SetConsoleCP(CP);
    SetConsoleOutputCP(CP);
}
