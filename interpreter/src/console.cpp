
#include "console.hpp"

char * command = nullptr;

const char *_GetCommandBuffer()
{
    
}

inline void CreateCommandBuffer(const char *_command)
{
    size_t size = 0;

    for(uint16_t i=0; _command[i]!='\0'; ++i) ++size;

    command = new char[size];
    memcpy(command, _command, size);
}

inline void LogCommandBuffer()
{
    if(command != nullptr)
    {
        for(uint16_t i=0; command[i]!='\0'; ++i)
            printf("%c", command[i]);
    }
    else printf(" -> Command buffer is empty\n");
}

inline void InterpretCommandBuffer()
{

    delete[] command;
    command = nullptr;
}