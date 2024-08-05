#include <iostream>
#include <algorithm>

using namespace std;

template<typename Tip>
class Skup {
    int broj_elemenata;
    int kapacitet_skupa;
    Tip *elementi_skupa;
public:
    explicit Skup(int kapacitet_skupa);
    ~Skup() { delete [] elementi_skupa; };
    Skup(const Skup<Tip> &skup);
    Skup<Tip> &operator =(const Skup<Tip> &skup);

    void dodajElement(const Tip &element);
    int brojElemenataSkupa() { return broj_elemenata; };
    bool provjeriElement(const Tip &element) const;

    bool operator !() const;

    template<typename T>
    friend ostream &operator <<(ostream &out, const Skup<T> &skup);

    template<typename T>
    friend Skup<T> operator +(const Skup<T> &sk1, const Skup<T> &sk2);

    template<typename T>
    friend Skup<T> operator *(const Skup<T> &sk1, const Skup<T> &sk2);

    template<typename T>
    friend Skup<T> operator -(const Skup<T> &sk1, const Skup<T> &sk2);

    template<typename T>
    Skup<T> &operator +=(const Skup<T> &sk1);

    template<typename T>
    Skup<T> &operator *=(const Skup<T> &sk1);

    template<typename T>
    Skup<T> &operator -=(const Skup<T> &sk1);

    template<typename T>
    friend bool operator <=(const Skup<T> &sk1, const Skup<T> &sk2);

    template<typename T>
    friend bool operator >=(const Skup<T> &sk1, const Skup<T> &sk2);

    template<typename T>
    friend bool operator ==(const Skup<T> &sk1, const Skup<T> &sk2);

    template<typename T>
    friend bool operator !=(const Skup<T> &sk1, const Skup<T> &sk2);

    template<typename T>
    friend bool operator <(const Skup<T> &sk1, const Skup<T> &sk2);

    template<typename T>
    friend bool operator >(const Skup<T> &sk1, const Skup<T> &sk2);

};

template<typename Tip>
Skup<Tip>::Skup(int kapacitet_skupa) : kapacitet_skupa(kapacitet_skupa), broj_elemenata(0) {
    this->elementi_skupa = new Tip[kapacitet_skupa];
}

template<typename Tip>
Skup<Tip>::Skup(const Skup<Tip> &skup) : broj_elemenata(skup.broj_elemenata), kapacitet_skupa(skup.kapacitet_skupa) {
    this->elementi_skupa = new Tip[kapacitet_skupa];
    for(int i = 0; i < broj_elemenata; i++) {
        elementi_skupa[i] = skup.elementi_skupa[i];
    }
}

template<typename Tip>
Skup<Tip> &Skup<Tip>::operator =(const Skup<Tip> &skup) {
    if (this == &skup) {
        return *this;
    }

    delete [] elementi_skupa;

    kapacitet_skupa = skup.kapacitet_skupa;
    broj_elemenata = skup.broj_elemenata;
    elementi_skupa = new Tip[kapacitet_skupa];
    for (int i = 0; i < broj_elemenata; i++) {
        elementi_skupa[i] = skup.elementi_skupa[i];
    }

    return *this;
}

template<typename Tip>
void Skup<Tip>::dodajElement(const Tip &element) {
    for(int i = 0; i < broj_elemenata; i++) {
        if (elementi_skupa[i] == element) return;
    }
    if (broj_elemenata >= kapacitet_skupa) {
        throw domain_error("Prekoracio si dozvoljen broj elemenata skupa!");
    }
    elementi_skupa[broj_elemenata++] = element;
}

template<typename Tip>
bool Skup<Tip>::provjeriElement(const Tip &element) const {
    for (int i = 0; i < broj_elemenata; i++) {
        if (element == elementi_skupa[i]) return true;
    }
    return false;
}

template<typename Tip>
bool Skup<Tip>::operator !() const {
    if (broj_elemenata == 0) return true;
    return false;
}

template<typename Tip>
ostream &operator <<(ostream &out, const Skup<Tip> &skup) {
    sort(skup.elementi_skupa, skup.elementi_skupa+skup.broj_elemenata);
    out<<"{";
    for (int i = 0; i < skup.broj_elemenata; i++) {
        if (i == skup.broj_elemenata - 1) {
            out << skup.elementi_skupa[i];
        }
        else
            out << skup.elementi_skupa[i]<< ", ";
    }
    out<<"}";
    return out;
}

