
#include <iostream>

inline int order(int wheel, int body, int figure){
    int a[] = {wheel, body, figure};
    for(int i=0; i<3; ++i){
        for(int j=i+1; j<3; ++j){
            if(a[j]<a[i]){
                int T = a[i];
                a[i] = a[j];
                a[j] = T;
            }
        }
    }
    return (body >= 1 && figure >= 2 && wheel >= 4 ? a[0] : 0);
}

inline int cars(int wheel, int body, int figure){
    int min = order(wheel, body, figure);
    float x;
    if(min == NULL) std::cout << "  ->> insufficient materials: ";
    for(int i=0; i <= min; ++i){
        wheel -= 4;
        body -= 1;
        figure -= 2;
        x = wheel - 4 <= 0 || body - 1 <= 0 || figure - 2 <= 0 ? (wheel <= 0 ? i/4 : (figure <= 0 ? i/2 : i)) : 0;
    }
    return x;
}

int main(int s, char * z[]){
    int wheel;std::cout << "wheel: ";std::cin >> wheel;std::cout << std::endl;
    int body;std::cout << "body: ";std::cin >> body;std::cout << std::endl;
    int figure;std::cout << "figure: ";std::cin >> figure;std::cout << std::endl;
    std::cout << cars(wheel, body, figure) << std::endl;
    return 0;
}
