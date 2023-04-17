
#include "main.hpp"

int main(int s, char * z[]){

    DWORD dwBytesWritten = 0;

    COORD pPosition = {0, 0};

    CONSOLEBUFFER consolebuffer;
    consolebuffer.ConstructConsole();

    consolebuffer.FlushScreenBuffer(L' ', dwBytesWritten);
    consolebuffer.WriteToScreenBuffer(pPosition, dwBytesWritten);

    console::CreateCommandBuffer(
        (const char*&&)_MacroModeString(open_file));
    console::DestroyCommandBuffer();

    console::CreateCommandBuffer(
        (const char*&&)_MacroModeString(close_file));
    console::DestroyCommandBuffer();

    GetInsertKey;

    consolebuffer.DestroyScreenBuffer();

    return 0;
}