#include <iostream>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Laptop {
    char firma[100];
    float inches;
    bool touch;
    int price;
    void print() {
        cout<<firma<<" "<<inches<<" "<<price<<endl;
    }
};
struct ITStore {
    char name[100];
    char location[100];
    Laptop laptopi[100];
    int size;
    void print() {
        cout<<name<<" "<<location<<endl;
        for (int i=0;i<size;i++) {
            laptopi[i].print();
        }
    }
};
void najeftina_ponuda(ITStore *it, int n) {
    int cheapest_ever=__INT_MAX__, cheapest_ever_index=-1;
    for (int i=0;i<n;i++) {
        for (int j=0;j<it[i].size;j++) {
            if (it[i].laptopi[j].touch && it[i].laptopi[j].price<cheapest_ever) {
                cheapest_ever=it[i].laptopi[j].price;
                cheapest_ever_index=i;
            }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata: "<<endl<<it[cheapest_ever_index].name<<" "<<it[cheapest_ever_index].location<<endl;
    cout<<"Najniskata cena iznesuva: "<<cheapest_ever<<endl;
}
int main() {
    ITStore s[100];
    int n;
    cin>>n;
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    for (int i=0;i<n;i++) {
        cin>>s[i].name>>s[i].location>>s[i].size;
        for (int j=0;j<s[i].size;j++) {
            cin>>s[i].laptopi[j].firma>>s[i].laptopi[j].inches>>s[i].laptopi[j].touch>>s[i].laptopi[j].price;
        }
    }
    for (int i=0;i<n;i++) {
        s[i].print();
    }
    //povik na glavnata metoda
    najeftina_ponuda(s, n);
    return 0;
}