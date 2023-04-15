#ifndef _MAIN_H
#define _MAIN_H

#include <stdint.h>
#include <stdio.h>
#include <iostream>

struct build{
private:
    const char *filename;
    FILE       *FW;
public:
    build() : filename(nullptr), FW(nullptr) {}
    ~build()
    {
        fclose(FW);
        filename = nullptr;
        FW       = nullptr;
    }

    inline void SetFileName(const char *_filename);
    inline void BuildFile();
};

#endif