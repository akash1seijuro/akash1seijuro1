#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Laptop {
    char name[100];
    float size;
    bool touch;
    int price;
};
struct ITStore {
    char name[100];
    char location[100];
    Laptop laptopi[100];
    int n;
};
void print(ITStore *it, int n) {
    for (int i=0;i<n;i++) {
        cout<<it[i].name<<" "<<it[i].location<<endl;
        for (int j=0;j<it[i].n;j++) {
            cout<<it[i].laptopi[j].name<<" "<<it[i].laptopi[j].size<<" "<<it[i].laptopi[j].price<<endl;
        }
    }
}
void najeftina_ponuda(ITStore *it, int n) {
    int index_it_cheapest=0, index_it_laptop_cheapest=0;
    int smallest_price=__INT_MAX__;
    for (int i=0;i<n;i++) {
        for (int j=0;j<it[i].n;j++) {
            if (it[i].laptopi[j].touch) {
                if (it[i].laptopi[j].price < smallest_price) {
                    smallest_price=it[i].laptopi[j].price;
                    index_it_laptop_cheapest=j;
                    index_it_cheapest=i;
                }
            }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata:"<<endl<<it[index_it_cheapest].name<<" "<<it[index_it_cheapest].location<<endl;
    cout<<"Najniskata cena iznesuva: "<<it[index_it_cheapest].laptopi[index_it_laptop_cheapest].price<<endl;
    //pechati name i location na prodavnicata so najeftin laptop, i vo nov red negovata cena (mora da ima touch==true), ako se 2+ togash prviot
}
int main() {
    ITStore s[100];
    int n;
    cin>>n; //broj na IT prodavnici
    for (int i=0;i<n;i++) {
        cin>>s[i].name>>s[i].location>>s[i].n;
        for (int j=0;j<s[i].n;j++) {
            cin>>s[i].laptopi[j].name>>s[i].laptopi[j].size>>s[i].laptopi[j].touch>>s[i].laptopi[j].price;
        }
    }
    //vnesuvanje na prodavnicite edna po edna, zaedno so raspolozlivite laptopvi vo niv
    print(s,n);
    //pecatenje na site prodavnici
    najeftina_ponuda(s, n);
    //povik na glavnata metoda
    return 0;
}
