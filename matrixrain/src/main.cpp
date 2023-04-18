
#include "main.hpp"

int main(int ss, char * zz[]){

    bool running = true;

    DWORD dwBytesWritten = 0;

    COORD pPosition = {0, 0};

    CONSOLEBUFFER consolebuffer;
    sStreamer s;

    consolebuffer.ConstructConsole();
    consolebuffer.FlushScreenBuffer(L' ', dwBytesWritten);

    while(running)
    {
        Sleep(consolebuffer.WriteStreamToScreenBuffer(pPosition, dwBytesWritten));
        pPosition.X = rand() % consolebuffer.nScreenWidth;
        
        if(GetAsyncKeyState(VK_ESCAPE & 0x1B)) running = false;
    }

    consolebuffer.DestroyScreenBuffer();

    GetInsertKey;

    return 0;
}