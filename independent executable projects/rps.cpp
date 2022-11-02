
#include <string>
#include <iostream>
#include <windows.h>

enum strings{
    p1_win,
    p2_win,
    tie,
    winners
};

#define rock 0
#define paper 1
#define scissors 2

inline std::string rps(uint8_t p1, uint8_t p2){
    std::string p1_p2;
    int x = (int)p1 == paper && (int)p2 == rock || (int)p1 == rock
    && (int)p2 == scissors || (int)p1 == scissors && (int)p2 == paper //check to see if player one wins
    ? p1_win : (p1 == p2 ? tie : p2_win); // check if it's a tie
    p1_p2 = x == tie ? "players tied!" : (x == p1_win ? "player 1 wins!" : "player 2 wins!");
    return p1_p2;
}

int main(int s, char * z[]){
    bool running = true;
    const char * gamesymbolp1;
    const char * gamesymbolp2;
    std::cout << "Hold space to generate rock, paper, scissors!\n And escape to quit!" << std::endl;
    while(running){
    // winners has the same integers receding it as the macros
        if(GetAsyncKeyState(VK_SPACE & 0x20) && running){
            uint8_t p1 = rand() % winners;
            uint8_t p2 = rand() % winners;
            gamesymbolp1 = p1 != rock ? (p1 == paper ? "paper" : "scissors") : "rock";
            gamesymbolp2 = p2 != rock ? (p2 == paper ? "paper" : "scissors") : "rock";
            std::cout << "player 1 -> " << gamesymbolp1 << " -------- " 
                      << "player 2 -> " << gamesymbolp2 << " -------- " 
                      << rps(p1, p2) << std::endl;
        }
        if(GetAsyncKeyState(VK_ESCAPE & 0x1B) && running) running = false;
    }
    return 0;
}
