#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
struct Voz {
    char relacija[50];
    double kilometri;
    int patnici;
    Voz(const char *relacija = "", double kilometri = 0, int patnici = 0) {
        strcpy(this->relacija, relacija);
        this->kilometri = kilometri;
        this->patnici = patnici;
    }
};
struct ZeleznickaStanica {
    char grad[20];
    Voz vozovi[30];
    int brojVozovi;
    ZeleznickaStanica(const char *grad = "") {
        strcpy(this->grad, grad);
        brojVozovi = 0;
    }
    void dodadiVoz(Voz v) {
        if (brojVozovi < 30) {
            vozovi[brojVozovi++] = v;
        }
    }
};
void najkratkaRelacija(ZeleznickaStanica *zs, int n, char *grad) {
    Voz *najkratokVoz = nullptr;
    for (int i = 0; i < n; i++) {
        if (strcmp(zs[i].grad, grad) == 0) {
            for (int j = 0; j < zs[i].brojVozovi; j++) {
                if (najkratokVoz == nullptr || zs[i].vozovi[j].kilometri <= najkratokVoz->kilometri) {
                    najkratokVoz = &zs[i].vozovi[j];
                }
            }
        }
    }
    if (najkratokVoz != nullptr) {
        cout << "Najkratka relacija: " << najkratokVoz->relacija << " (" << najkratokVoz->kilometri << " km)" << endl;
    }
}
int main() {
    int n;
    cin >> n;
    ZeleznickaStanica zStanica[100];
    for (int i = 0; i < n; i++) {
        char grad[20];
        cin >> grad;
        zStanica[i] = ZeleznickaStanica(grad);
        int brojVozovi;
        cin >> brojVozovi;
        for (int j = 0; j < brojVozovi; j++) {
            char relacija[50];
            double kilometri;
            int patnici;
            cin >> relacija >> kilometri >> patnici;
            zStanica[i].dodadiVoz(Voz(relacija, kilometri, patnici));
        }
    }
    char grad[25];
    cin >> grad;
    najkratkaRelacija(zStanica, n, grad);
    return 0;
}
