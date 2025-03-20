#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Pica {
private:
	char name[15];
	int price;
	char *ingredients;
	int discount;
	void copy(const Pica &p) {
		strcpy(name, p.name);
		ingredients=new char[strlen(p.ingredients)+1];
		strcpy(ingredients, p.ingredients);
		price=p.price;
		discount=p.discount;
	}
public:
	int getPrice() const{
		return price;
	}
	int getDiscount() const{
		return discount;
	}
	Pica(const char *name="", int price=0, const char *ingredients="", int discount=0) {
		strcpy(this->name, name);
		this->price=price;
		this->ingredients=new char[strlen(ingredients)+1];
		strcpy(this->ingredients, ingredients);
		this->discount=discount;
	}
	Pica(const Pica &p) {
		copy(p);
	}
	Pica& operator=(const Pica &p) {
		if(this!=&p) {
			delete[] this->ingredients;
			copy(p);
		}
		return *this;
	}
	~Pica() {
		delete[] this->ingredients;
	}
	void pecati() const{
		cout<<name<<" - "<<ingredients<<", "<<price;
	}
	bool istiSe(const Pica &p) const{
		return (strcmp(p.ingredients, this->ingredients)==0);
	}
};
class Picerija {
private:
	char name[15];
	Pica *pici;
	int n;
	void copy(const Picerija &p) {
		strcpy(name, p.name);
		pici=new Pica[p.n];
		n=p.n;
		for(int i=0;i<p.n;i++) {
			pici[i]=p.pici[i];
		}
	}
public:
	void setIme(const char *name) {
		strcpy(this->name, name);
	}
	char *getIme() {
		return this->name;
	}
	Picerija(const char *name="") {
		strcpy(this->name, name);
		this->n=0;
		pici=nullptr;
	}
	Picerija(const Picerija &p) {
		copy(p);
	}
	Picerija& operator=(const Picerija &p) {
		if(this!=&p) {
			delete[] this->pici;
			copy(p);
		}
		return *this;
	}
	~Picerija() {
		delete[] this->pici;
	}
	Picerija &operator+=(const Pica &p) {
		for (int i=0;i<n;i++) {
			if (pici[i].istiSe(p)) {
				return *this;
			}
		}
		Pica *new_pici=new Pica[n+1];
		for (int i=0;i<n;i++) {
			new_pici[i]=pici[i];
		}
		new_pici[n]=p;
		delete [] pici;
		pici=new_pici;
		n++;
		return *this;
	}
	void piciNaPromocija() const{
		for (int i=0;i<n;i++) {
			if (pici[i].getDiscount()>0 && pici[i].getDiscount()<100) {
				pici[i].pecati();
				cout<<" "<<pici[i].getPrice()*(100-pici[i].getDiscount())/100.0;
				cout<<endl;
			}
		}
	}
};
int main() {

	int n;
	char ime[15];
	cin >> ime;
	cin >> n;

	Picerija p1(ime);
	for (int i = 0; i < n; i++){
		char imp[100];
		cin.get();
		cin.getline(imp, 100);
		int cena;
		cin >> cena;
		char sostojki[100];
		cin.get();
		cin.getline(sostojki, 100);
		int popust;
		cin >> popust;
		Pica p(imp, cena, sostojki, popust);
		p1+=p;
	}

	Picerija p2 = p1;
	cin >> ime;
	p2.setIme(ime);
	char imp[100];
	cin.get();
	cin.getline(imp, 100);
	int cena;
	cin >> cena;
	char sostojki[100];
	cin.get();
	cin.getline(sostojki, 100);
	int popust;
	cin >> popust;
	Pica p(imp, cena, sostojki, popust);
	p2+=p;

	cout << p1.getIme() << endl;
	cout << "Pici na promocija:" << endl;
	p1.piciNaPromocija();

	cout << p2.getIme() << endl;
	cout << "Pici na promocija:" << endl;
	p2.piciNaPromocija();

	return 0;
}
