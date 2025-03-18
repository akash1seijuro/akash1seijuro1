#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Igrac {
    char korisnickoIme[15];
    int nivo;
    int poeni;
};
struct KompjuterskaIgra {
    char ime[20];
    Igrac lista[30];
    int n;
};
void najdobarIgrac(KompjuterskaIgra *ki, int n) {
    int index_ki_best=0,index_ki_i_best=0;
    int highest_points=0,highest_level=0;
    for (int i=0;i<n;i++) {
        for (int j=0;j<ki[i].n;j++) {
            if (ki[i].lista[j].poeni>highest_points) {
                highest_points=ki[i].lista[j].poeni;
                highest_level=ki[i].lista[j].nivo;
                index_ki_best=i;
                index_ki_i_best=j;
            }else if (ki[i].lista[j].poeni==highest_level) {
                if (ki[i].lista[j].nivo>highest_level) {
                    highest_level=ki[i].lista[j].nivo;
                    index_ki_best=i;
                    index_ki_i_best=j;
                }
            }
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<ki[index_ki_best].lista[index_ki_i_best].korisnickoIme<<" koj ja igra igrata "<<ki[index_ki_best].ime<<endl;
    //pechati korisnickoIme na najdobriot igrach (najvekje poeni) na igrata so najgolem n, ako se 2+ togash koj e povisoko nivo
}
int main() {
    int n;
    cin>>n; //broj na KompjuterskaIgra
    KompjuterskaIgra ki[n]; //kreirame nizata
    for (int i=0;i<n;i++) {
        cin>>ki[i].ime>>ki[i].n;
        for (int j=0;j<ki[i].n;j++) {
            cin>>ki[i].lista[j].korisnickoIme>>ki[i].lista[j].nivo>>ki[i].lista[j].poeni;
        }
    }
    najdobarIgrac(ki,n);
}
