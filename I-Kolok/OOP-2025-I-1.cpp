//klasa Satellite i Country, Satellite imashe svoj char name[51], char
#include <iostream>
#include <cstring>
using namespace std;
enum Type {
    FAILED=0,PARTIAL,SUCCESS
};
class Satellite {
    char name[51];
    char country[51];
public:
    Satellite(const char *name="", const char *country="") {
        strcpy(this->name,name);
        strcpy(this->country,country);
    }
    void print() const {
        cout<<name<<" ("<<country<<")"; //ne endl oti mora vo Mission vo ista linija ushte neshto
    }
};
class Mission {
    Satellite s;
    char name[11];
    char date[11]; //vo format dd.mm.yyyy, ne e bitno sho ima tochki, bitno da nema prazno mesto
    int memory; //vo terabajti
    Type type; //0 ako e failed, 1 ako e partial, 2 ako e success
public:
    Mission(Satellite s={}, const char *name="", const char *date="", int memory=0, int(type)=0) { //pozhelno e tuka casting na type vo int prom.
        this->s=s;
        strcpy(this->name,name);
        strcpy(this->date,date);
        this->memory=memory;
        this->type=(Type)type; //mora desnovo da go vratime vo Type nazad, oti inache kje ostane int kako vo arg. posleden
    }
    void print() const {
        cout<<"Mission name: "<<name<<endl;
        cout<<"Satellite: ";
        s.print();
        cout<<" with memory: "<<memory<<"TB"<<endl;
        cout<<"Mission's date at: "<<date<<" Status: ";
        if (type==FAILED) {
            cout<<"Failed";
        }else if (type==PARTIAL) {
            cout<<"Partial";
        }else {
            cout<<"Success";
        }
        cout<<endl;
    }
};
int main() {
    int n;
    cin>>n;
    char name[11],date[11],namee[51],country[51];
    int memory;
    int type;
    Mission m[100];
    for (int i=0;i<n;i++) {
        cin>>name>>date; //imeto i datumot na misijata
        cin.ignore(); //za ako treba nov red za narednive 2
        cin.getline(namee,51);
        cin.getline(country,51); //edno do drugo se vnesuvaat, i + ima prazni mesta i vo namee i vo country, mora so getline
        cin>>memory>>type; //obichni integers
        Satellite s=Satellite(namee,country);
        m[i]=Mission(s,name,date,memory,type);
        m[i].print();
    }
    return 0;
}
//BARAN INPUT VO ZADACHATA PRIMER:
/*3 //broj na misii
Misija1 10.10.2010 //vo ist red ovie
Voyager 1 //ova i slednoto vo novi redovi oti mozhe da se dolgi (duri 50 karakteri)
United States of America //ova i prethodnoto vo nivniot input imaat prazni mesta, MORA cin.getline za dvete
100 //memorijata
1 //1 e partial, 2 e successful, 0 e failed
Misija2 10.10.2012
Voyager 5
Republic of Serbia
200
0
Misija3 05.05.2005
Voyager69
Republic of Macedonia
3000
2
//na kraj vo output, kako vnesuvate edna po edna kje gi printa (nebitno dali edna po edna, ili site naednash, istiot output e na kraj)