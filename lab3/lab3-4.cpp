#include <iostream>
#include <cstring>
using namespace std;
class Tour;
class Agency;
class Tour {
private:
    char destination[101];
    int duration;
    double price;
    static int TOTAL_TOURS;
    int passengers;
public:
    friend class Agency;
    friend void findBestAgency(Agency *a, int n);
    static int getNumTours() {
        return TOTAL_TOURS;
    }
    Tour(const char *destination="", int duration=0, double price=0.0, int passengers=0) {
        strcpy(this->destination, destination);
        this->duration = duration;
        this->price = price;
        this->passengers = passengers;
        TOTAL_TOURS++;
    }
    Tour(const Tour &t) {
        strcpy(this->destination, t.destination);
        this->duration = t.duration;
        this->price = t.price;
        this->passengers = t.passengers;
        TOTAL_TOURS++;
    }
    double profitByTour() const {
        return 1.0*passengers*price;
    }
    void display() const {
        cout<<"Destination: "<<destination<<", Duration: "<<duration<<" days, Price: "<<price<<", Passengers: "<<passengers<<endl;
    }
    static void RESET(){
        TOTAL_TOURS=0;
    }
};
int Tour::TOTAL_TOURS = -100;
class Agency {
private:
    char name[101];
    Tour tours[10];
    int n;
public:
    friend void findBestAgency(Agency *a, int n);
    void setName(const char *name) {
        strcpy(this->name, name);
    }
    Agency(const char *name="") {
        strcpy(this->name, name);
        n=0;
    }
    void display() const {
        cout<<"Travel Agency: "<<name<<endl;
        for (int i=0;i<n;i++) {
            tours[i].display();
        }
    }
    void addTour(Tour tour) { //nema inkrement na total tours bidejki tuka se vrshi samo dodavanje na el. vo niza, NE SAMOTO KREIRANJE !!!
        if (n<10) {
            tours[n++]=tour;
        }
    }
};
void findBestAgency(Agency *a, int n) {
    int best=0; //index for the best one
    double max=0.0,current=0.0;
    for (int i=0;i<n;i++) {
        current=0.0;
        for (int j=0;j<a[i].n;j++) {
            current+=a[i].tours[j].profitByTour();
        }
        if (current>max) {
            max=current;
            best=i;
        }
    }
    a[best].display();
}
int main() {


    int test_case_n;

    char name[50];
    char dest[50];
    int dur;
    double pr;
    int pass;

    cin>>test_case_n;

    if (test_case_n == 0) {
        cout << "Testing Tour c-tors, display function:"<<endl;
        cin >> dest >> dur >> pr >> pass;
        Tour t1 = Tour(dest, dur, pr, pass);
        Tour t2 = Tour(t1);
        t1.display();
        t2.display();
    } else if (test_case_n == 1) {
        Tour::RESET();
        cout << "Testing Tour profitByTour function:"<<endl;
        cin >> dest >> dur >> pr >> pass;
        Tour t1 = Tour(dest, dur, pr, pass);
        cout<<t1.profitByTour()<<endl;
    } else if (test_case_n == 2) {
        Tour::RESET();
        cout << "Testing Agency c-tor, display function:"<<endl;

        Agency agency;

        cin>>name;
        agency.setName(name);
        int numTours;
        cin>>numTours;
        for (int j = 0; j < numTours; ++j) {
            cin>>dest>>dur>>pr>>pass;
            agency.addTour(Tour(dest, dur, pr, pass));
        }

        agency.display();


    } else if (test_case_n == 3) {
        Tour::RESET();
        cout << "Testing static field in Tour:" <<endl;

        Agency agency [10];
        int n;
        cin >> n;

        for (int i = 0; i < n ; ++i) {
            cin>>name;
            agency[i].setName(name);
            int numTours;
            cin>>numTours;
            for (int j = 0; j < numTours; ++j) {
                cin>>dest>>dur>>pr>>pass;
                agency[i].addTour(Tour(dest, dur, pr, pass));


            }

        }

        cout<<"Total number of tours: "<<Tour::getNumTours()<<endl;



    } else if (test_case_n == 4) {
        Tour::RESET();
        Agency agency [10];
        int n;
        cin >> n;

        for (int i = 0; i < n ; ++i) {
            cin>>name;
            agency[i].setName(name);
            int numTours;
            cin>>numTours;
            for (int j = 0; j < numTours; ++j) {
                cin>>dest>>dur>>pr>>pass;
                agency[i].addTour(Tour(dest, dur, pr, pass));
            }
        }

        findBestAgency(agency, n);
    }


    return 0;

}