template<typename Tip>
Skup<Tip> operator +(const Skup<Tip> &sk1, const Skup<Tip> &sk2) {
    Skup<Tip> pomocni(sk1.kapacitet_skupa+sk2.kapacitet_skupa);
    for(int i = 0; i < sk1.broj_elemenata; i++) {
        pomocni.dodajElement(sk1.elementi_skupa[i]);
    }
    for(int i = 0; i < sk2.broj_elemenata; i++) {
        pomocni.dodajElement(sk2.elementi_skupa[i]);
    }
    return pomocni;
}

template<typename Tip>
Skup<Tip> operator *(const Skup<Tip> &sk1, const Skup<Tip> &sk2) {
    Skup<Tip> pomocni(max(sk1.kapacitet_skupa, sk2.kapacitet_skupa));
    for (int i = 0; i < sk1.broj_elemenata; i++) {
        if (sk2.provjeriElement(sk1.elementi_skupa[i])) {
            pomocni.dodajElement(sk1.elementi_skupa[i]);
        }
    }
    return pomocni;
}

template<typename Tip>
Skup<Tip> operator -(const Skup<Tip> &sk1, const Skup<Tip> &sk2) {
    Skup<Tip> pomocni(max(sk1.kapacitet_skupa, sk2.kapacitet_skupa));
    for (int i = 0; i < sk1.broj_elemenata; i++) {
        if (!sk2.provjeriElement(sk1.elementi_skupa[i])) {
            pomocni.dodajElement(sk1.elementi_skupa[i]);
        }
    }
    for (int i = 0; i < sk2.broj_elemenata; i++) {
        if (!sk1.provjeriElement(sk2.elementi_skupa[i])) {
            pomocni.dodajElement(sk2.elementi_skupa[i]);
        }
    }
    return pomocni;
}

template<typename Tip>
template<typename T>
Skup<T> &Skup<Tip>::operator +=(const Skup<T> &sk1) {
    return *this = *this + sk1;
}

template<typename Tip>
template<typename T>
Skup<T> &Skup<Tip>::operator *=(const Skup<T> &sk1) {
    return *this = *this * sk1;
}

template<typename Tip>
template<typename T>
Skup<T> &Skup<Tip>::operator -=(const Skup<T> &sk1) {
    return *this = *this - sk1;
}

template<typename T>
bool operator <=(const Skup<T> &sk1, const Skup<T> &sk2) {
    if (sk1.broj_elemenata > sk2.broj_elemenata) {
        return false;
    }
    for(int i = 0; i < sk1.broj_elemenata; i++) {
        if (!sk2.provjeriElement(sk1.elementi_skupa[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool operator >=(const Skup<T> &sk1, const Skup<T> &sk2) {
    if (sk1.broj_elemenata < sk2.broj_elemenata) {
        return false;
    }
    for(int i = 0; i < sk2.broj_elemenata; i++) {
        if (!sk1.provjeriElement(sk2.elementi_skupa[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool operator ==(const Skup<T> &sk1, const Skup<T> &sk2) {
    if ((sk1.broj_elemenata > sk2.broj_elemenata) or (sk1.broj_elemenata < sk2.broj_elemenata)) {
        return false;
    }
    for(int i = 0; i < sk1.broj_elemenata; i++) {
        if (!sk2.provjeriElement(sk1.elementi_skupa[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool operator !=(const Skup<T> &sk1, const Skup<T> &sk2) {
    if ((sk1.broj_elemenata > sk2.broj_elemenata) or (sk1.broj_elemenata < sk2.broj_elemenata)) {
        return true;
    }
    for(int i = 0; i < sk1.broj_elemenata; i++) {
        if (sk2.provjeriElement(sk1.elementi_skupa[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool operator <(const Skup<T> &sk1, const Skup<T> &sk2) {
    if (sk1.broj_elemenata >= sk2.broj_elemenata) {
        return false;
    }
    for(int i = 0; i < sk1.broj_elemenata; i++) {
        if (!sk2.provjeriElement(sk1.elementi_skupa[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool operator >(const Skup<T> &sk1, const Skup<T> &sk2) {
    if (sk1.broj_elemenata <= sk2.broj_elemenata) {
        return false;
    }
    for(int i = 0; i < sk2.broj_elemenata; i++) {
        if (!sk1.provjeriElement(sk2.elementi_skupa[i])) {
            return false;
        }
    }
    return true;
}

int main() {
    try {
        Skup<int> sk1(5);
        Skup<int> sk5(5);
        sk1.dodajElement(1);
        sk1.dodajElement(2);
        sk1.dodajElement(3);
        sk1.dodajElement(4);
        sk5.dodajElement(1);
        sk5.dodajElement(4);
        sk5.dodajElement(3);
        sk5.dodajElement(2);
        // sk5.dodajElement(7);
        cout<<(sk5 > sk1);
    }
    catch (domain_error &e){
        cout<<e.what()<<endl;
    }
}
