#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Ucesnik {
private:
    char *name;
    bool gender;
    int age;
    void copy(const Ucesnik &u) {
        name = new char[strlen(u.name) + 1];
        strcpy(name, u.name);
        gender = u.gender;
        age = u.age;
    }
public:
    int getAge() {
        return age;
    }
    Ucesnik(const char *name="", bool gender=false, int age=18) {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->gender = gender;
        this->age = age;
    }
    Ucesnik(const Ucesnik &u) {
        copy(u);
    }
    Ucesnik &operator=(const Ucesnik &u) {
        if (this != &u) {
            delete [] name;
            copy(u);
        }
        return *this;
    }
    ~Ucesnik() {
        if (name!=nullptr) {
            delete [] name;
        }
    }
    bool operator>(const Ucesnik &u) {
        return this->age>u.age;
    }
    friend ostream &operator<<(ostream &out, const Ucesnik &u) {
        out<<u.name<<endl;
        if (u.gender==0) {
            out<<"zhenski"<<endl;
        }else {
            out<<"mashki"<<endl;
        }
        out<<u.age<<endl;
        return out;
    }
};
class Maraton {
private:
    char location[100];
    Ucesnik *ucesnici;
    int size;
    void copy(const Maraton &m) {
        strcpy(location, m.location);
        size = m.size;
        this->ucesnici = new Ucesnik[m.size];
        for (int i=0;i<m.size;i++) {
            this->ucesnici[i]=m.ucesnici[i];
        }
    }
public:
    Maraton(const char *location="") {
        strcpy(this->location, location);
        this->ucesnici = nullptr;
        this->size=0;
    }
    Maraton(const Maraton &m) {
        copy(m);
    }
    Maraton &operator=(const Maraton &m) {
        if (this != &m) {
            delete [] this->ucesnici;
            this->ucesnici = new Ucesnik[m.size];
        }
        return *this;
    }
    ~Maraton() {
        if (this->ucesnici!=nullptr) {
            delete [] this->ucesnici;
        }
    }
    Maraton& operator+=(Ucesnik &u) {
        Ucesnik *tmp = new Ucesnik[this->size+1];
        for (int i=0;i<size;i++) {
            tmp[i]=this->ucesnici[i];
        }
        tmp[size]=u;
        delete [] this->ucesnici;
        this->ucesnici = tmp;
        this->size++;
        return *this;
    }
    float prosecnoVozrast() {
        float sum=0;
        for (int i=0;i<this->size;i++) {
            sum+=ucesnici[i].getAge();
        }
        return sum/(float)size;
    }
    void pecatiPomladi(Ucesnik &u) {
        for (int i=0;i<size;i++) {
            if (u>ucesnici[i]) {
                cout<<ucesnici[i];
            }
        }
    }
};

int main() {
    char ime[100];
    bool maski;
    int vozrast, n;
    cin >> n;
    char lokacija[100];
    cin >> lokacija;
    Maraton m(lokacija);
    Ucesnik **u = new Ucesnik*[n];
    for(int i = 0; i < n; ++i) {
        cin >> ime >> maski >> vozrast;
        u[i] = new Ucesnik(ime, maski, vozrast);
        m += *u[i];
    }
    m.pecatiPomladi(*u[n - 1]);
    cout << m.prosecnoVozrast() << endl;
    for(int i = 0; i < n; ++i) {
        delete u[i];
    }
    delete [] u;
    return 0;
}