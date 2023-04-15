#ifndef _FILE_BUILD_H
#define _FILE_BUILD_H
#pragma once

struct file{
private:
    char *_name;
    FILE *_FR;
public:
    file() = default;
    
    virtual inline void SetName(const char *_n);
    virtual inline void BuildFile();
    virtual inline void Interpret();
};

#endif