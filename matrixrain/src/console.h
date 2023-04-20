#ifndef _CONSOLE_H
#define _CONSOLE_H
#pragma once

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdint>
#include <windows.h>

#define GetInsertKey while(1){ if(GetAsyncKeyState(VK_INSERT & 0x2D)) break; }

struct CONSOLEBUFFER
{
public:
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
    inline uint16_t WriteStreamToScreenBuffer(COORD pPosition, DWORD dwBytesWritten, uint16_t speed, size_t size);
    inline void DestroyScreenBuffer();
};

#endif