#include <iostream>
#include <cstring>
using namespace std;
enum Tip {
    LINUX,UNIX,WINDOWS
};
class OperativenSistem {
private:
    char *name;
    float version;
    Tip type;
    float size; //vo GBi
    void copy(const OperativenSistem &os) {
        this->name=new char[strlen(os.name)+1];
        strcpy(this->name,os.name);
        this->version=os.version;
        this->type=os.type;
        this->size=os.size;
    }
public:
    float getVersion() {
        return version;
    }
    OperativenSistem(const char*name="", float version=0, Tip type=LINUX, float size=0) {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        this->version=version;
        this->type=type;
        this->size=size;
    }
    OperativenSistem(const OperativenSistem &os) {
        copy(os);
    }
    OperativenSistem &operator=(const OperativenSistem &os) {
        if (this!=&os) {
            delete [] name;
            copy(os);
        }
        return *this;
    }
    ~OperativenSistem() {
        delete [] name;
    }
    void pecati() {
        cout<<"Ime: "<<name<<" Verzija: "<<version<<" Tip: "<<type<<" Golemina:"<<size<<"GB"<<endl;
    }
    bool ednakviSe(const OperativenSistem &os) {
        return (strcmp(name,os.name)==0 && version==os.version && type==os.type && size==os.size);
    }
    int sporediVerzija(const OperativenSistem &os) {
        if (ednakviSe(os)) {
            return 0;
        }else if (os.version>version) {
            return -1;
        }else {
            return 1;
        }
    }
    bool istaFamilija(const OperativenSistem &os) {
        return (strcmp(name,os.name)==0 && type==os.type);
    }
};
class Repozitorium {
private:
    char name[20];
    OperativenSistem *os;
    int size;
public:
    Repozitorium(const char *name="") {
        strcpy(this->name,name);
        this->size=0;
        this->os = nullptr;
    }
    ~Repozitorium() {
        delete [] this->os;
    }
    void pecatiOperativniSistemi() {
        cout<<"Repozitorium: "<<name<<endl;
        for (int i=0;i<size;i++) {
            os[i].pecati();
        }
    }
    void izbrishi(const OperativenSistem &oss) {
        for (int i=0;i<size;i++) {
            if (os[i].ednakviSe(oss)) {
                OperativenSistem *new_os = new OperativenSistem[size-1];
                for (int j=0,k=0;k<size;k++) {
                    if (j!=i) {
                        new_os[k++]=os[j];
                    }
                }
                delete [] os;
                os=new_os;
                size--;
                break;
            }
        }
    }
    void dodadi(OperativenSistem &oss) {
        OperativenSistem *new_os = new OperativenSistem[size+1];
        for (int i=0;i<size;i++) {
            if (os[i].istaFamilija(oss)) {
                if (os[i].getVersion()<oss.getVersion()) {
                    os[i]=oss;
                    return;
                }
            }
            new_os[i]=os[i];
        }
        new_os[size]=oss;
        delete [] os;
        os=new_os;
        size++;
    }
};
int main() {
    char repoName[20];
    cin>>repoName;
    Repozitorium repozitorium=Repozitorium(repoName);
    int brojOperativniSistemi = 0;
    cin>>brojOperativniSistemi;
    char ime[20];
    float verzija;
    int tip;
    float golemina;
    for (int i = 0; i<brojOperativniSistemi; i++){
        cin>>ime;
        cin>>verzija;
        cin>>tip;
        cin>>golemina;
        OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
        repozitorium.dodadi(os);
    }

    repozitorium.pecatiOperativniSistemi();
    cin>>ime;
    cin>>verzija;
    cin>>tip;
    cin>>golemina;
    OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
    cout<<"=====Brishenje na operativen sistem====="<<endl;
    repozitorium.izbrishi(os);
    repozitorium.pecatiOperativniSistemi();
    return 0;
}