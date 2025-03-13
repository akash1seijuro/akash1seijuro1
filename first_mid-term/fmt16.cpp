#include <iostream>
#include <cstring>
using namespace std;
#define NEDELI 4
#define DENOVI 5
struct RabotnaNedela {
    int casovi[DENOVI];
};
struct Rabotnik {
    char ime[50];
    RabotnaNedela nedeli[NEDELI];
};
int maxNedela(Rabotnik* r) {
    int maxHours = 0;
    int maxWeek = 0;
    for (int i = 0; i < NEDELI; ++i) {
        int totalHours = 0;
        for (int j = 0; j < DENOVI; ++j) {
            totalHours += r->nedeli[i].casovi[j];
        }
        if (totalHours > maxHours) {
            maxHours = totalHours;
            maxWeek = i;
        }
    }
    return maxWeek + 1;
}
void table(Rabotnik* r, int n) {
    cout << "Rab\t1\t2\t3\t4\tVkupno" << endl;
    for (int i = 0; i < n; ++i) {
        cout << r[i].ime;
        int totalHours = 0;
        for (int j = 0; j < NEDELI; ++j) {
            int weekHours = 0;
            for (int k = 0; k < DENOVI; ++k) {
                weekHours += r[i].nedeli[j].casovi[k];
            }
            totalHours += weekHours;
            cout << "\t" << weekHours;
        }
        cout << "\t" << totalHours << endl;
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
    cout << "MAX NEDELA NA RABOTNIK: " << rabotnici[n / 2].ime << endl;
    cout << maxNedela(&rabotnici[n / 2]) << endl;
    return 0;
}
