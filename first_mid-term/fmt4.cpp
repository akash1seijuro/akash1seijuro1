#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Patnik {
private:
    char name[100];
    int cls; //1 or 2
    bool bicycle;
public:
    char* getName() {
        return this->name;
    }
    int getCls() const{
        return this->cls;
    }
    bool getBicycle() const{
        return this->bicycle;
    }
    void setName(char *name) {
        strcpy(this->name, name);
    }
    void setCls(int cls) {
        this->cls = cls;
    }
    void setBicycle(bool bicycle) {
        this->bicycle = bicycle;
    }
    Patnik(char *name="", int cls=2, bool bicycle=false) {
        strcpy(this->name,name);
        this->cls=cls;
        this->bicycle=bicycle;
    }
    friend ostream &operator<<(ostream &out, const Patnik &p) {
        out<<p.name<<endl<<p.cls<<endl<<p.bicycle<<endl;
        return out;
    }
};
class Voz {
private:
    char final_destination[100];
    Patnik *patnici;
    int size;
    int allowed_bicycles;
    void copy(const Voz &v) {
        strcpy(final_destination, v.final_destination);
        this->patnici = new Patnik[v.size];
        for (int i=0;i<v.size;i++) {
            this->patnici[i]=v.patnici[i];
        }
        this->size=v.size;
        this->allowed_bicycles=v.allowed_bicycles;
    }
public:
    Voz(const char *final_destination="", int allowed_bicycles=0) {
        strcpy(this->final_destination,final_destination);
        this->allowed_bicycles = allowed_bicycles;
        this->size=0;
        this->patnici = nullptr;
    }
    Voz(const Voz &v) {
        copy(v);
    }
    Voz &operator=(const Voz &v) {
        if (this!=&v) {
            delete [] patnici;
            copy(v);
        }
        return *this;
    }
    ~Voz() {
        if (patnici!=nullptr) {
            delete [] patnici;
        }
    }
    Voz &operator+=(Patnik &p) {
        int allowed=allowed_bicycles;
        if (p.getBicycle() && allowed<=0) {
            return *this;
        }
        Patnik *new_patnici = new Patnik[this->size+1];
        for (int i=0;i<size;i++) {
            new_patnici[i]=patnici[i];
        }
        new_patnici[size]=p;
        delete [] patnici;
        patnici=new_patnici;
        size++;
        if (p.getBicycle()) {
            allowed--;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Voz &v) {
        out<<v.final_destination<<endl;
        for (int i=0;i<v.size;i++) {
            out<<v.patnici[i]<<endl;
        }
        return out;
    }
    void patniciNemaMesto() {
        int first_class_left_out=0,second_class_left_out=0,max_available=allowed_bicycles;
        int count_of_first_class=0;
        for (int i=0;i<size;i++) {
            if (patnici[i].getCls()==1) {
                count_of_first_class++;
            }
        }
        for (int i=0;i<size;i++) {
            if (patnici[i].getCls()==1) {
                if (patnici[i].getBicycle() && max_available>0) {
                    max_available--;
                }else if (patnici[i].getBicycle() && max_available<=0) {
                    first_class_left_out++;
                }
            }
        }
        for (int i=0;i<size;i++) {
            if (patnici[i].getCls()==2) {
                if (patnici[i].getBicycle() && max_available>0) {
                    max_available--;
                }else if (patnici[i].getBicycle() && max_available<=0) {
                    second_class_left_out++;
                }
            }
        }
        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<first_class_left_out<<endl;
        cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<second_class_left_out<<endl;
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