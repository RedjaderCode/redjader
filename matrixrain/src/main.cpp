
#include "main.h"

int main(int ss, char * zz[]){

    bool running = true;

    DWORD dwBytesWritten = 0;

    COORD pPosition = {0, 0};

    CONSOLEBUFFER consolebuffer;

    consolebuffer.ConstructConsole();
    consolebuffer.FlushScreenBuffer(L'|', dwBytesWritten);

    /*
    sStreamer s[ consolebuffer.nScreenWidth ];
    for(uint16_t i=0; i <= consolebuffer.nScreenWidth; ++i)
    {
        uint16_t speed = rand() % 8 + 4;
        size_t length  = rand() % 9 + 7;
        s[ i ] = {speed, length};
    }
    */

    uint16_t speed = rand() % 8 + 4;
    size_t length  = rand() % 9 + 7;
    sStreamer s = {speed, length};

    while(running)
    {
        //uint16_t streamer = rand() % consolebuffer.nScreenWidth;

        Sleep(consolebuffer.WriteStreamToScreenBuffer(
            pPosition, dwBytesWritten, 
            s/*[ streamer ]*/.speed, s/*[ streamer ]*/.length));
        pPosition.X = rand() % consolebuffer.nScreenWidth;
        
        if(GetAsyncKeyState(VK_ESCAPE & 0x1B)) running = false;
    }

    consolebuffer.DestroyScreenBuffer();

    return 0;
}