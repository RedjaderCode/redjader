
#ifndef _CONSOLE_H
#define _CONSOLE_H
#pragma once

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <cstdint>
#include <windows.h>

enum ConsoleCommands
{
    open_file
};

inline void CreateCommandBuffer(const char *_command);
inline void InterpretCommandBuffer(); // after interpreting the buffer, destroy it's memory
inline void LogCommandBuffer();

const char *_GetCommandBuffer();

#endif