#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Tanc {
    char name[15];
    char country[15];
};
struct Tancer {
    char name[20];
    char surname[20];
    Tanc tanci[5];
};
void tancuvanje(Tancer *t, int n, char *zemja) {
    for (int i=0;i<n;i++) { //mine niz site tancheri
        for (int j=0;j<3;j++) { //mine niz site tancovi na sekoj tancher poedinechno
            if (strcmp(t[i].tanci[j].country,zemja) == 0) {
                cout<<t[i].name<<" "<<t[i].surname<<", "<<t[i].tanci[j].name<<endl;
                break; //dovolno e 1
            }
        }
    }
    //pechati vo poseben red name i surname na tancherite (mozhe 2+) koi znaat da igraat 1+ tanc od zemjata dadena vo argument char *zemja
    //ime prezime imenatanc
}
int main() {
    int n;
    cin>>n;
    Tancer t[n];
    for (int i=0;i<n;i++) {
        cin>>t[i].name>>t[i].surname;
        for (int j=0;j<3;j++) {
            cin>>t[i].tanci[j].name>>t[i].tanci[j].country;
        }
    }
    char zemja[20];
    cin>>zemja;
    tancuvanje(t, n, zemja);
    return 0;
}
