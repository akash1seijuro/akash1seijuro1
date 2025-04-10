#include <iostream>
#include <cstring>
using namespace std;
class Robot;
class Colony;
enum Type {
    EMPLOYER=0,WORKER,SCIENTIST
};
class Robot {
private:
    char name[51];
    int battery;
    Type category;
public:
    friend void addBatteryForOthersCategory(Colony *c, int n, Type notfromthisCategory, int amount);
    const char *getName() const {
        return name;
    }
    Type getCategory() const {
        return category;
    }
    Robot(const char *name="", int battery=0, Type category=EMPLOYER) { //vo mainot nemashe kako prethodnata zadacha zamaranje so int(type)
        strcpy(this->name,name);
        this->battery = battery;
        this->category = category;
    }
    void addBattery(int increase) {
        int total=battery+increase;
        if (total>100) {
            battery=100;
        }else {
            battery+=increase;
        }
    } //tl;dr, ako e nad 100, neka ostane 100, ako e pod, togash dodadi kolku sho prakjash so increase
    void print() const {
        cout<<name<<endl<<battery;
        if (category==EMPLOYER) {
            cout<<"EMPLOYER"<<endl;
        }else if (category==WORKER) {
            cout<<"WORKER"<<endl;
        }else {
            cout<<"SCIENTIST"<<endl;
        }
    } //nebiten tolku mn print
};
class Colony {
    private:
    char name[51];
    Robot robots[100];
    int n; //broj na roboti
    public:
    friend void addBatteryForOthersCategory(Colony *c, int n, Type notfromthisCategory, int amount);
    int getN() const { //ne se bara vo zadachata ni main, ama mora za da raboti skroz dole metodata
        return n;
    }
    Colony(const char *name="") {
        strcpy(this->name,name);
        n=0;
    }
    void addRobot(const Robot &r) {//SAMO AKO GO NEMA PO IME I TIP, TOGASH DA SE DODADE
        for (int i=0;i<n;i++) {
            if (strcmp(robots[i].getName(),r.getName())==0 && robots[i].getCategory()==r.getCategory()){
                cout<<"This robot can't be added!"<<endl; //nestho vaka tekst
                return; //nema sho da se pravi vekje, bez ova return kje prodolzi pak nadole za dzabe
            }
        }
        if (n<100) { //mozhe i bez ova, chisto da ne otideme offside
            robots[n++]=r;
        }
    }
    void print() const {
        cout<<"Name: "<<name<<endl;
        for (int i=0;i<n;i++) {
            robots[i].print();
        }
    } //pak nebiten tolku mn print
};
void addBatteryForOthersCategory(Colony *c, int n, Type notfromthisCategory, int amount) { //NE E BITNO IMEVO, SLICHNO NESHTO BESEH; PRVOTO E NIZA KOLONII, VTOROTO KOLKU SE, TRETOTO POKACHUVANJE NA BATERIJATA ZA amount
    //SAMO ZA TIE SHO NE SE OD category
    for (int i=0;i<n;i++) {
        for (int j=0;j<c[i].getN();j++) {
            if (c[i].robots[j].getCategory()!=notfromthisCategory) {
                c[i].robots[j].addBattery(amount);
            }
        }
    }
}//TL;DR TREBASHE DA SE DODADE NA SEKOJ ROBOT BATERIJA povekje amount, SAMO AKO NE E OD TAA KATEGORIJA SHO SE PRAKJA U METODANA