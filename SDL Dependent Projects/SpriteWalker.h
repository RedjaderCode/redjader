#ifndef SPRITEWALKER_H_
#define SPRITEWALKER_H_

#include <SDL.h>
#include <SDL_Image.h>
#include <stdio.h>
#include <chrono>
#include <windows.h>

class GetTexture{

    private:

    int IMG_Width;
    int IMG_Height;

    SDL_Texture * cTexture;

    public:

    class sGet_Time{
        private:

        std::chrono::time_point<std::chrono::high_resolution_clock> nFirst;
        std::chrono::time_point<std::chrono::high_resolution_clock> nLast;
        std::chrono::duration<float> dDuration;

        public:

        sGet_Time();
        ~sGet_Time();
    };


    GetTexture();
    ~GetTexture();

    void free();
    void LoadTexture(const char * PTH);
    void render(int x, int y, SDL_Rect * clip);
    void LOADIMG();

    int GetWidth();
    int GetHeight();
};

#endif
