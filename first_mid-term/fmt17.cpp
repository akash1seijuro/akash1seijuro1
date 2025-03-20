#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
enum Tip {
	LINUX=0,UNIX,WINDOWS
};
class OperativenSistem {
private:
	char *name;
	float version;
	Tip tip;
	float size;
	void copy(const OperativenSistem &os) {
		this->name=new char[strlen(os.name)+1];
		strcpy(this->name,os.name);
		this->version=os.version;
		this->tip=os.tip;
		this->size=os.size;
	}
public:
	OperativenSistem(const char *name="", float version=0, Tip tip=LINUX, float size=0) {
		this->name=new char[strlen(name)+1];
		strcpy(this->name,name);
		this->version=version;
		this->tip=tip;
		this->size=size;
	}
	OperativenSistem(const OperativenSistem &os) {
		copy(os);
	}
	OperativenSistem &operator=(const OperativenSistem &os) {
		if (this!=&os) {
			delete [] this->name;
			copy(os);
		}
		return *this;
	}
	~OperativenSistem() {
		delete [] this->name;
	}
	void pecati() {
		cout<<"Ime: "<<this->name<<" Verzija: "<<this->version<<" Tip: "<<this->tip<<" Golemina:"<<this->size<<"GB"<<endl;
	}
	bool ednakviSe(const OperativenSistem &os) {
		return (strcmp(this->name,os.name)==0 && this->tip==os.tip && this->size==os.size && this->version==os.version);
	}
	int sporediVerzija(const OperativenSistem &os) {
		if (version>os.version) {
			return 1;
		}else if (version<os.version) {
			return -1;
		}else {
			return 0;
		}
	}
	bool istaFamilija(const OperativenSistem &os) {
		return (strcmp(this->name,os.name)==0 && this->tip==os.tip);
	}
};
class Repozitorium {
private:
	char name[20];
	OperativenSistem *os;
	int n;
public:
	Repozitorium(const char *name="") {
		strcpy(this->name,name);
		this->n=0;
		os=nullptr;
	}
	~Repozitorium() {
		delete [] this->os;
	}
	void pecatiOperativniSistemi() {
		cout<<"Repozitorium: "<<name<<endl;
		for (int i=0;i<n;i++) {
			os[i].pecati();
		}
	}
	void izbrishi(const OperativenSistem &oss) {
		int k=0;
		int count=0;
		for (int i=0;i<n;i++) {
			if (os[i].ednakviSe(oss)) {
				count++;
			}
		}
		OperativenSistem *new_os=new OperativenSistem[n-count];
		for (int i=0;i<n;i++) {
			if (!(os[i].ednakviSe(oss))) {
				new_os[k++]=os[i];
			}
		}
		delete [] os;
		os=new_os;
		n-=count;
	}
	void dodadi(const OperativenSistem &oss) {
		for (int i=0;i<n;i++) {
			if (os[i].istaFamilija(oss) && os[i].sporediVerzija(oss)==-1) {
				os[i]=oss;
				return;
			}
		}
		OperativenSistem *new_os=new OperativenSistem[n+1];
		for (int i=0;i<n;i++) {
			new_os[i]=os[i];
		}
		new_os[n]=oss;
		delete [] os;
		os=new_os;
		n++;
	}
};
int main() {
	char repoName[20];
	cin>>repoName;
	Repozitorium repozitorium=Repozitorium(repoName);
	int brojOperativniSistemi = 0;
	cin>>brojOperativniSistemi;
	char ime[20];
	float verzija;
	int tip;
	float golemina;
	for (int i = 0; i<brojOperativniSistemi; i++){
		cin>>ime;
		cin>>verzija;
		cin>>tip;
		cin>>golemina;
		OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
		repozitorium.dodadi(os);
	}

	repozitorium.pecatiOperativniSistemi();
	cin>>ime;
	cin>>verzija;
	cin>>tip;
	cin>>golemina;
	OperativenSistem os = OperativenSistem(ime, verzija, (Tip)tip, golemina);
	cout<<"=====Brishenje na operativen sistem====="<<endl;
	repozitorium.izbrishi(os);
	repozitorium.pecatiOperativniSistemi();
	return 0;
}
