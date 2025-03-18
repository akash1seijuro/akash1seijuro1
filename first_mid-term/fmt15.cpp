#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
#define NEDELI 4
#define DENOVI 5
struct RabotnaNedela {
    int casovi[5]; //sekoja rabotna nedela ima svoj broj na rabotni chasovi
    int nedela; //broj na nedelata
};
struct Rabotnik {
    char ime[50];
    RabotnaNedela nedeli[4];
};
int maxNedela(Rabotnik *r) {
    int index_rabotnanedela=0;
    int most_hours=0;
    for (int i=0;i<4;i++) { //mine niz sekoja RabotnaNedela
        int current_hours=0;
        for (int j=0;j<5;j++) { //do 5 bidejki sekoja RabotnaNedela ima max 5 dena vo koja ima rabotni chasovi
            current_hours+=r->nedeli[i].casovi[j];
        }
        if (current_hours>most_hours) {
            most_hours=current_hours;
            index_rabotnanedela=i;
        }
    }
    return index_rabotnanedela+1;//oti se bara da pochnuva od 1, faktichki i=0 kje treba da vrakja 1
    //ja vrakja RabotnaNedela na rabotnikot *r vo koja ima najgolem broj rabotni chasovi
}
void table(Rabotnik *r, int n) {
    cout<<"Rab\t"<<"1\t"<<"2\t"<<"3\t"<<"4\t"<<"Vkupno"<<endl;
    for (int i=0;i<n;i++) {
        cout<<r[i].ime<<"\t";
        int max_sum=0;
        for (int j=0;j<4;j++) {
            int sum=0;
            for (int k=0;k<5;k++) {
                sum+=r[i].nedeli[j].casovi[k];
            }
            max_sum+=sum;
            cout<<sum<<"\t";
        }
        cout<<max_sum;
        cout<<endl;
    }
}
int main() {
    int n;
    cin>>n;
    Rabotnik rabotnici[n];
    for (int i = 0; i < n; ++i) {
        cin>>rabotnici[i].ime;
        for (int j = 0; j < NEDELI; ++j) {
            for (int k = 0; k < DENOVI; ++k) {
                cin>>rabotnici[i].nedeli[j].casovi[k];
            }
        }
    }
    cout<<"TABLE"<<endl;
    table(rabotnici, n);
    cout<<"MAX NEDELA NA RABOTNIK: "<<rabotnici[n/2].ime<<endl;
    cout<<maxNedela(&rabotnici[n/2]);
    return 0;
}
