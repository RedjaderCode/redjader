
#include "file_build.h"

inline void build::SetFileName(const char *_filename){
    filename = _filename!=this->filename ? (const char*&&)_filename : filename;
}

inline void build::BuildFile(){
    fopen_s(&FW, this->filename, "wb");
    if(!FW) printf("Couldn't open file: %s", this->filename);
    else printf("file built");
}