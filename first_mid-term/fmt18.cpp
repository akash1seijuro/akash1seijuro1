#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct SkiLift {
    char name[15];
    int n; //maksimalen broj na korisnici odednash
    bool valid;
};
struct SkiCenter {
    char name[20];
    char country[20];
    SkiLift lifts[20];
    int n;
};
void najgolemKapacitet(SkiCenter *sc, int n) {
    int index_sc_max=0;
    int max_capacity=0,max_ski_lifts=0;
    for (int i=0;i<n;i++) {
        int current_capacity=0,current_ski_lifts=0;
        for (int j=0;j<sc[i].n;j++) {
            if (sc[i].lifts[j].valid) {
                current_capacity+=sc[i].lifts[j].n;
                current_ski_lifts++;
            }
        }
        if (current_capacity>max_capacity) {
            max_capacity=current_capacity;
            max_ski_lifts=current_ski_lifts;
            index_sc_max=i;
        }else if (current_capacity==max_capacity) {
            if (current_ski_lifts>max_ski_lifts) {
                max_ski_lifts=current_ski_lifts;
                index_sc_max=i;
            }
        }
    }
    cout<<sc[index_sc_max].name<<endl<<sc[index_sc_max].country<<endl<<max_capacity<<endl;
    //pechati name<<endl<<country<<n na SKiCenter koj ima max korisnici odednash (od site skiliftovi, koi se valid==true), ako se 2+ togash toj koj ima > broj skiliftovi
}
int main() {
    int n;
    cin>>n;
    SkiCenter sc[n];
    for (int i=0;i<n;i++) {
        cin>>sc[i].name>>sc[i].country>>sc[i].n;
        for (int j=0;j<sc[i].n;j++) {
            cin>>sc[i].lifts[j].name>>sc[i].lifts[j].n>>sc[i].lifts[j].valid;
        }
    }
    najgolemKapacitet(sc,n);
    return 0;
}
