#include <iostream>
#include <cstring>
using namespace std;
class StockRecord {
    char id[12];
    char company_name[50];
    double price_of_actions;
    float current_price;
    int actions_bought;
public:
    StockRecord(const char *id="", const char *company_name="", double price_of_actions=0, int actions_bought=0) {
        strcpy(this->id, id);
        strcpy(this->company_name, company_name);
        this->price_of_actions = price_of_actions;
        this->actions_bought = actions_bought;
    }
    void setNewPrice(double c){
        this->current_price = (double)c;
    }
    float getNewPrice() const{
        return this->current_price;
    }
    float value() const{
        return this->current_price*this->actions_bought;
    }
    float profit() const{
        return 1.0*this->actions_bought*(this->current_price-this->price_of_actions);
    }
    friend ostream &operator<<(ostream &out, const StockRecord &sr) {
        out<<sr.company_name<<" "<<sr.actions_bought<<" "<<sr.price_of_actions<<" "<<sr.current_price<<" "<<sr.profit()<<endl;
        return out;
    }
};
class Client {
    char full_name[60];
    int id;
    StockRecord *stocks;
    int stocks_count;
    void copy(const Client &other) {
        strcpy(this->full_name, other.full_name);
        this->id = other.id;
        this->stocks = new StockRecord[other.stocks_count];
        for (int i = 0; i < other.stocks_count; i++) {
            this->stocks[i] = other.stocks[i];
        }
        this->stocks_count = other.stocks_count;
    }
public:
    Client(const char *full_name="", int id=0) {
        strcpy(this->full_name, full_name);
        this->id = id;
        this->stocks_count=0;
        this->stocks=nullptr;
    }
    Client(const Client &other) {
        copy(other);
    }
    Client &operator=(const Client &other) {
        if (this != &other) {
            delete [] stocks;
            copy(other);
        }
        return *this;
    }
    ~Client() {
        delete [] stocks;
    }
    float totalValue()const{
        float total=0;
        for (int i=0;i<stocks_count;i++) {
            total+=stocks[i].value();
        }
        return total;
    }
    void operator+=(const StockRecord &sr) {
        StockRecord *new_stocks = new StockRecord[stocks_count+1];
        for (int i=0;i<stocks_count;i++) {
            new_stocks[i] = stocks[i];
        }
        new_stocks[stocks_count] = sr;
        delete [] stocks;
        stocks = new_stocks;
        stocks_count++;
    }
    friend ostream &operator<<(ostream &out, const Client &c) {
        out<<c.id<<" "<<c.totalValue()<<endl;
        for (int i=0;i<c.stocks_count;i++) {
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