#include <iostream>
#include <iomanip>

using namespace std;

class Sat {
    int sati;
    int minute;
    int sekunde;
public:
    Sat();
    Sat(int sati, int minute, int sekunde);
    Sat(int sekunde);
    void Postavi(int sati, int minute, int sekunde);
    void PomjeriZa(int pomak);
    void Sljedeci();
    void Prethodni();
    int DajSate() const { return sati; };
    int DajMinute() const { return minute; };
    int DajSekunde() const { return sekunde; };
    void Ispisi() const;
};

Sat::Sat() {
    sati = 0;
    minute = 0;
    sekunde = 0;
}

Sat::Sat(int sati, int minute, int sekunde) : sati(sati), minute(minute), sekunde(sekunde) {
    if ((sati < 0) or (minute < 0) or (sekunde < 0)) {
        throw domain_error("Vrijeme ne moze biti negativno! (I ja bi se volio vratiti u proslost...)");
    }
    else if ((minute > 59) or (sekunde > 59)) {
        throw domain_error("Mjerna jedinica vremena ne moze biti veca od 60!");
    }
}

Sat::Sat(int sekunde) : sekunde(sekunde) {

}

void Sat::Postavi(int sati, int minute, int sekunde) {
    if ((sati < 0) or (minute < 0) or (sekunde < 0)) {
        throw domain_error("Vrijeme ne moze biti negativno! (I ja bi se volio vratiti u proslost...)");
    }
    else if ((minute > 59) or (sekunde > 59)) {
        throw domain_error("Mjerna jedinica vremena ne moze biti veca od 60!");
    }
    this->sati = sati;
    this->minute = minute;
    this->sekunde = sekunde;
}

void Sat::PomjeriZa(int pomak) {
    double p_sati, p_minute, p_sekunde, ukupno;
    p_sati = sati * 3600;
    p_minute = minute * 60;
    ukupno = sekunde + p_minute + p_sati;
    ukupno += pomak;
    p_sati = double(ukupno) / 3600;
    sati = floor(p_sati);
    p_minute = (p_sati - sati) * 60;
    minute = floor(p_minute);
    p_sekunde = (p_minute - minute) * 60;
    sekunde = round(p_sekunde);
}

void Sat::Sljedeci() {
    this->PomjeriZa(1);
}

void Sat::Prethodni() {
    this->PomjeriZa(-1);
}

void Sat::Ispisi() const {
    cout<<setfill('0')<<setw(2)<<sati;
    cout<<":";
    cout<<setfill('0')<<setw(2)<<minute;
    cout<<":";
    cout<<setfill('0')<<setw(2)<<sekunde<<endl;
}

int main() {
    try {
        Sat satnica;
        Sat sati(10, 16, 23);
        satnica.Postavi(60,0,0);
        satnica.Prethodni();
        satnica.Ispisi();
    }
    catch (const domain_error &e) {
        cout<<e.what()<<endl;
    }
}