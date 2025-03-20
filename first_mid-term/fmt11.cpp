#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class Ucesnik {
private:
	char *name;
	bool gender;
	int age;
	void copy(const Ucesnik &u) {
		name = new char[strlen(u.name) + 1];
		strcpy(name, u.name);
		gender = u.gender;
		age = u.age;
	}
public:
	int getAge() {
		return age;
	}
	Ucesnik(const char *name="", bool gender=false, int age=18) {
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->gender = gender;
		this->age = age;
	}
	Ucesnik(const Ucesnik &u) {
		copy(u);
	}
	Ucesnik &operator=(const Ucesnik &u) {
		if (this != &u) {
			delete [] name;
			copy(u);
		}
		return *this;
	}
	~Ucesnik() {
		delete [] name;
	}
	bool operator>(const Ucesnik &u) {
		return age > u.age;
	}
	friend ostream &operator<<(ostream &os, const Ucesnik &u) {
		os<<u.name<<endl;
		if (u.gender==true) {
			os<<"mashki"<<endl;
		}else {
			os<<"zhenski"<<endl;
		}
		os<<u.age<<endl;
		return os;
	}
};
class Maraton {
private:
	char location[100];
	Ucesnik *ucesnici;
	int n;
	void copy(const Maraton &m) {
		strcpy(location, m.location);
		n = m.n;
		ucesnici=new Ucesnik[m.n];
		for (int i=0;i<m.n;i++) {
			ucesnici[i]=m.ucesnici[i];
		}
	}
public:
	Maraton(const char *location="") {
		strcpy(this->location, location);
		this->n=0;
		ucesnici=nullptr;
	}
	Maraton(const Maraton &m) {
		copy(m);
	}
	Maraton &operator=(const Maraton &m) {
		if (this != &m) {
			delete [] ucesnici;
			copy(m);
		}
		return *this;
	}
	~Maraton() {
		delete [] ucesnici;
	}
	Maraton &operator+=(Ucesnik &u) {
		Ucesnik *new_u=new Ucesnik[n+1];
		for (int i=0;i<n;i++) {
			new_u[i]=ucesnici[i];
		}
		new_u[n]=u;
		delete [] ucesnici;
		ucesnici=new_u;
		n++;
		return *this;
	}
	double prosecnoVozrast() {
		int total_age=0;
		for (int i=0;i<n;i++) {
			total_age+=ucesnici[i].getAge();
		}
		return (double)total_age/(double)n;
	}
	void pecatiPomladi(Ucesnik &u) {
		for (int i=0;i<n;i++) {
			if (u>ucesnici[i]) {
				cout<<ucesnici[i];
			}
		}
	}
};
int main() {
	char ime[100];
	bool maski;
	int vozrast, n;
	cin >> n;
	char lokacija[100];
	cin >> lokacija;
	Maraton m(lokacija);
	Ucesnik **u = new Ucesnik*[n];
	for(int i = 0; i < n; ++i) {
		cin >> ime >> maski >> vozrast;
		u[i] = new Ucesnik(ime, maski, vozrast);
		m += *u[i];
	}
	m.pecatiPomladi(*u[n - 1]);
	cout << m.prosecnoVozrast() << endl;
	for(int i = 0; i < n; ++i) {
		delete u[i];
	}
	delete [] u;
	return 0;
}
