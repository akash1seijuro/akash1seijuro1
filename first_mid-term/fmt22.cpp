#include <iostream>
#include <iomanip>
#include <algorithm>
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
    char name[15];
    Proizvod proizvodi[10];
    int odelno_narachani[10]; //za sekoj proizvod, kolku pati e narachan
    int n;//broj na proizvodi na narachkata
};
void pecatiFaktura(Narachka n) {
    cout<<"Faktura za "<<n.name<<endl;
    for (int i=0;i<n.n;i++) {
        for (int j=0;j<n.n;j++) {
            if (n.proizvodi[j].quantity<n.odelno_narachani[j]) {
                cout<<"Fakturata ne moze da se izgotvi"<<endl;
                return;
            }
        }
    }
    int total=0;
    /*
    int n;
    cin>>n;
    char **names = new char*[n];
    sort(names,names+n, [] (const char* a, const char* b) {
        return strcmp(a, b) < 0;
    });
     */
    for (int i=0;i<n.n-1;i++) {
        if (n.proizvodi[i].code[0]>n.proizvodi[i+1].code[0]) {
            swap(n.proizvodi[i],n.proizvodi[i+1]);
        }else if (n.proizvodi[i].code[1]>n.proizvodi[i+1].code[1]) {
            swap(n.proizvodi[i],n.proizvodi[i+1]);
        }
    }
    for (int i=0;i<n.n;i++) {
        cout<<n.proizvodi[i].code<<" "<<n.proizvodi[i].price<<" "<<n.odelno_narachani[i]<<" "<<n.odelno_narachani[i]*n.proizvodi[i].price<<endl;
        n.proizvodi[i].quantity-=n.odelno_narachani[i]; //azhuriranje
        total+=n.odelno_narachani[i]*n.proizvodi[i].price;
    }
    cout<<"Vkupnata suma na fakturata e "<<total<<endl;
    //tuka e delot kadeshto sigurno mozheme da ja napravime narachkata, kod+cena+broj_na_narachani_proizvodi+vkupna_cena_proizvod
    //i azhuriraj go brojot na dostapni kvantitet za toj proizvod otkatko kje se zemat del od niv vo narachkata
    //pechati edna faktura za edna naracha(n), "Faktura za " XXXXXX, t.s. XXXXX e imeto na liceto chija e narachkata
}
int main() {
    Narachka narachka;
    cin>>narachka.name;
    // внеси го името лицето кое ја прави нарачката
    cin>>narachka.n;
    // внеси го бројот на порачани производи во нарачката
    //за секој од нарачаните производи се внесуваат информации
    for (int i = 0; i < narachka.n; ++i) {
        cin>>narachka.proizvodi[i].code;
        // внеси код
        cin>>narachka.proizvodi[i].price;
        // внеси единицчна цена
        cin>>narachka.proizvodi[i].quantity;
        // внеси број на производи во магацин
    }
    //за секој производ се внесува колку такви производи се порачани во нарачката
    int j;
    for (j = 0; j < narachka.n; ++j) {
        cin>>narachka.odelno_narachani[j];
        //се внесува број на производи во нарачката
    }

    pecatiFaktura(narachka);
    // повик на функцијата pecatiFaktura


    return 0;
}