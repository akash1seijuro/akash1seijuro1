#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Zichara {
private:
	char *location;
	int price;
	void copy(const Zichara &zichara) {
		location = new char[strlen(zichara.location) + 1];
		strcpy(location, zichara.location);
		price = zichara.price;
	}
public:
	int getPrice() const{
		return price;
	}
	Zichara(const char *location="", int price=0) {
		this->location = new char[strlen(location) + 1];
		strcpy(this->location, location);
		this->price = price;
	}
	Zichara(const Zichara &zichara) {
		copy(zichara);
	}
	Zichara &operator=(const Zichara &zichara) {
		if (this != &zichara) {
			delete [] location;
			copy(zichara);
		}
		return *this;
	}
	~Zichara() {
		delete [] location;
	}
};
class PlaninarskiDom {
private:
	char name[15];
	int prices[2];
	char cls;
	bool valid;
	Zichara *zichara;
	void copy(const PlaninarskiDom &plan) {
		strcpy(name, plan.name);
		for (int i=0;i<2;i++) {
			prices[i] = plan.prices[i];
		}
		cls = plan.cls;
		valid = plan.valid;
		if (plan.zichara) { //ako postoi vo copy-construktorot
			this->zichara=new Zichara(*plan.zichara);
		}else {
			this->zichara=nullptr;
		}
	}
public:
	void setZichara(const Zichara &zichara) {
		delete this->zichara;
		this->zichara = new Zichara(zichara); //copy-constructor called
		valid = true; //deka postoi zhicharata vo domot
	}
	PlaninarskiDom(const char *name="", int *prices=nullptr, char cls=' ') {
		strcpy(this->name, name);
		if (prices!=nullptr) {
			for (int i=0;i<2;i++) {
				this->prices[i]=prices[i];
			}
		}else {
			for (int i=0;i<2;i++) {
				this->prices[i]=0;
			}
		}
		this->cls = cls;
		valid = false;
		zichara=nullptr;
	}
	PlaninarskiDom(const PlaninarskiDom &plan) {
		copy(plan);
	}
	PlaninarskiDom &operator=(const PlaninarskiDom &plan) {
		if (this != &plan) {
			delete this->zichara;
			copy(plan);
		}
		return *this;
	}
	~PlaninarskiDom() {
		delete this->zichara;
	}
	PlaninarskiDom &operator--() {
		if (cls>='A' && cls<='E') {
			cls++;
			return *this;
		}
		return *this;
	}
	friend ostream &operator<<(ostream &os, const PlaninarskiDom &plan) {
		os<<plan.name<<" klasa:"<<plan.cls;
		if (plan.valid) {
			os<<" so Zichara"<<endl;
		}else {
			os<<endl;
		}
		return os;
	}
	bool operator<=(const char znak) const{
		return cls>=znak;
	}
	void presmetajDnevenPrestoj(int day, int month, int &total) {
		if (day<1 || day>31 || month<1 || month>12) {
			throw 1;
		}
		total=0;
		if (month>=4 && month<=9) {
			total+=prices[0];
		}else {
			total+=prices[1];
		}
		if (valid) {
			total+=zichara->getPrice();
		}
	}
};
int main(){

	PlaninarskiDom p; //креирање на нов објект од класата планинарски дом

	//во следниот дел се вчитуваат информации за планинарскиот дом
	char imePlaninarskiDom[15],mestoZichara[30],klasa;
	int ceni[12];
	int dnevnakartaZichara;
	bool daliZichara;
	cin>>imePlaninarskiDom;
	for (int i=0;i<2;i++) cin>>ceni[i];
	cin>>klasa;
	cin>>daliZichara;

	//во следниот дел се внесуваат информации и за жичарата ако постои
	if (daliZichara) {
		cin>>mestoZichara>>dnevnakartaZichara;
		PlaninarskiDom pom(imePlaninarskiDom,ceni,klasa);
		Zichara r(mestoZichara,dnevnakartaZichara);
		pom.setZichara(r);
		p=pom;
	}
	else{
		PlaninarskiDom *pok=new PlaninarskiDom(imePlaninarskiDom,ceni,klasa);
		p=*pok;
	}

	//се намалува класата на планинарскиот дом за 2
	--p;
	--p;

	int cena;
	int den,mesec;
	cin>>den>>mesec;
	try{
		p.presmetajDnevenPrestoj(den,mesec,cena); //тука се користи функцијата presmetajDnevenPrestoj
		cout<<"Informacii za PlaninarskiDomot:"<<endl;
		cout<<p;
		if (p<='D')
			cout<<"Planinarskiot dom za koj se vneseni informaciite ima klasa poniska ili ista so D\n";

		cout<<"Cenata za "<<den<<"."<<mesec<<" e "<<cena; //се печати цената за дадениот ден и месец
	}
	catch (int){
		cout<<"Mesecot ili denot e greshno vnesen!";
	}
}
