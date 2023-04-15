
#include "main.hpp"

int main(int s, char * z[]){

    LogCommandBuffer();
    CreateCommandBuffer(_GetCommandBuffer());
    LogCommandBuffer();
    
    printf("goodbye!");

    return 0;
}