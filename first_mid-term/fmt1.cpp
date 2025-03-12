#include <iostream>
#include <cstring>
using namespace std;
enum tip {
    POP=0,RAP,ROK
};
class Pesna {
private:
    char *name;
    int time;
    tip type;
public:
    char* getName() {
        return this->name;
    }
    int getTime() {
        return this->time;
    }
    tip getType() {
        return this->type;
    }
    void setName(char *name) {
        this->name = name;
    }
    void setTime(int time) {
        this->time = time;
    }
    void setType(tip type) {
        this->type = type;
    }
    Pesna(const char *name="", int time=0, int type=0) {
        this->name = new char[strlen(name)+1];
        strcpy(this->name, name);
        this->time = time;
        this->type=(tip)type;
    }
    Pesna(const Pesna &p) {
        this->name = new char[strlen(p.name)+1];
        strcpy(this->name, p.name);
        this->time = p.time;
        this->type = (tip)p.type;
    }
    Pesna &operator=(const Pesna &p) {
        if (this!=&p) {
            delete[] name;
            this->name = new char[strlen(p.name)+1];
            strcpy(this->name, p.name);
            this->time = p.time;
            this->type = (tip)p.type;
        }
        return *this;
    }
    ~Pesna() {
        delete[] name;
    }
    void pecati() {
        cout<<"\""<<this->name<<"\""<<"-"<<time<<"min"<<endl;
    }
};
class CD {
private:
    Pesna pesni[10];
    int number;
    int duration;
public:
    int getBroj() {
        return this->number;
    }
    int getDuration() {
        return this->duration;
    }
    void setNumber(int number) {
        this->number = number;
    }
    void setDuration(int duration) {
        this->duration = duration;
    }
    Pesna getPesna(int i) {
        return pesni[i];
    }
    CD(int duration=0,int number=0) {
        this->duration = duration;
        this->number = 0;
    }
    void dodadiPesna(Pesna p) {
        int vkupnoVreme = 0;
        for (int i = 0; i < number; i++) {
            vkupnoVreme += pesni[i].getTime();
        }
        if (number < 10 && vkupnoVreme + p.getTime() <= duration) {
            pesni[number++] = p;
        }
    }
    void pecatiPesniPoTip(int t) {
        for (int i = 0; i < number; i++) {
            if (pesni[i].getType() == t) {
                pesni[i].pecati();
            }
        }
    }
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, minuti, kojtip;
	char ime[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
		p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<n; i++)
				(omileno.getPesna(i)).pecati();
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        	for (int i=0; i<omileno.getBroj(); i++)
				(omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
		CD omileno(20);
		cin>>n;
			for (int i=0;i<n;i++){
				cin >> ime;
				cin >> minuti;
				cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
				Pesna p(ime,minuti,(tip)kojtip);
				omileno.dodadiPesna(p);
			}
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

return 0;
}