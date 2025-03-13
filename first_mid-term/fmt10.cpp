#include <iostream>
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
void najdobarIgrac(KompjuterskaIgra *lista, int n) {
    int max_index=0,max=0;
    for (int i=0;i<n;i++) {
        if (lista[i].n>max) {
            max=lista[i].n;
            max_index=i;
        }
    }
    int max_poeni=0,max_poeni_index=0,max_nivo=0;
    for (int i=0;i<lista[max_index].n;i++) {
        if (lista[max_index].lista[i].poeni==max_poeni) {
            if (lista[max_index].lista[i].nivo>max_nivo) {
                max_nivo=lista[max_index].lista[i].nivo;
                max_poeni=lista[max_index].lista[i].poeni;
                max_poeni_index=lista[max_index].lista[i].poeni;
            }
        }
        if (lista[max_index].lista[i].poeni>max_poeni) {
            max_nivo=lista[max_index].lista[i].nivo;
            max_poeni=lista[max_index].lista[i].poeni;
            max_poeni_index=i;
        }
    }
    cout<<"Najdobar igrac e igracot so korisnicko ime "<<lista[max_index].lista[max_poeni_index].korisnickoIme<<" koj ja igra igrata "<<lista[max_index].ime<<endl;
}
int main() {
    int n,m;
    char ime[20];
    cin>>n;
    KompjuterskaIgra poleigri[100];
    for (int i=0; i<n; i++) {
        KompjuterskaIgra nova;
        cin>>nova.ime>>nova.n;
        Igrac pole[30];
        for (int j=0; j<nova.n; j++) {
            Igrac nov;
            cin>>nov.korisnickoIme>>nov.nivo>>nov.poeni;
            nova.lista[j]=nov;
        }
        poleigri[i]=nova;
    }

    najdobarIgrac(poleigri,n);
    return 0;
}