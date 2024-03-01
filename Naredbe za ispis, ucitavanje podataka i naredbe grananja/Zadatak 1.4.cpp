#include <iostream>

int main() {
    double sati, prva, druga;
    std::cin>>sati;

    prva = 10 + (sati * 0.5);
    druga = sati * 0.8;

    if (prva > druga) std::cout<<"Druga firma je isplatnija!";
    else std::cout<<"Prva firma je isplatnija!";

    return 0;
}
