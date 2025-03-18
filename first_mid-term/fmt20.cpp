#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Pacient {
    char name[100];
    bool insurance;
    int n; //broj na pregledi vo posledniot mesec
};
struct MaticenDoktor {
    char name[100];
    int n; //broj na pacienti
    Pacient pacienti[200];
    double price; //cena na pregled
};
void najuspesen_doktor(MaticenDoktor *md, int n) {
    int index_md_best=0;
    double max_sum=0.0,current_sum=0.0;
    int max_visits=0,current_visits=0;
    for (int i=0;i<n;i++) {
        current_visits=0,current_sum=0.0;
        for (int j=0;j<md[i].n;j++) {
            current_visits+=md[i].pacienti[j].n;
            if (!(md[i].pacienti[j].insurance)) {
                current_sum+=md[i].pacienti[j].n*md[i].price;
            }
        }
        if (current_sum>max_sum) {
            max_sum=current_sum;
            max_visits=current_visits;
            index_md_best=i;
        }else if (current_sum==max_sum) {
            if (current_visits>max_visits) {
                max_visits=current_visits;
                index_md_best=i;
            }
        }
    }
    cout<<md[index_md_best].name<<" "<<fixed<<setprecision(2)<<max_sum<<" "<<max_visits<<endl;
    //pechati name, zarabotena suma i broj na pregledi na doktorot koj zarabotil najvekje (samo na pacienti koi se insurance==false), ako se 2+ togash togash onoj koj ima najvekje pregledi (site pacienti)
}
int main() {
    int n;
    cin>>n;
    MaticenDoktor md[n];
    for (int i=0;i<n;i++) {
        cin>>md[i].name>>md[i].n>>md[i].price;
        for (int j=0;j<md[i].n;j++) {
            cin>>md[i].pacienti[j].name>>md[i].pacienti[j].insurance>>md[i].pacienti[j].n;
        }
    }
    najuspesen_doktor(md, n);
    return 0;
}
