#include <iostream>

int main() {
    int h, min, s;
    int h1, min1, s1;

    std::cout<<"Unesite prvo vrijeme (h min s)"<<std::endl;
    std::cin>>h>>min>>s;
    std::cout<<"Unesite drugo vrijeme (h min s)"<<std::endl;
    std::cin>>h1>>min1>>s1;

    int total_prvi = h*3600 + min*60 + s;
    int total_drugi = h1*3600 + min1*60 + s1;
    int razlika = abs(total_prvi - total_drugi);

    double sati = double(razlika) / 3600;
    int fsati = int(sati);
    double minute = (double(sati) - fsati) * 60;
    int fminute = int(minute);
    double sekunde = double(minute - fminute) * 60;
    int fsekunde = ceil(sekunde);

    std::cout<<"Izmedju ova dva trenutka proteklo je "<<fsati<<"h "<<fminute<<"min "<<fsekunde<<"s.";
    return 0;
}
