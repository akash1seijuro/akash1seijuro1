#include <iostream>
#include <cstring>
using namespace std;
class Scholarship;
class Student;
class Student {
private:
    char name[51];
    char surname[51];
    char faculty[51];
    float gpa;
    static int ALL;
    static int FINKASHI;
public:
    friend class Scholarship;
    friend void studentsWithScholarship(Scholarship &s, int n);
    Student(const char *name="", const char *surname="", const char *faculty="", float gpa=0) {
        strcpy(this->name, name);
        strcpy(this->surname, surname);
        strcpy(this->faculty, faculty);
        this->gpa = gpa;
        ALL++;
        if (strcmp(faculty,"FINKI")==0 && gpa>9.0) {
            FINKASHI++;
        }
    }
    ~Student(){}
    bool finkiStudent() const{
        return (strcmp(faculty,"FINKI")==0 && gpa>9.0);
    }
    void print() const{
        cout<<name<<" "<<surname<<" "<<faculty<<" "<<gpa<<endl;
    }
};
int Student::ALL = 0;
int Student::FINKASHI = 0;
class Scholarship {
private:
    char name[51];
    Student students[100];
    int n;
    static float GPA; //zbir od site proseci na FINKASHI samo !!!
public:
    friend void studentsWithScholarship(Scholarship &s, int n);
    Scholarship(const char *name="") {
        strcpy(this->name, name);
        n=0;
    }
    ~Scholarship(){}
    void addStudent(const Student &s) {
        if (n<100) {
            students[n++]=s;
            if (s.finkiStudent()) {
                GPA+=s.gpa;
            }
        }
    }
    void print() const {
        cout<<"Scholarship name: "<<name<<", total applicants: "<<n<<endl;
    }
};
float Scholarship::GPA = 0.0;
void studentsWithScholarship(Scholarship &s, int n) {
    for (int i=0;i<n;i++) {
        for (int j=0;j<n-1-i;j++) {
            if (s.students[j].gpa<s.students[j+1].gpa) {
                swap(s.students[j],s.students[j+1]);
            }
        }
    }
    cout<<"FINKI students with a scholarship"<<endl;
    int count=0;
    for (int i=0;i<n;i++) {
        if (s.students[i].finkiStudent() && count<3) {
            count++;
            s.students[i].print();
        }
    }
    cout<<"Scholarship data shows that "<<Student::FINKASHI*100.0/n<<"% of applicants are from FINKI, with an average grade of "<<Scholarship::GPA/Student::FINKASHI*1.0<<endl;
}
int main() {
    char name[50], surname[50], faculty[50], scholarship_name[50];
    float average_grade;
    int n,case_;
    cin>>case_;
    if (case_ == 0)
        //Testing Student constructor
    {
        cout<<"--Testing finkiStudent method--"<<endl;
        Student s("Ana", "Denkova", "BAS", 9.89);
        cout<<s.finkiStudent();
    }
    else if (case_==1){
        //Testing addStudent and print method
        cout<<"--Testing addStudent and print method--"<<endl;
        Scholarship sc("ITCompany");
        Student s("Ana", "Denkova", "BAS", 9.89);
        sc.addStudent(s);
        sc.print();
    }
    else if (case_ == 2){
        cin>>scholarship_name;
        Scholarship sc(scholarship_name);
        cin>>n;
        for(int i=0; i<n; i++)
        {
            cin>>name>>surname>>faculty>>average_grade;
            Student s = Student(name, surname, faculty, average_grade);
            sc.addStudent(s);
        }
        sc.print();
        studentsWithScholarship(sc,n);
    }
    return 0;
}