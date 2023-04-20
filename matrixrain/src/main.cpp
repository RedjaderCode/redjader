
#include "main.h"

int main(int ss, char * zz[]){

    bool running = true;

    DWORD dwBytesWritten = 0;

    COORD pPosition = {0, 0};

    CONSOLEBUFFER consolebuffer;

    consolebuffer.ConstructConsole();
    consolebuffer.FlushScreenBuffer(L'|', dwBytesWritten);

    uint16_t speed = rand() % 8 + 4;
    size_t length  = rand() % 9 + 7;
    sStreamer s = {speed, length};

    while(running)
    {
        Sleep(consolebuffer.WriteStreamToScreenBuffer(pPosition, dwBytesWritten, s.speed, s.length));
        pPosition.X = rand() % consolebuffer.nScreenWidth;
        
        if(GetAsyncKeyState(VK_ESCAPE & 0x1B)) running = false;
    }

    consolebuffer.DestroyScreenBuffer();

    return 0;
}