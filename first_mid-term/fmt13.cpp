#include <iostream>
#include <cstring>
using namespace std;
class Zichara {
    char *mesto;
    int cenaDnevna;
public:
    Zichara(const char *mesto = "", int cenaDnevna = 0) {
        this->mesto = new char[strlen(mesto) + 1];
        strcpy(this->mesto, mesto);
        this->cenaDnevna = cenaDnevna;
    }
    Zichara(const Zichara &z) {
        this->mesto = new char[strlen(z.mesto) + 1];
        strcpy(this->mesto, z.mesto);
        this->cenaDnevna = z.cenaDnevna;
    }
    Zichara &operator=(const Zichara &z) {
        if (this != &z) {
            delete[] mesto;
            this->mesto = new char[strlen(z.mesto) + 1];
            strcpy(this->mesto, z.mesto);
            this->cenaDnevna = z.cenaDnevna;
        }
        return *this;
    }
    ~Zichara() {
        delete[] mesto;
    }
    int getCena() const {
        return cenaDnevna;
    }
};
class PlaninarskiDom {
    char name[15];
    int ceni[2];
    char cls;
    bool daliZichara;
    Zichara *zichara;
public:
    PlaninarskiDom(const char *name = "", int *ceni = nullptr, char cls = 'F') {
        strncpy(this->name, name, 14);
        this->name[14] = '\0';
        this->cls = cls;
        this->daliZichara = false;
        this->zichara = nullptr;
        if (ceni) {
            this->ceni[0] = ceni[0];
            this->ceni[1] = ceni[1];
        } else {
            this->ceni[0] = this->ceni[1] = 0;
        }
    }
    PlaninarskiDom(const PlaninarskiDom &p) {
        strcpy(this->name, p.name);
        this->cls = p.cls;
        this->ceni[0] = p.ceni[0];
        this->ceni[1] = p.ceni[1];
        this->daliZichara = p.daliZichara;
        if (p.zichara) {
            this->zichara = new Zichara(*p.zichara);
        } else {
            this->zichara = nullptr;
        }
    }
    PlaninarskiDom &operator=(const PlaninarskiDom &p) {
        if (this != &p) {
            strcpy(this->name, p.name);
            this->cls = p.cls;
            this->ceni[0] = p.ceni[0];
            this->ceni[1] = p.ceni[1];
            this->daliZichara = p.daliZichara;
            delete zichara;
            if (p.zichara) {
                this->zichara = new Zichara(*p.zichara);
            } else {
                this->zichara = nullptr;
            }
        }
        return *this;
    }
    ~PlaninarskiDom() {
        delete zichara;
    }
    PlaninarskiDom &operator--() {
        if (cls < 'F') {
            cls++;
        }
        return *this;
    }
    friend ostream &operator<<(ostream &out, const PlaninarskiDom &p) {
        out << p.name << " klasa:" << p.cls;
        if (p.daliZichara) {
            out << " so Zichara";
        }
        out << endl;
        return out;
    }
    bool operator<=(char c) const {
        return cls >= c;
    }
    void setZichara(const Zichara &z) {
        delete zichara;
        zichara = new Zichara(z);
        daliZichara = true;
    }
    void presmetajDnevenPrestoj(int den, int mesec, int &cena) {
        if (mesec < 1 || mesec > 12 || den < 1 || den > 31) {
            throw 1;
        }
        int sezona = (mesec >= 4 && mesec <= 9) ? 0 : 1;
        cena = ceni[sezona];
        if (daliZichara) {
            cena += zichara->getCena();
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
