#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Patnik {
private:
    char name[100];
    int cls;
    bool bicycle;
public:
    int getCls() {
        return cls;
    }
    bool getBicycle() {
        return bicycle;
    }
    Patnik(const char *name="", int cls=2, bool bicycle=false) {
        strcpy(this->name, name);
        this->cls = cls;
        this->bicycle = bicycle;
    }
    friend ostream &operator<<(ostream &out, const Patnik &p) {
        out<<p.name<<endl<<p.cls<<endl<<p.bicycle<<endl;
        return out;
    }
};
class Voz {
private:
    char location[100];
    Patnik *patnici;
    int n;
    int allowed;
public:
    Voz(const char *location="", int allowed=0) {
        strcpy(this->location, location);
        this->allowed = allowed;
        this->n=0;
        this->patnici=nullptr;
    }
    Voz &operator+=(Patnik &p) {
        int current_allowed=allowed;
        for (int i=0;i<n;i++) {
            if (patnici[i].getBicycle()==true) {
                current_allowed++;
            }
        }
        if (p.getBicycle()==true && current_allowed<=0) {
            return *this;
        }
        Patnik *new_patnici=new Patnik[n+1];
        for (int i=0;i<n;i++) {
            new_patnici[i]=patnici[i];
        }
        if (p.getBicycle()==true) {
            current_allowed--;
        }
        new_patnici[n]=p;
        delete [] patnici;
        patnici=new_patnici;
        this->n++;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Voz &p) {
        out<<p.location<<endl;
        for (int i=0;i<p.n;i++) {
            out<<p.patnici[i]<<endl;
        }
        return out;
    }
    void patniciNemaMesto() {
        int current_allowed=allowed;
        int first_class_out=0,second_class_out=0;
        for (int i=0;i<n;i++) {
            if (patnici[i].getCls()==1 && patnici[i].getBicycle()==true) {
                if (current_allowed<=0) {
                    first_class_out++;
                }else {
                    current_allowed--;
                }
            }
        }
        for (int i=0;i<n;i++) {
            if (patnici[i].getCls()==2 && patnici[i].getBicycle()==true) {
                if (current_allowed<=0) {
                    second_class_out++;
                }else {
                    current_allowed--;
                }
            }
        }
        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<first_class_out<<endl;
        cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<second_class_out<<endl;
    }
};
int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
