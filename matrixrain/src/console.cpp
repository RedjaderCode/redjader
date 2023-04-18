
#include "console.hpp"

char * command = nullptr;

inline void console::CreateCommandBuffer(const char *_command)
{
    size_t size = 0;

    for(uint16_t i=0; _command[i]!='\0'; ++i) ++size;

    command = new char[ size ];
    memcpy(command, _command, size);
}

inline void console::DestroyCommandBuffer()
{
    delete[] command;
    command = nullptr;
}
/////////////////////////////////////////
// struct for the console construction //
/////////////////////////////////////////
inline void CONSOLEBUFFER::ConstructConsole()
{
    screen = new char[nScreenWidth * nScreenHeight];
    hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    SetConsoleActiveScreenBuffer(hConsole);
    DWORD dwBytesWritten = 0;
}

inline void CONSOLEBUFFER::FlushScreenBuffer(char c, DWORD dwBytesWritten)
{
    for(uint32_t iterator=0; iterator <= nScreenWidth * nScreenHeight - 1; ++iterator)
    {
        screen[iterator] = c;
    }
    screen[nScreenWidth * nScreenHeight - 1] = '\0';

    for(uint32_t y=0; y <= nScreenHeight; ++y) {
        for(uint32_t x=0; x <= nScreenWidth; ++x) {
            WriteConsoleOutputCharacter(hConsole, screen, nScreenWidth * nScreenHeight, {0, 0}, &dwBytesWritten);
        }
    }
}

inline uint16_t CONSOLEBUFFER::WriteStreamToScreenBuffer(COORD pPosition, DWORD dwBytesWritten)
{

    uint16_t length = 0;
    for(uint16_t iterator=pPosition.Y; iterator <= 10; ++iterator)
    {
        char sStreamerElement = L"abcdefghijklmnopqrstuvwxyz"[rand() % 25];
        pPosition.Y = iterator; ++length;
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