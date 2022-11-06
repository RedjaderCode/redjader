
#include <cstring>
#include <iostream>

std::string DoubleCharacterSwap(std::string str, char c1, char c2){
    char * swapper = new char[str.length()];
    for(int i=0; i<str.length(); ++i){
        if(str[i]==c1) swapper[i]=c2;
        else if(str[i]==c2) swapper[i]=c1;
        else{
            swapper[i]=str[i];
        }
    }
    for(int i=0; i<str.length(); ++i){
        str[i]=swapper[i];
    }
    return str;
    delete[] swapper;
}

int main(int s, char * z[]){
    std::cout << DoubleCharacterSwap("joshua", 's', 'a');
    return 0;
}
