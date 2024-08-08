#include <iostream>

using namespace std;

enum Pravci {Sjever, Istok, Jug, Zapad};
const char* pravci[4] {"sjever", "istok", "jug", "zapad"};

class Robot {
    int x;
    int y;
    Pravci p;
public:
    Robot(int x, int y, Pravci p);
    void PomjeriSe(int korak);
    void Nalijevo();
    void Nadesno();
    int Pozicija_x() const;
    int Pozicija_y() const;
    Pravci Orijentacija() const;
    void Ispisi() const;
};

Robot::Robot(int x, int y, Pravci p) : x(x), y(y), p(p) {};

void Robot::PomjeriSe(int korak) {
    if (p == Istok) {
        x += korak;
    }
    else if (p == Zapad) {
        x -= korak;
    }
    else if (p == Sjever) {
        y += korak;
    }
    else if (p == Jug) {
        y -= korak;
    }
}

void Robot::Nalijevo() {
    if (p == Istok) {
        p = Sjever;
    }
    else if (p == Zapad) {
        p = Jug;
    }
    else if (p == Sjever) {
        p = Zapad;
    }
    else if (p == Jug) {
        p = Istok;
    }
}

void Robot::Nadesno() {
    if (p == Istok) {
        p = Jug;
    }
    else if (p == Zapad) {
        p = Sjever;
    }
    else if (p == Sjever) {
        p = Istok;
    }
    else if (p == Jug) {
        p = Zapad;
    }
}

int Robot::Pozicija_x() const {
    return x;
}

int Robot::Pozicija_y() const {
    return y;
}

Pravci Robot::Orijentacija() const {
    return p;
}

void Robot::Ispisi() const {

    cout<<"Robot se nalazi na poziciji ("<<x<<","<<y<<") i gleda na "<<pravci[p]<<"."<<endl;
}

int main() {
    Robot GigyCube(17,6,Istok);
    GigyCube.Ispisi();
    GigyCube.Nalijevo();
    GigyCube.PomjeriSe(5);
    GigyCube.Nalijevo();
    GigyCube.PomjeriSe(4);
    GigyCube.Ispisi();
}