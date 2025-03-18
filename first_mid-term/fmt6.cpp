#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Voz {
    char path[50];
    float distance;
    int passengers;
};
struct ZeleznickaStanica {
    char city[20];
    Voz vozovi[30];
    int n;
};
void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad) {
    int index_zs_smallest_distance=0, index_zs_vozovi_smallest_distance=0;
    float smallest_distance=float(__INT_MAX__);
    for (int i=0;i<n;i++) {
        if (strcmp(zs[i].city,grad)==0) {
            for (int j=0;j<zs[i].n;j++) {
                if (zs[i].vozovi[j].distance<=smallest_distance) { //<= za da go zeme posledniot
                    smallest_distance=zs[i].vozovi[j].distance;
                    index_zs_smallest_distance=i;
                    index_zs_vozovi_smallest_distance=j;
                }
            }
        }
    }
    cout<<"Najkratka relacija: "<<zs[index_zs_smallest_distance].vozovi[index_zs_vozovi_smallest_distance].path<<" ("<<zs[index_zs_smallest_distance].vozovi[index_zs_vozovi_smallest_distance].distance<<" km)"<<endl;
}
//RABOTI I OVA !!!
// void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad) {
//     float smallest_distance=(float)__INT_MAX__, current_distance=(float)__INT_MAX__;
//     char shortest_path[50], current_path[50];
//     for (int i=0;i<n;i++) { //mine niz site zheleznichki
//         if (strcmp(zs[i].city, grad) == 0) {
//             current_distance=(float)__INT_MAX__;
//             current_path[0]='\0';
//             for (int j=0;j<zs[i].n;j++) { //mine niz site vozovi od sekoja zheleznichka
//                 if (zs[i].vozovi[j].distance <= current_distance) {
//                     current_distance=zs[i].vozovi[j].distance;
//                     strcpy(current_path,zs[i].vozovi[j].path);
//                 }
//             }
//             if (current_distance <= smallest_distance) {
//                 smallest_distance=current_distance;
//                 strcpy(shortest_path,current_path);
//             }
//         }
//     }
//     cout<<"Najkratka relacija: "<<shortest_path<<" ("<<smallest_distance<<" km)"<<endl;
//     //pechati relacijata/path i distance na vozot koj minuva najmalku kilometri a e od zheleznichka so ist grad kako arg char *grad, ako ima 2+, togash posledniot
// }

int main(){

    int n;
    cin>>n; //se cita brojot na zelezlnichki stanici

    ZeleznickaStanica zStanica[100];
    for (int i=0;i<n;i++){
        cin>>zStanica[i].city>>zStanica[i].n;
        for (int j=0;j<zStanica[i].n;j++) {
            cin>>zStanica[i].vozovi[j].path>>zStanica[i].vozovi[j].distance>>zStanica[i].vozovi[j].passengers;
        }
        //se citaat infomracii za n zelezlnichkite stanici i se zacuvuvaat vo poleto zStanica
    }

    char grad[25];
    cin>>grad;

    najkratkaRelacija(zStanica,n,grad);
    return 0;
}






