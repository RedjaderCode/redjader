
#include "console.hpp"

char * command = nullptr;
const char *_RedJader = "MichelleIsAmazing()RedJader-> ";



const char *_GetCommandBuffer()
{
    return nullptr;
}

const char *_MacroModeString(cmd e)
{
    const char *_mode;
    switch(e)
    {
        case open_file:  _mode = "open";  break;
        case close_file: _mode = "close"; break;
    }

    return _mode;
}

inline void console::CreateCommandBuffer(const char *_command)
{
    size_t size = 0;

    for(uint16_t i=0; _command[i]!='\0'; ++i) ++size;

    command = new char[ size ];
    memcpy(command, _command, size);
}

inline void console::LogCommandBuffer()
{
    if(command != nullptr)
    {
        for(uint16_t i=0; command[i]!='\0'; ++i)
            printf("%c", command[i]);

        printf("\n");
    }
    else printf(" -> Command buffer is empty\n");
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

inline void CONSOLEBUFFER::WriteToScreenBuffer(COORD pPosition, DWORD dwBytesWritten)
{
    size_t _REDJADER_SIZE=0;

    for(uint16_t i=0; _RedJader[i]!='\0'; ++i)
    {
        ++_REDJADER_SIZE;
    }

    WriteConsoleOutputCharacter(hConsole, _RedJader, _REDJADER_SIZE, pPosition, &dwBytesWritten);
}

inline void CONSOLEBUFFER::DestroyScreenBuffer()
{
    nScreenHeight = 0;
    nScreenWidth  = 0;
    hConsole      = 0;

    delete[] screen;
    screen = nullptr;
}