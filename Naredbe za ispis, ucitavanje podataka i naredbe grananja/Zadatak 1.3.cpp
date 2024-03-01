#include <iostream>

int main() {
    double n;
    std::cin>>n;

    if (std::cin.good()) {
        if (int(n) == n && n > 0) {
            std::cout << "Uneseni podatak je prirodan broj.";
        } else if (int(n) == n && n <= 0) {
            std::cout << "Uneseni podatak je cijeli broj, ali nije prirodan.";
        } else if (int(n) != n) {
            std::cout << "Uneseni podatak je realan broj, ali nije cijeli.";
        }
    }
    else std::cout<<"Uneseni podatak nije broj.";

    return 0;
}
