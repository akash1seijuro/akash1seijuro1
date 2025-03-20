#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class StockRecord {
private:
    char id[12];
    char name[50];
    float og_price;
    float current_price;
    int actions;
public:
    StockRecord(const char *id="", const char *name="", float og_price=0, int actions=0) {
        strcpy(this->id, id);
        strcpy(this->name, name);
        this->og_price = og_price;
        this->actions = actions;
    }
    void setNewPrice(double c) {
        current_price = c;
    }
    double value() {
        return actions*current_price;
    }
    double profit() const{
        return actions*(current_price-og_price);
    }
    friend ostream &operator<<(ostream &out, const StockRecord &s) {
        out<<s.name<<" "<<s.actions<<" "<<s.og_price<<" "<<s.current_price<<" "<<s.profit()<<endl;
        return out;
    }
};
class Client {
private:
    char name[60];
    int id;
    StockRecord *stocks;
    int n;
    void copy(const Client &c) {
        strcpy(name, c.name);
        id = c.id;
        n = c.n;
        stocks = new StockRecord[c.n];
        for (int i = 0; i < c.n; i++) {
            stocks[i]= c.stocks[i];
        }
    }
public:
    Client(const char *name="", int id=000000) {
        strcpy(this->name, name);
        this->id = id;
        n=0;
        stocks=nullptr;
    }
    Client(const Client &c) {
        copy(c);
    }
    Client &operator=(const Client &c) {
        if (this!=&c) {
            delete [] stocks;
            copy(c);
        }
        return *this;
    }
    ~Client() {
        delete [] stocks;
    }
    double totalValue() const{
        double total=0.0;
        for (int i = 0; i < n; i++) {
            total+=stocks[i].value();
        }
        return total;
    }
    Client &operator+=(StockRecord &s) {
        StockRecord *new_s = new StockRecord[n+1];
        for (int i=0;i<n;i++) {
            new_s[i] = stocks[i];
        }
        new_s[n]=s;
        delete [] stocks;
        stocks=new_s;
        n++;
        return *this;
    }
    friend ostream &operator<<(ostream &out, const Client &c) {
        out<<c.id<<" "<<c.totalValue()<<endl;
        for (int i=0;i<c.n;i++) {
            out<<c.stocks[i];
        }
        return out;
    }
};
int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}
