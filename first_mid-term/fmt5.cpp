#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Gitara {
	char id[25];
	float price;
	int year;
	char type[40];
public:
	char *getTip() {
		return type;
	}
	float getNabavna() const{
		return price;
	}
	int getGodina() const{
		return year;
	}
	char *getSeriski() {
		return id;
	}
	Gitara(const char *type="", const char *id="", int year=1900, float price=0) {
		strcpy(this->id, id);
		this->price = price;
		this->year = year;
		strcpy(this->type, type);
	}
	bool daliIsti(Gitara g) {
		return (strcmp(g.id, id) == 0);
	}
	void pecati() {
		cout<<id<<" "<<type<<" "<<price<<endl;
	}
};
class Magacin {
private:
	char name[30];
	char location[60];
	Gitara *gitari;
	int n;
	int year;
public:
	Magacin(const char *name="", const char *location="", int year=1900) {
		strcpy(this->name, name);
		strcpy(this->location, location);
		this->year = year;
		n=0;
		gitari=nullptr;
	}
	double vrednost() {
		double total=0.0;
		for (int i=0;i<n;i++) {
			total+=gitari[i].getNabavna();
		}
		return total;
	}
	void dodadi(Gitara d) {
		Gitara *new_gitari=new Gitara[n+1];
		for (int i=0;i<n;i++) {
			new_gitari[i]=gitari[i];
		}
		new_gitari[n]=d;
		delete [] gitari;
		gitari=new_gitari;
		n++;
	}
	void prodadi(Gitara p) {
		int k=0;
		int counter=0;
		for (int i=0;i<n;i++) {
			if (gitari[i].daliIsti(p)) {
				counter++;
			}
		}
		if (counter==0) {
			return;
		}
		Gitara *new_gitari=new Gitara[n-counter];
		for (int i=0;i<n;i++) {
			if (!(gitari[i].daliIsti(p))) {
				new_gitari[k++]=gitari[i];
			}
		}
		delete [] gitari;
		gitari=new_gitari;
		n-=counter;
	}
	void pecati(bool daliNovi) {
		cout<<name<<" "<<location<<endl;
		if (daliNovi==true) {
			for (int i=0;i<n;i++) {
				if (gitari[i].getGodina()>year) {
					gitari[i].pecati();
				}
			}
		}else {
			for (int i=0;i<n;i++) {
				gitari[i].pecati();
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
