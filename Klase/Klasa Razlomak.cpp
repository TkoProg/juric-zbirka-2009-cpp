#include <iostream>
#include <exception>
#include <numeric>

using namespace std;

class Razlomak {
    int brojnik;
    int nazivnik;

    void skratiRazlomak() {
        int nzd = gcd(brojnik,nazivnik);
        brojnik /= nzd;
        nazivnik /= nzd;
    }

public:
    Razlomak(int brojnik, int nazivnik);
    explicit Razlomak(int brojnik);
    Razlomak();

    int GetBrojnik() const {return brojnik;};
    int GetNazivnik() const {return nazivnik;};

    friend Razlomak operator +(Razlomak const &r1, Razlomak const &r2);
    friend Razlomak operator -(Razlomak const &r1, Razlomak const &r2);
    friend Razlomak operator *(Razlomak const &r1, Razlomak const &r2);
    friend Razlomak operator /(Razlomak const &r1, Razlomak const &r2);

    friend Razlomak operator +(Razlomak &r) { return r; };
    friend Razlomak operator -(Razlomak &r) { return {-r.brojnik, r.nazivnik}; };

    Razlomak &operator +=(Razlomak const &r);
    Razlomak &operator -=(Razlomak const &r);
    Razlomak &operator *=(Razlomak const &r);
    Razlomak &operator /=(Razlomak const &r);

    Razlomak &operator ++() { return *this += Razlomak(1, 1); };
    Razlomak operator ++(int) { return *this += Razlomak(1, 1); };
    Razlomak &operator --() { return *this -= Razlomak(1, 1); };
    Razlomak operator --(int) { return *this -= Razlomak(1, 1); };

    friend ostream &operator <<(ostream &out, const Razlomak &r);
    friend istream &operator >>(istream &in, Razlomak &r);

    friend bool operator <(const Razlomak &r1, const Razlomak &r2);
    friend bool operator >(const Razlomak &r1, const Razlomak &r2);
    friend bool operator <=(const Razlomak &r1, const Razlomak &r2);
    friend bool operator >=(const Razlomak &r1, const Razlomak &r2);
    friend bool operator ==(const Razlomak &r1, const Razlomak &r2);
    friend bool operator !=(const Razlomak &r1, const Razlomak &r2);

    explicit operator double() const { return double(brojnik) / nazivnik; };
};

Razlomak::Razlomak(int brojnik, int nazivnik) : brojnik(brojnik), nazivnik(nazivnik) {
    if (nazivnik == 0) {
        throw domain_error("Nazivnik ne smije biti nula!");
    }
    if ((nazivnik < 0 and brojnik > 0) or (nazivnik < 0 and brojnik < 0)) {
        this->nazivnik = -nazivnik;
        this->brojnik = -brojnik;
    }
    skratiRazlomak();
}

Razlomak::Razlomak(int brojnik) : brojnik(brojnik) {
    nazivnik = 1;
}

Razlomak::Razlomak() {
    brojnik = 0;
    nazivnik = 1;
}

Razlomak operator +(Razlomak const &r1, Razlomak const &r2) {
    int novi_brojnik, novi_nazivnik;
    novi_nazivnik = r1.nazivnik * r2.nazivnik;
    novi_brojnik = (r1.brojnik * r2.nazivnik) + (r2.brojnik * r1.nazivnik);
    return {novi_brojnik, novi_nazivnik};
}

Razlomak operator -(Razlomak const &r1, Razlomak const &r2) {
    int novi_brojnik, novi_nazivnik;
    novi_nazivnik = r1.nazivnik * r2.nazivnik;
    novi_brojnik = (r1.brojnik * r2.nazivnik) - (r2.brojnik * r1.nazivnik);
    return {novi_brojnik, novi_nazivnik};
}

Razlomak operator *(const Razlomak &r1, const Razlomak &r2) {
    int novi_brojnik, novi_nazivnik;
    novi_nazivnik = r1.nazivnik * r2.nazivnik;
    novi_brojnik = r1.brojnik * r2.brojnik;
    return {novi_brojnik, novi_nazivnik};
}

Razlomak operator /(const Razlomak &r1, const Razlomak &r2) {
    int novi_brojnik, novi_nazivnik;
    novi_nazivnik = r1.nazivnik * r2.brojnik;
    novi_brojnik = r1.brojnik * r2.nazivnik;
    return {novi_brojnik, novi_nazivnik};
}

Razlomak &Razlomak::operator +=(const Razlomak &r) {
    return *this = *this + r;
}

Razlomak &Razlomak::operator -=(const Razlomak &r) {
    return *this = *this - r;
}

Razlomak &Razlomak::operator *=(const Razlomak &r) {
    return *this = *this * r;
}

Razlomak &Razlomak::operator /=(const Razlomak &r) {
    return *this = *this / r;
}

ostream &operator <<(ostream &out, const Razlomak &r) {
    out << r.brojnik << "/" << r.nazivnik;
    return cout;
}

istream &operator >>(istream &in, Razlomak &r) {
    int b, n = 1;
    char c;
    in >> b;

    if (in.peek() == '/') {
        in >> c;
        in >> n;
    }

    if (n == 0) {
        throw domain_error("Nazivnik ne smije biti nula!");
    }

    r.brojnik = b;
    r.nazivnik = n;
    r.skratiRazlomak();
    return in;
}

bool operator <(const Razlomak &r1, const Razlomak &r2) {
    return (double(r1.brojnik) / r1.nazivnik) < (double(r2.brojnik) / r2.nazivnik);
}

bool operator >(const Razlomak &r1, const Razlomak &r2) {
    return (double(r1.brojnik) / r1.nazivnik) > (double(r2.brojnik) / r2.nazivnik);
}

bool operator <=(const Razlomak &r1, const Razlomak &r2) {
    return (double(r1.brojnik) / r1.nazivnik) <= (double(r2.brojnik) / r2.nazivnik);
}

bool operator >=(const Razlomak &r1, const Razlomak &r2) {
    return (double(r1.brojnik) / r1.nazivnik) >= (double(r2.brojnik) / r2.nazivnik);
}

bool operator ==(const Razlomak &r1, const Razlomak &r2) {
    return (r1.brojnik == r2.brojnik) and (r1.nazivnik == r2.nazivnik);
}

bool operator !=(const Razlomak &r1, const Razlomak &r2) {
    return (r1.nazivnik != r2.nazivnik) or (r1.brojnik != r2.brojnik);
}

int main() {
    try {
        Razlomak r(100,50);
        Razlomak r1(10,5);
        cout<<double(r1) * 5;
        cout<<r.operator double() + 2;
        int n;
        cin>>n;
        auto *razlomci = new Razlomak[n];
        for (int i = 0; i < 10; i++) {
            cout<<razlomci[i];
            cout<<endl;
        }
    }
    catch (const domain_error &e) {
        cout<<e.what()<<endl;
    }
}