
#include "main.h"

int main(int ss, char * zz[]){

    bool running = true;

    DWORD dwBytesWritten = 0;

    COORD pPosition = {0, 0};

    CONSOLEBUFFER consolebuffer;

    uint32_t SCREEN_WIDTH = consolebuffer.nScreenWidth;

    consolebuffer.ConstructConsole();
    consolebuffer.FlushScreenBuffer(L'-', dwBytesWritten);

    sStreamer s[ consolebuffer.nScreenWidth ];
    for(uint16_t i=0; i <= consolebuffer.nScreenWidth; ++i)
    {
        s[ i ].InitializeAttributes();
    }

    while(running)
    {
        uint32_t streamer = rand() % consolebuffer.nScreenWidth;

        Sleep(consolebuffer.WriteStreamToScreenBuffer(
            pPosition, dwBytesWritten, 
            s[ streamer ].speed, s[ streamer ].length));
        pPosition.X = rand() % SCREEN_WIDTH;
        pPosition.Y += s[ streamer ].speed;
        
        if(GetAsyncKeyState(VK_ESCAPE & 0x1B)) running = false;
    }

    consolebuffer.DestroyScreenBuffer();

    return 0;
}

inline void sStreamer::InitializeAttributes()
{
    speed  = (uint16_t&&)rand() % 2 + 1;
    length = (size_t&&  )rand() % 9 + 7;
}