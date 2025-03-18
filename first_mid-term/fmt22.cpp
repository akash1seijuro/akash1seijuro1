#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Proizvod {
    char code[20];
    int price;
    int quantity;
};
struct Narachka {
    char name[15]; //imeto na chovekot koj ja pravi narachkata
    Proizvod proizvodi[10];
    int n[10]; //za sekoj proizvod, kolku pati e narachan
    int all; //brojot na proizvodi vo narachkata
};
void pecatiFaktura(Narachka n) {
    cout << "Faktura za " << n.name << endl;
    int max_sum=0;
    for (int i=0;i<n.all;i++) { //mine niz site proizvodi
        if (n.proizvodi[i].quantity - n.n[i] < 0) {
            cout<<"Fakturata ne moze da se izgotvi"<<endl;
            return;
        }
    }
    for (int i=0;i<n.all;i++) {
        for (int j=0;j<n.all-i-1;j++) {
            if (strcmp(n.proizvodi[j].code,n.proizvodi[j+1].code) > 0) {
                swap(n.proizvodi[j],n.proizvodi[j+1]);
            }
        }
    }
    for (int i=0;i<n.all;i++) {
        max_sum+=n.n[i]*n.proizvodi[i].price;
        cout<<n.proizvodi[i].code<<" "<<n.proizvodi[i].price<<" "<<n.n[i]<<" "<<n.n[i]*n.proizvodi[i].price<<endl;
    }
    cout<<"Vkupnata suma na fakturata e "<<max_sum<<endl;
    //pechati name za imeto na chovekot koj ja ima narachkata "n";
    //ako site proizvodi od narachkata "n" mozhat da se narachaat (gi ima vo magacinot, "quantity"), togash pechati: code price quantity vkupnacena;
    //azhuriraj go brojot na dostapni proizvodi za sekoj proizvod
}
int main() {
    Narachka narachka;
    cin>>narachka.name>>narachka.all;
    for (int i=0;i<narachka.all;i++) {
        cin>>narachka.proizvodi[i].code>>narachka.proizvodi[i].price>>narachka.proizvodi[i].quantity;
    }
    for (int i=0;i<narachka.all;i++) {
        cin>>narachka.n[i];
    }
    pecatiFaktura(narachka);
    return 0;
}
