#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <iomanip>
#include <fstream>
using namespace std;
struct Vozenje {
    char ime[100];
    int traenje;
    double cena;
    int daliPopust;
    void print() {
        cout<<ime<<" "<<traenje<<" "<<fixed<<setprecision(2)<<cena<<endl;
    }
};
struct ZabavenPark {
    char ime[100];
    char lokacija[100];
    int n;
    Vozenje niza[100];
    void print() {
        cout<<ime<<" "<<lokacija<<endl;
        for (int i=0;i<n;i++) {
            niza[i].print();
        }
    }
};
void najdobar_park(ZabavenPark *zp, int n) {
    int most_offers_index=0, most_offers=0, most_minutes=0;
    for (int i=0;i<n;i++) {
        int current_offers=0, current_minutes=0;
        if (i==0) {
            most_offers_index=0;
            for (int k=0;k<zp[0].n;k++) {
                most_offers+=zp[0].niza[k].daliPopust;
                most_minutes+=zp[0].niza[k].traenje;
            }
        }
        for (int j=0;j<zp[i].n;j++) {
            current_offers+=zp[i].niza[j].daliPopust;
            current_minutes+=zp[i].niza[j].traenje;
        }
        if ((current_offers==most_offers && current_minutes>=most_minutes) || current_offers>most_offers) {
            most_offers_index=i;
            most_minutes=current_minutes;
            most_offers=current_offers;
        }
    }
    cout<<"Najdobar park: "<<zp[most_offers_index].ime<<" "<<zp[most_offers_index].lokacija<<endl;
}
void pecati(ZabavenPark *zp, int n) {
    for (int i=0;i<n;i++) {
        zp[i].print();
    }
}
int main()
{
    int i, j, n, broj;
    //kreiraj niza od maksimum 100 zabavni parkovi
    ZabavenPark ff[100];
    scanf("%d", &n);
    //citanje na podatocite
    for (i = 0; i < n; i++){
        //ime na festivalot
        cin>>ff[i].ime;
        //mesto
        cin>>ff[i].lokacija;
        //broj na filmovi
        cin>>ff[i].n;
        for (j = 0; j < ff[i].n; j++){
            cin>>ff[i].niza[j].ime; 			/* Ime na filmot */
            cin>>ff[i].niza[j].traenje; 		/* Vremetraenje   */
            cin>>ff[i].niza[j].cena;	/* Cena */
            cin>>ff[i].niza[j].daliPopust;	/* Popust */
        }
    }
    pecati(ff,n);
    najdobar_park(ff,n);
    return 0;
}