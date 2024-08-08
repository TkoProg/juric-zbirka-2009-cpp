#include <iostream>
#include <iomanip>

using namespace std;

class Tim {
    char ime[20]{};
    int broj_odigranih;
    int broj_pobjeda;
    int broj_nerjesenih;
    int broj_poraza;
    int broj_datih;
    int broj_primljenih;
    int broj_poena;
public:
    explicit Tim(const char ime[]);
    void ObradiUtakmicu(int broj_datih, int broj_primljenih);
    const char *ImeTima() const;
    int BrojPoena() const;
    int GolRazlika() const;
    void IspisiPodatke() const;
};

Tim::Tim(const char *ime) : broj_odigranih(0), broj_pobjeda(0), broj_nerjesenih(0), broj_poraza(0), broj_datih(0), broj_primljenih(0), broj_poena(0) {
    strcpy(this->ime, ime);
}

void Tim::ObradiUtakmicu(int broj_datih, int broj_primljenih) {
    broj_odigranih += 1;
    if (broj_datih > broj_primljenih) {
        broj_pobjeda += 1;
        broj_poena += 3;
    }
    else if (broj_datih == broj_primljenih) {
        broj_nerjesenih += 1;
        broj_poena += 1;
    }
    else {
        broj_poraza += 1;
    }
    this->broj_datih += broj_datih;
    this->broj_primljenih += broj_primljenih;
}

const char *Tim::ImeTima() const {
    return ime;
}

int Tim::BrojPoena() const {
    return broj_poena;
}

int Tim::GolRazlika() const {
    return broj_datih - broj_primljenih;
}

void Tim::IspisiPodatke() const {
    cout<<setw(20)<<left<<ime;
    cout<<setw(4)<<right<<broj_odigranih;
    cout<<setw(4)<<right<<broj_pobjeda;
    cout<<setw(4)<<right<<broj_nerjesenih;
    cout<<setw(4)<<right<<broj_poraza;
    cout<<setw(4)<<right<<broj_datih;
    cout<<setw(4)<<right<<broj_primljenih;
    cout<<setw(4)<<right<<broj_poena;
}

class Liga {
    int broj_timova;
    const int max_br_timova;
    Tim **timovi;

    static bool Kriterij(Tim *tim1, Tim *tim2) {
        if (tim1->BrojPoena() != tim2->BrojPoena())
            return tim1->BrojPoena() > tim2->BrojPoena();
        return tim1->GolRazlika() > tim2->GolRazlika();
    }

public:
    explicit Liga(int velicina_lige);
    ~Liga();
    void DodajNoviTim(const char ime_tima[]);
    void RegistrirajUtakmicu(const char tim1[], const char tim2[], int rezultat_1, int rezultat_2);
    void IspisiTabelu();
};

Liga::Liga(int velicina_lige) : max_br_timova(velicina_lige), broj_timova(0) {
    timovi = new Tim*[velicina_lige];
}

Liga::~Liga() {
    for (int i = 0; i <= broj_timova; i++) {
        delete [] timovi[i];
    }
    delete [] timovi;
}

void Liga::DodajNoviTim(const char *ime_tima) {
    if (broj_timova >= max_br_timova) {
        throw overflow_error("Liga je puna!");
    }
    timovi[broj_timova++] = new Tim(ime_tima);
}

void Liga::RegistrirajUtakmicu(const char *tim1, const char *tim2, int rezultat_1, int rezultat_2) {
    bool check1 = false, check2 = false;
    for(int i = 0; i < broj_timova; i++) {
        if (strcmp(timovi[i]->ImeTima(), tim1) == 0) {
            check1 = true;
        }
        if (strcmp(timovi[i]->ImeTima(), tim2) == 0) {
            check2 = true;
        }
    }

    if (!check1 or !check2) {
        throw overflow_error("Jedan ili oba tima se ne nalaze u ligi!");
    }

    for(int i = 0; i < broj_timova; i++) {
        if (strcmp(timovi[i]->ImeTima(), tim1) == 0) {
            timovi[i]->ObradiUtakmicu(rezultat_1, rezultat_2);
        }
        if (strcmp(timovi[i]->ImeTima(), tim2) == 0) {
            timovi[i]->ObradiUtakmicu(rezultat_2, rezultat_1);
        }
    }
}

void Liga::IspisiTabelu() {
    sort(timovi, timovi + broj_timova, Kriterij);
    for(int i = 0; i < broj_timova; i++) {
        timovi[i]->IspisiPodatke();
        cout<<endl;
    }
}

int main() {
    try {
        Liga sumska_liga(5);
        sumska_liga.DodajNoviTim("Celik");
        sumska_liga.DodajNoviTim("Jedinstvo");
        sumska_liga.DodajNoviTim("Zeljeznicar");
        sumska_liga.DodajNoviTim("Velez");
        sumska_liga.DodajNoviTim("Sarajevo");
        sumska_liga.RegistrirajUtakmicu("Celik", "Jedinstvo", 3, 2);
        sumska_liga.RegistrirajUtakmicu("Zeljeznicar", "Velez", 2, 2);
        sumska_liga.RegistrirajUtakmicu("Sarajevo", "Celik", 1, 4);
        sumska_liga.RegistrirajUtakmicu("Velez", "Sarajevo", 2, 1);
        sumska_liga.RegistrirajUtakmicu("Jedinstvo", "Sarajevo", 0, 2);
        sumska_liga.RegistrirajUtakmicu("Celik", "Zeljeznicar", 1, 1);
        sumska_liga.RegistrirajUtakmicu("Sarajevo", "Velez", 1, 1);
        sumska_liga.IspisiTabelu();
    }
    catch (const overflow_error &e) {
        cout<<e.what()<<endl;
    }
}