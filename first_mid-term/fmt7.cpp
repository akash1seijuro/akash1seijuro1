#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Vozenje {
    char name[100];
    int duration;
    double price;
    bool offer;
};
struct ZabavenPark {
    char name[100];
    char location[100];
    Vozenje vozenja[100];
    int n;
};
void pecati(ZabavenPark *zp, int n) {
    for (int i=0;i<n;i++) {
        cout<<zp[i].name<<" "<<zp[i].location<<endl;
        for (int j=0;j<zp[i].n;j++) {
            cout<<zp[i].vozenja[j].name<<" "<<zp[i].vozenja[j].duration<<" "<<fixed<<setprecision(2)<<zp[i].vozenja[j].price<<endl;
        }
    }
}
void najdobar_park(ZabavenPark *zp, int n) {
    int index_zp_cheapest_park=0, max_offers=0, max_duration=0;
    for (int i=0;i<n;i++) {
        int current_offers=0, current_duration=0;
        for (int j=0;j<zp[i].n;j++) {
            current_duration+=zp[i].vozenja[j].duration;
            if (zp[i].vozenja[j].offer) {
                current_offers++;
            }
        }
        if (current_offers>max_offers) {
            max_offers=current_offers;
            max_duration=current_duration;
            index_zp_cheapest_park=i;
        }else if (current_offers==max_offers) {
            if (current_duration>max_duration) {
                max_duration=current_duration;
                index_zp_cheapest_park=i;
            }
        }
    }
    cout<<"Najdobar park: "<<zp[index_zp_cheapest_park].name<<" "<<zp[index_zp_cheapest_park].location<<endl;
    //pechati name i location na parkot koj ima najgolem broj offer's, ako se 2+ togash onoj so najdolgo traenje (od site vozenja, ne samo offer)
}


int main()
{
    int n;
    cin>>n;
    ZabavenPark ff[100];
    for (int i=0;i<n;i++) {
        cin>>ff[i].name>>ff[i].location>>ff[i].n;
        for (int j=0;j<ff[i].n;j++) {
            cin>>ff[i].vozenja[j].name>>ff[i].vozenja[j].duration>>ff[i].vozenja[j].price>>ff[i].vozenja[j].offer;
        }
    }
    pecati(ff,n);
    najdobar_park(ff,n);
    return 0;
}
