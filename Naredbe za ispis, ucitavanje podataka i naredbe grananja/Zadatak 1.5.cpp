#include <iostream>

int main() {
    double a, b, c, rjesenje1, rjesenje2, D;
    std::cin>>a;
    std::cin>>b;
    std::cin>>c;
    std::cout<<a<<b<<c;

    D = pow(b,2) - (4 * a * c);
    if (D >= 0) {
        rjesenje1 = (-b + sqrt(D)) / (2 * a);
        rjesenje2 = (-b - sqrt(D)) / (2 * a);
    }
    else {
        // Mrsko mi nastavljat
    }
    return 0;
}
