#include <iostream>

int main() {
    double a, b, c;
    std::cin>>a>>b>>c;
    bool trougao = false;

    if (pow(a, 2) == pow(b, 2) + pow(c, 2)) trougao = true;
    else if (pow(b, 2) == pow(a, 2) + pow(c, 2)) trougao = true;
    else if (pow(c, 2) == pow(b, 2) + pow(a, 2)) trougao = true;

    if (trougao) std::cout<<"Moze se oformiti trougao!";
    else std::cout<<"Ne moze se oformiti trougao!";
}
