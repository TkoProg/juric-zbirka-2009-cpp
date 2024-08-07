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
    const char *ImeTime() const;
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

const char *Tim::ImeTime() const {
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

int main() {
    Tim sarajevo("FK Sarajevo");
    sarajevo.ObradiUtakmicu(3, 3);
    sarajevo.ObradiUtakmicu(5,2);
    sarajevo.ObradiUtakmicu(1,0);
    cout<<sarajevo.ImeTime();
    cout<<endl;
    cout<<sarajevo.GolRazlika();
    cout<<endl;
    cout<<sarajevo.BrojPoena();
    cout<<endl;
    sarajevo.IspisiPodatke();
}