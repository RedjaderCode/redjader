
#ifndef _CONSOLE_H
#define _CONSOLE_H
#pragma once

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdint>
#include <windows.h>

#define GetInsertKey while(1){ if(GetAsyncKeyState(VK_INSERT & 0x2D)) break; }

enum cmd { open_file, close_file };

const char *_MacroModeString(cmd e);
const char *_GetCommandBuffer();

namespace console{
    inline void CreateCommandBuffer(const char *_command);
    inline void DestroyCommandBuffer(); // after interpreting the buffer, destroy it's memory
    inline void LogCommandBuffer();
};

struct CONSOLEBUFFER
{
private:
    uint32_t nScreenWidth;
    uint32_t nScreenHeight;
private:
    char *screen;
    HANDLE hConsole;

public:
    CONSOLEBUFFER() : 
        nScreenWidth(120), nScreenHeight(40),
        screen(nullptr), hConsole(0)
    {}

    inline void ConstructConsole();
    inline void FlushScreenBuffer(char c, DWORD dwBytesWritten);
    inline void WriteToScreenBuffer(COORD pPosition, DWORD dwBytesWritten);
    inline void DestroyScreenBuffer();
};

#endif