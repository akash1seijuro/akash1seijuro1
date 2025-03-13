#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;
class IceCream {
private:
    char *name;
    char content[100];
    double price;
    int offer=0;
    void copy(const IceCream &other) {
        this->name=new char[strlen(other.name)+1];
        strcpy(this->name,other.name);
        this->offer=other.offer;
        this->price=other.price;
        strcpy(this->content,other.content);
    }
public:
    IceCream(const char*name="", const char *content="", double price=0.0) {
        this->name=new char[strlen(name)+1];
        strcpy(this->name,name);
        strcpy(this->content,content);
        this->price=price;
        this->offer=0;
    }
    IceCream(const IceCream &other) {
        copy(other);
    }
    IceCream& operator=(const IceCream &other) {
        if (this != &other) {
            delete [] name;
            copy(other);
        }
        return *this;
    }
    ~IceCream() {
        delete [] name;
    }
    friend ostream &operator<<(ostream &out, const IceCream &ic) {
        out<<ic.name<<": "<<ic.content<<" "<<ic.price;
        if (ic.offer>0) {
            out<<" ("<<ic.price*(100-ic.offer)/100.00<<")";
        }
        return out;
    }
    IceCream& operator++() {
        offer+=5;
        return *this;
    }
    IceCream& operator+(const char *added_name) {
        char *new_name = new char[strlen(name)+strlen(added_name)+4]; //3 za " + " i 1 za null terminatorot
        strcpy(new_name,name);
        strcat(new_name," + ");
        strcat(new_name,added_name);
        delete [] name;
        name=new_name;
        price+=10;
        return *this;
    }
    void setDiscount(int discount) {
        offer=discount;
    }
    void setName(const char *name) {
        strcpy(this->name,name);
    }
};
class IceCreamShop {
private:
    char name[50];
    IceCream *ic;
    int n;
    void copy(const IceCreamShop &other) {
        strcpy(name,other.name);
        this->n=other.n;
        this->ic=new IceCream[other.n];
        for (int i = 0; i < other.n; i++) {
            this->ic[i]=other.ic[i];
        }

    }
public:
    IceCreamShop(const char*name="") {
        strcpy(this->name,name);
        this->n=0;
        this->ic = new IceCream[this->n];
    }
    IceCreamShop(const IceCreamShop &other) {
        copy(other);
    }
    IceCreamShop& operator=(const IceCreamShop &other) {
        if (this != &other) {
            delete [] this->ic;
            copy(other);
        }
        return *this;
    }
    ~IceCreamShop() {
        delete [] this->ic;
    }
    friend ostream &operator<<(ostream &out, const IceCreamShop &ic) {
        out<<ic.name<<endl;
        for (int i = 0; i < ic.n; i++) {
            out<<ic.ic[i]<<endl;
        }
        return out;
    }
    IceCreamShop& operator+=(IceCream &ic) {
        IceCream *new_ic=new IceCream[this->n+1];
        for (int i = 0; i < this->n; i++) {
            new_ic[i]=this->ic[i];
        }
        new_ic[this->n]=ic;
        delete [] this->ic;
        this->ic=new_ic;
        this->n++;
        return *this;
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