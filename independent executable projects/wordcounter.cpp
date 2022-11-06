/*
this program can count words in files to a fair accuracy.
Works best with just paragraphs, and the alike.

For this program, put any file(s) inside the FILES director in order for it to work.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#define UNICODE

struct file{
    const char * nFile;
    std::ifstream VIF;

    file() {std::cout << "Constructor needs a filename: (Ex: bin.bin)" << std::endl;}
    file(const char * _nFile) : nFile(_nFile) {VIF.open(nFile, std::ios::in);}
    ~file(){VIF.close();}

    inline int wordcounter(){
        VIF.seekg(0, VIF.end);
        size_t SizeOfFile        = VIF.tellg();
        char * buffer            = new char[SizeOfFile];
        int    WordCountIterator = 0;
        
        for(int i=0; i<=SizeOfFile; ++i){
            VIF.seekg(i);
            VIF.read ((char*)&(*(buffer+i)), sizeof(char));

            if(*(buffer+i)==' '&&*(buffer+i)!=*(buffer+(i+1))) ++WordCountIterator;
        }
        buffer[SizeOfFile] = '\0';
        if(*(buffer+(SizeOfFile))!=' ') ++WordCountIterator;
        
        std::cout << buffer << std::endl;
        std::cout << "\twords: ";
        delete[] buffer;
        return WordCountIterator - 1;
    }
};

auto GetFileCount = std::filesystem::directory_iterator("FILES");
int  iterator;
std::string assetsPaths[10];

void CreateImgIterator(){
    iterator = 0;
    for(auto& s : GetFileCount){
        std::cout << "\t" << iterator << " ->> Loading: " << s.path().string() << std::endl;
        assetsPaths[iterator] = s.path().string();
        iterator+= s.is_regular_file()?: 1;
    }
    std::cout << std::endl;
}

int main(int s, char * z[]){
    CreateImgIterator();

    int choice; std::cout << "Choose file: ";
    std::cin >> choice; std::cout << std::endl;

    file FILE(assetsPaths[choice].c_str());
    std::cout << FILE.wordcounter() << std::endl;
    return 0;
}