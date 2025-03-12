#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Gitara {
private:
	char serial_number[25];
	float price;
	int production_year;
	char type[40];
public:
	float getNabavna() {
		return price;
	}
	char *getSeriski() {
		return serial_number;
	}
	int getGodina() {
		return this->production_year;
	}
	char *getTip(){
	    return this->type;
	}
	Gitara(const char *type="", const char *serial_number="", int production_year=0, float price=0) {
		strcpy(this->serial_number, serial_number);
		this->price = price;
		this->production_year = production_year;
		strcpy(this->type, type);
	}
	bool daliIsti(Gitara &g) {
		return strcmp(g.serial_number, serial_number) == 0;
	}
	void pecati() {
		cout<<serial_number<<" "<<type<<" "<<price<<endl;
	}
};
class Magacin {
private:
	char name[30];
	char location[60];
	Gitara *gitari;
	int size;
	int opening_year;
	void copy(const Magacin &m) {
		strcpy(name, m.name);
		strcpy(location, m.location);
		this->gitari = new Gitara[m.size];
		for (int i=0;i<m.size;i++) {
			this->gitari[i] = m.gitari[i];
		}
		this->size = m.size;
		this->opening_year = m.opening_year;
	}
public:
	int getOpeningYear() {
		return this->opening_year;
	}
	Magacin(const char*name="", const char*location="", int opening_year=1900) {
		strcpy(this->name, name);
		strcpy(this->location, location);
		this->opening_year = opening_year;
		this->size = 0;
		this->gitari=nullptr;
	}
	Magacin(const Magacin &m) {
		copy(m);
	}
	Magacin& operator=(const Magacin &m) {
		if (this!=&m) {
			delete [] gitari;
			copy(m);
		}
		return *this;
	}
	~Magacin() {
		if (gitari!=nullptr) {
			delete [] gitari;
		}
	}
	double vrednost() {
		double sum=0;
		for (int i=0;i<size;i++) {
			sum+=this->gitari[i].getNabavna();
		}
		return sum;
	}
	void dodadi(Gitara d) {
		Gitara *new_gitari = new Gitara[size+1];
		for (int i=0;i<size;i++) {
			new_gitari[i] = this->gitari[i];
		}
		new_gitari[size]=d;
		delete [] gitari;
		gitari=new_gitari;
		size++;
	}
	void prodadi(Gitara p) {
		int count=0;
		for (int i=0;i<size;i++) {
			if (gitari[i].daliIsti(p)) {
				count++;
			}
		}
		if (count==0) {
			return;
		}
		Gitara *new_gitari = new Gitara[size-count];
		int j=0;
		for (int i=0;i<size;i++) {
			if (!(gitari[i].daliIsti(p))) {
				new_gitari[j++] = gitari[i];
			}
		}
		delete [] gitari;
		gitari=new_gitari;
		size-=count;
	}
	void pecati(bool daliNovi) {
		cout<<name<<" "<<location<<endl;
		if (!(daliNovi)) {
			for (int i=0;i<size;i++) {
				gitari[i].pecati();
			}
		}else {
			for (int i=0;i<size;i++) {
				if (gitari[i].getGodina()>opening_year) {
					gitari[i].pecati();
				}
			}
		}
	}
};
int main() {
	// se testira zadacata modularno
    int testCase;
    cin >> testCase;

	int n, godina;
	float cena;
	char seriski[50],tip[50];

	if(testCase == 1) {
        cout << "===== Testiranje na klasata Gitara ======" << endl;
        cin>>tip;
        cin>>seriski;
        cin >> godina;
        cin >> cena;
        Gitara g(tip,seriski, godina,cena);
		cout<<g.getTip()<<endl;
		cout<<g.getSeriski()<<endl;
		cout<<g.getGodina()<<endl;
		cout<<g.getNabavna()<<endl;
    } else if(testCase == 2){
        cout << "===== Testiranje na klasata Magacin so metodot print() ======" << endl;
		Magacin kb("Magacin1","Lokacija1");
        kb.pecati(false);
	}
    else if(testCase == 3) {
        cout << "===== Testiranje na klasata Magacin so metodot dodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2005);
		cin>>n;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;
                Gitara g(tip,seriski, godina,cena);
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
    }

    else if(testCase == 4) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2012);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(false);
        kb.prodadi(brisi);
        kb.pecati(false);
    }
    else if(testCase == 5) {
        cout << "===== Testiranje na klasata Magacin so metodot prodadi() i pecati(true) ======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
                cout<<"gitara dodadi"<<endl;
				kb.dodadi(g);
			}
        kb.pecati(true);
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        Magacin kb3;
        kb3=kb;
        kb3.pecati(true);
    }
   else if(testCase ==6)
        {
        cout << "===== Testiranje na klasata Magacin so metodot vrednost()======" << endl;
        Magacin kb("Magacin1","Lokacija1",2011);
            cin>>n;
            Gitara brisi;
			for (int i=0;i<n;i++){
                cin>>tip;
                cin>>seriski;
                cin >> godina;
                cin >> cena;

                Gitara g(tip,seriski, godina,cena);
                if(i==2)
                    brisi=g;
				kb.dodadi(g);
			}
        cout<<kb.vrednost()<<endl;
        kb.prodadi(brisi);
        cout<<"Po brisenje:"<<endl;
        cout<<kb.vrednost();
        Magacin kb3;
        kb3=kb;
        }
    return 0;
}