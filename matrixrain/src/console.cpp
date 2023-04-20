
#include "console.h"

char * command = nullptr;

/////////////////////////////////////////
// struct for the console construction //
/////////////////////////////////////////

inline void CONSOLEBUFFER::ConstructConsole()
{
    screen = new char[nScreenWidth * nScreenHeight];
    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
}

inline void CONSOLEBUFFER::FlushScreenBuffer(char c, DWORD dwBytesWritten)
{
    for(uint32_t iterator=0; iterator <= nScreenWidth * nScreenHeight - 1; ++iterator)
    {
        screen[iterator] = c;
    }
    screen[ nScreenWidth * nScreenHeight ] = '\0';
    
    WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
}

inline uint16_t CONSOLEBUFFER::WriteStreamToScreenBuffer(COORD pPosition, DWORD dwBytesWritten, uint16_t speed, size_t length)
{
    for(uint16_t iterator=pPosition.Y; iterator <= length; ++iterator)
    {
        char sStreamerElement = L"abcdefghijklmnopqrstuvwxyz"[rand() % 25];
        pPosition.Y = iterator;
        WriteConsoleOutputCharacter(hConsole, &sStreamerElement, sizeof(char), pPosition, &dwBytesWritten);
    }

    return length * 5;
}

inline void CONSOLEBUFFER::DestroyScreenBuffer()
{
    nScreenHeight = 0;
    nScreenWidth  = 0;
    hConsole      = 0;

    delete[] screen;
    screen = nullptr;
}