#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Pica {
private:
    char name[15];
    int price;
    char *sostojki;
    int offer; //namaluvanje na cena, brojkata e %
    void copy(const Pica &P) {
        strcpy(name, P.name);
        price = P.price;
        offer = P.offer;
        this->sostojki = new char[strlen(P.sostojki)+1];
        strcpy(this->sostojki, P.sostojki);
    }
public:
    int getPrice() const {
        return price;
    }
    int getOffer() const{
        return offer;
    }
    Pica(const char *name="", int price=0, const char *sostojki="", int offer=0) {
        strcpy(this->name, name);
        this->price = price;
        this->sostojki = new char[strlen(sostojki)+1];
        strcpy(this->sostojki, sostojki);
        this->offer = offer;
    }
    Pica(const Pica &p) {
        copy(p);
    }
    Pica &operator=(const Pica &p) {
        if (this!=&p) {
            delete [] sostojki;
            copy(p);
        }
        return *this;
    }
    ~Pica() {
        if (sostojki!=nullptr) {
            delete [] sostojki;
        }
    }
    void pecati() {
        cout<<name<<" - "<<sostojki<<", "<<price;
    }
    bool istiSe(Pica p) {
        return strcmp(this->sostojki, p.sostojki) == 0;
    }
};
class Picerija {
private:
    char name[15];
    Pica *pici;
    int size;
    void copy(const Picerija &P) {
        strcpy(name, P.name);
        size = P.size;
        pici = new Pica[size];
        for (int i=0;i<size;i++) {
            pici[i]=P.pici[i];
        }
    }
public:
    char *getIme(){
        return name;
    }
    void setIme(char *name) {
        strcpy(this->name, name);
    }
    Picerija(const char *name="") {
        strcpy(this->name, name);
        this->size=0;
        pici=nullptr;
    }
    Picerija(const Picerija &p) {
        copy(p);
    }
    Picerija &operator=(const Picerija &p) {
        if (this!=&p) {
            delete [] pici;
            copy(p);
        }
        return *this;
    }
    ~Picerija() {
        if (pici!=nullptr) {
            delete [] pici;
        }
    }
    Picerija& operator+=(Pica P) {
        Pica *new_pici = new Pica[size+1];
        for (int i=0;i<size;i++) {
            if (pici[i].istiSe(P)) {
                return *this;
            }
        }
        for (int i=0;i<size;i++) {
            new_pici[i]=pici[i];
        }
        new_pici[size]=P;
        delete [] pici;
        pici=new_pici;
        size++;
        return *this;
    }
    void piciNaPromocija() {
        for (int i=0;i<size;i++) {
            if (pici[i].getOffer()>0 && pici[i].getOffer()<100) {
                pici[i].pecati();
                cout<<" "<<pici[i].getPrice()*(1-((pici[i].getOffer())/100.0))<<endl;
            }
        }
    }
};

int main() {

    int n;
    char ime[15];
    cin >> ime;
    cin >> n;

    Picerija p1(ime);
    for (int i = 0; i < n; i++){
        char imp[100];
        cin.get();
        cin.getline(imp, 100);
        int cena;
        cin >> cena;
        char sostojki[100];
        cin.get();
        cin.getline(sostojki, 100);
        int popust;
        cin >> popust;
        Pica p(imp, cena, sostojki, popust);
        p1+=p;
    }

    Picerija p2 = p1;
    cin >> ime;
    p2.setIme(ime);
    char imp[100];
    cin.get();
    cin.getline(imp, 100);
    int cena;
    cin >> cena;
    char sostojki[100];
    cin.get();
    cin.getline(sostojki, 100);
    int popust;
    cin >> popust;
    Pica p(imp, cena, sostojki, popust);
    p2+=p;

    cout << p1.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p1.piciNaPromocija();

    cout << p2.getIme() << endl;
    cout << "Pici na promocija:" << endl;
    p2.piciNaPromocija();

    return 0;
}
