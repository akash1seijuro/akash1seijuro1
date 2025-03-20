#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
enum tip {
	POP=0,RAP,ROK
};
class Pesna {
private:
	char *name;
	int duration;
	tip type;
	void copy(const Pesna &p) {
		name = new char[strlen(p.name)+1];
		strcpy(name, p.name);
		duration = p.duration;
		type = p.type;
	}
public:
	tip getTip() {
		return type;
	}
	int getDuration() {
		return duration;
	}
	Pesna(const char *name="", int duration=0, tip type=POP) {
		this->name = new char[strlen(name)+1];
		strcpy(this->name, name);
		this->duration = duration;
		this->type = type;
	}
	Pesna(const Pesna &p) {
		copy(p);
	}
	Pesna &operator=(const Pesna &p) {
		if (this!=&p) {
			delete [] name;
			copy(p);
		}
		return *this;
	}
	~Pesna() {
		delete [] name;
	}
	void pecati() {
		cout<<"\""<<name<<"\"-"<<duration<<"min"<<endl;
	}
};
class CD {
private:
	Pesna pesni[10];
	int n;
	int duration; //maks. dozvoleno vremetraenje na site pesni vo CD-to
public:
	Pesna getPesna(int i) {
		return pesni[i];
	}
	int getBroj() {
		return n;
	}
	CD(int duration=0) {
		this->duration = duration;
		n = 0;
	}
	void dodadiPesna(Pesna p) {
		int total=p.getDuration();
		for (int i=0;i<n;i++) {
			total+=pesni[i].getDuration();
		}
		if (n>=10 || total>duration) {
			return;
		}
		pesni[n++]=p;
	}
	void pecatiPesniPoTip(tip t) {
		for (int i=0;i<n;i++) {
			if (pesni[i].getTip()==t) {
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
