#include <iostream>
#include <cstring>
using namespace std;

#define DENOVI 5
#define NEDELI 4

struct RabotnaNedela {
    int casovi[DENOVI];
    int broj_na_nedela;
};

struct Rabotnik {
    char ime[50];
    RabotnaNedela nedeli[NEDELI];
};

int maxNedela(Rabotnik r) {
    int maxCasovi = 0, maxNedelaIndex = 0;
    for (int i = 0; i < NEDELI; i++) {
        int suma = 0;
        for (int j = 0; j < DENOVI; j++) {
            suma += r.nedeli[i].casovi[j];
        }
        if (suma > maxCasovi) {
            maxCasovi = suma;
            maxNedelaIndex = i;
        }
    }
    return maxNedelaIndex + 1;
}

void table(Rabotnik r[], int n) {
    cout << "Rab\t1\t2\t3\t4\tVkupno" << endl;
    for (int i = 0; i < n; i++) {
        cout << r[i].ime << "\t";
        int total = 0;
        for (int j = 0; j < NEDELI; j++) {
            int weeklyTotal = 0;
            for (int k = 0; k < DENOVI; k++) {
                weeklyTotal += r[i].nedeli[j].casovi[k];
            }
            total += weeklyTotal;
            cout << weeklyTotal << "\t";
        }
        cout << total << endl;
    }
}

int main() {
    int n;
    cin >> n;
    Rabotnik rabotnici[n];
    for (int i = 0; i < n; ++i) {
        cin >> rabotnici[i].ime;
        for (int j = 0; j < NEDELI; ++j) {
            for (int k = 0; k < DENOVI; ++k) {
                cin >> rabotnici[i].nedeli[j].casovi[k];
            }
        }
    }
    cout << "TABLE" << endl;
    table(rabotnici, n);
    cout << "MAX NEDELA NA RABOTNIK: " << rabotnici[n/2].ime << endl << maxNedela(rabotnici[n/2]);
    return 0;
}