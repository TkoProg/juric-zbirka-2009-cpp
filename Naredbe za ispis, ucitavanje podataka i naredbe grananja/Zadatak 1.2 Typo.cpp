#include <iostream>

int main() {
    int brzina;
    const int morska_milja = 1852;
    std::cin>>brzina;
    std::cout<<(double(brzina) / morska_milja) * 3600;
}
