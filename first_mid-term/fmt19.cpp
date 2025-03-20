#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class IceCream {
private:
    char *name;
    char ingredients[100];
    double price;
    int discount;
    void copy(const IceCream &i) {
        name=new char[strlen(i.name)+1];
        strcpy(name,i.name);
        strcpy(ingredients,i.ingredients);
        price=i.price;
        discount=i.discount;
    }
public:
    IceCream(const char *name="", const char *ingredients="", double price=0.0) {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->price=price;
        this->discount=0;
    }
    IceCream(const IceCream &i) {
        copy(i);
    }
    IceCream& operator=(const IceCream &i) {
        if (this!=&i) {
            delete[] name;
            copy(i);
        }
        return *this;
    }
    ~IceCream() {
        delete[] name;
    }
    friend ostream &operator<<(ostream &os, const IceCream &i) {
        os<<i.name<<": "<<i.ingredients<<" "<<i.price;
        if (i.discount) {
            os<<" ("<<i.price*(100-i.discount)/100.0<<")";
        }
        return os;
    }
    IceCream &operator++(){
        discount+=5;
        return *this;
    }
    IceCream operator+(const char *znaci){
        char *new_name=new char[strlen(name)+strlen(znaci)+4];
        strcat(new_name,name);
        strcat(new_name," + ");
        strcat(new_name,znaci);
        IceCream new_i(new_name,ingredients,price+10);
        new_i.setDiscount(discount);
        return new_i;
    }
    void setDiscount(int discount) {
        if (discount>=0 && discount<=100) {
            this->discount=discount;
        }
    }
    void setName(const char *name) {
        delete[] this->name;
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
    }
};
class IceCreamShop {
private:
    char name[50];
    IceCream *icecreams;
    int n;
    void copy(const IceCreamShop &ics) {
        strcpy(name,ics.name);
        n=ics.n;
        icecreams=new IceCream[ics.n];
        for (int i=0;i<ics.n;i++) {
            icecreams[i]=ics.icecreams[i];
        }
    }
public:
    IceCreamShop(const char *name="") {
        strcpy(this->name,name);
        n=0;
        icecreams=nullptr;
    }
    IceCreamShop(const IceCreamShop &ics) {
        copy(ics);
    }
    IceCreamShop& operator=(const IceCreamShop &ics) {
        if (this!=&ics) {
            delete[] icecreams;
            copy(ics);
        }
        return *this;
    }
    ~IceCreamShop() {
        delete[] icecreams;
    }
    IceCreamShop &operator+=(const IceCream &ic) {
        IceCream *new_ic=new IceCream[n+1];
        for (int i=0;i<n;i++) {
            new_ic[i]=icecreams[i];
        }
        new_ic[n]=ic;
        delete[] icecreams;
        icecreams=new_ic;
        n++;
        return *this;
    }
    friend ostream &operator<<(ostream &os, const IceCreamShop &ics) {
        os<<ics.name<<endl;
        for (int i=0;i<ics.n;i++) {
            os<<ics.icecreams[i]<<endl;
        }
        return os;
    }
};
int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;

        cin >> discount;
        ic1.setDiscount(discount);


    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}
