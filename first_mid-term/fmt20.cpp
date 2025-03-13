#include <iostream>
#include <iomanip>
#include <cstring>
using namespace std;
struct Pacient {
    char ime[100];
    int zdrastveno;
    int pregledi;
};
struct doktor {
    char name[100];
    int br_pac;
    Pacient niza[200];
    double cena;
};
void najuspesen_doktor(doktor *d, int n) {
    double current_max=0.0, max_max=0.0;
    int max_max_index=0;
    int current_all_pregledi=0, max_all_pregledi=0;
    int current_pregledi=0, max_pregledi=0; //privatnite za vo print-ot dole trebaat
    for (int i=0;i<n;i++) {
        current_max=0,current_all_pregledi=0,current_pregledi=0;
        for (int j=0;j<d[i].br_pac;j++) {
            current_all_pregledi+=d[i].niza[j].pregledi;
            if (d[i].niza[j].zdrastveno == 0) {
                current_pregledi+=d[i].niza[j].pregledi;
                current_max+=d[i].niza[j].pregledi;
            }
        }
        if (current_max>max_max) {
            max_max=current_max;
            max_max_index=i;
            max_all_pregledi=current_all_pregledi;
            if (current_pregledi>max_pregledi) {
                max_pregledi=current_pregledi;
            }
        }else if (current_max==max_max) {
            if (current_all_pregledi>max_all_pregledi) {
                max_max_index=i;
                max_max=current_max;
                max_all_pregledi=current_all_pregledi;
                if (current_pregledi>max_pregledi) {
                    max_pregledi=current_pregledi;
                }
            }
        }
    }
    cout<<d[max_max_index].name<<" "<<fixed<<setprecision(2)<<max_pregledi*d[max_max_index].cena<<" "<<max_all_pregledi<<endl;
}
int main()
{
    int i, j, n, broj;
    doktor md[200];
    cin>>n;
    for (i = 0; i < n; i++){
        //ime na doktor
        cin>>md[i].name;
        //broj na pacienti
        cin>>md[i].br_pac;
        //cena na pregled
        cin>>md[i].cena;

        for (j = 0; j < md[i].br_pac; j++){
            cin>>md[i].niza[j].ime;
            cin>>md[i].niza[j].zdrastveno;
            cin>>md[i].niza[j].pregledi;
        }
    }
    najuspesen_doktor(md, n);
    return 0;
}