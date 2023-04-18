
#ifndef _MAIN_H
#define _MAIN_H
#pragma once

#include "library.cpp"

#include <cstdio>
#include <stdint.h>
#include <stdio.h>
#include <windows.h>

struct sStreamer
{
    uint16_t speed;
    size_t length;
    sStreamer() : speed(5), length(7) {}
    ~sStreamer()
    {
        speed  = 0;
        length = 0;
    }
};

#endif