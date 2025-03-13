#include <iostream>
#include <cstring>
using namespace std;
struct SkiLift {
    char ime[15];
    int max;
    bool working;
};
struct SkiCenter {
    char ime[20];
    char drzhava[20];
    SkiLift skiLifts[20];
    int n; //broj na ski-liftovi
};
void najgolemKapacitet(const SkiCenter *sc, int n) {
    int max_capacity=0,max_ski_lifts=0,max_capacity_index=0;
    for (int i=0;i<n;i++) {
        int current_capacity=0,current_ski_lifts=0;
        for (int j=0;j<sc[i].n;j++) {
            if (sc[i].skiLifts[j].working) {
                current_ski_lifts++;
                current_capacity+=sc[i].skiLifts[j].max;
            }
        }
        if (current_ski_lifts>=max_ski_lifts) {
            max_ski_lifts=current_ski_lifts;
        }
        if (current_capacity > max_capacity) {
            max_capacity = current_capacity;
            max_capacity_index = i;
        }else if (current_capacity == max_capacity && max_ski_lifts <= current_ski_lifts) {
            max_ski_lifts = current_ski_lifts;
            max_capacity_index = i;
            max_capacity = current_capacity;
        }
        //ispechati go ski-centarot so najgolem broj korisnici vo istovreme, ako 2+ se isti togash tojshto ima pogolem broj
        //ski-liftovi; ime<<endl<<drzhava<<kapacitet (vo predvid samo working=true liftovite
    }
    cout<<sc[max_capacity_index].ime<<endl<<sc[max_capacity_index].drzhava<<endl<<max_capacity<<endl;
}
int main()
{
    int n;
    cin>>n;
    SkiCenter sc[n];
    for (int i = 0; i < n; i++){
        cin>>sc[i].ime>>sc[i].drzhava>>sc[i].n;
        for (int j=0;j<sc[i].n;j++) {
            cin>>sc[i].skiLifts[j].ime>>sc[i].skiLifts[j].max>>sc[i].skiLifts[j].working;
        }
    }
    najgolemKapacitet(sc,n);
    return 0;
}