
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <windows.h>

struct file{
    int iterator;
    std::string assetsPaths[100];
    const char * PTH;
    std::fstream rFile;
    std::fstream wFile;

    file(){std::cout << "file struct constructor needs const char*"; }
    file(const char * _assetsPaths) : PTH(_assetsPaths) {}

    std::filesystem::directory_iterator GetFileCount = std::filesystem::directory_iterator(PTH);

    void CreateImgIterator(){
        iterator = 0;
        for(auto& s : GetFileCount){
            std::cout << "\n\t" << (iterator+1) << "->> Loading: " << s.path().string();
            assetsPaths[iterator] = s.path().string();
            iterator+= s.is_regular_file()?: 1;
        }
    }

    inline void copy(){
        CreateImgIterator();
        std::cout << std::endl << std::endl;
        for(int i=0; i<=iterator; ++i){
            char * IntStr;
            itoa(i, IntStr, 10);

            rFile.open(assetsPaths[i].c_str(), std::ios::binary | std::ios::out | std::ios::in);
            if(!rFile.is_open()) std::cout << assetsPaths[i] << " ->> couldn't open to read" << std::endl;
            wFile.open((std::string)IntStr + ".png", std::ios::binary | std::ios::out | std::ios::in);
            if(!wFile.is_open()) std::cout << assetsPaths[i] << " ->> couldn't open to write" << std::endl;
            std::cout << assetsPaths[i] << " -> ";
/*
            i = GetAsyncKeyState(VK_NUMPAD1 & 0x61)?: 1;
            i = GetAsyncKeyState(VK_NUMPAD2 & 0x62)?: 2;
            i = GetAsyncKeyState(VK_NUMPAD3 & 0x63)?: 3;
            i = GetAsyncKeyState(VK_NUMPAD4 & 0x64)?: 4;
            i = GetAsyncKeyState(VK_NUMPAD5 & 0x65)?: 5;
            i = GetAsyncKeyState(VK_NUMPAD6 & 0x66)?: 6;
            i = GetAsyncKeyState(VK_NUMPAD7 & 0x67)?: 7;
            i = GetAsyncKeyState(VK_NUMPAD8 & 0x68)?: 8;
            i = GetAsyncKeyState(VK_NUMPAD9 & 0x69)?: 9;
*/
            int i1=0;
            int perc=0;
            uint8_t buffer;
            rFile.seekg(0, rFile.end);
            size_t SizeOfFile = rFile.tellg();
            std::cout << SizeOfFile << std::endl;
            while(i1 <= SizeOfFile){

                rFile.seekg(i1);
                rFile.read((char*)&buffer, sizeof(char));
                wFile.seekp(i1);
                wFile.write((char*)&buffer, sizeof(char));

                if(i1%(SizeOfFile/100)==NULL){
                    std::cout << "->> Copying[" << perc << "%]" << std::endl;
                    ++perc;
                }
                ++i1;
            }
            std::cout << std::endl;
            //i = GetAsyncKeyState(VK_ESCAPE & 0x1B)? iterator: i;
        }
    }
};

int main(int s, char * z[]){
    const char * pth = "copyer";
    file FILE(pth);
    FILE.copy();
    std::cin.get();
    return 0;
}
