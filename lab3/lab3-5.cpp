#include <iostream>
#include <cstring>
using namespace std;
class UserProfile;
class Achievement;
class Achievement {
private:
    char name[51];
    char description[101];
    static int TOTAL_USER_ACHIEVEMENTS;
public:
    friend class UserProfile;
    friend void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m);
    bool isEqual(const Achievement &a) {
        return strcmp(name, a.name) == 0 && strcmp(description, a.description) == 0;
    }
    Achievement(const char *name="", const char *description="") {
        strcpy(this->name, name);
        strcpy(this->description, description);
        TOTAL_USER_ACHIEVEMENTS++;
    }
    Achievement(const Achievement &a) {
        strcpy(this->name, a.name);
        strcpy(this->description, a.description);
        TOTAL_USER_ACHIEVEMENTS++;
    }
    void print() {
        cout<<name<<endl<<description<<endl;
    }
    static void incrementTotalUserAchievements() {
        TOTAL_USER_ACHIEVEMENTS++;
    }
};
int Achievement::TOTAL_USER_ACHIEVEMENTS = 0;
class UserProfile {
private:
    char name[51];
    Achievement a[50];
    int n;
public:
    friend void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m);
    UserProfile(const char *name="") {
        strcpy(this->name, name);
        n=0;
    }
    void print() {
        cout<<"User: "<<name<<endl;
        cout<<"Achievements:"<<endl;
        for (int i=0;i<n;i++) {
            a[i].print();
        }
    }
    void addAchievement(const Achievement &aa) {
        if (n<50) {
            a[n++]=aa;
            Achievement::incrementTotalUserAchievements();
        }
    }
};
void showAchievementsProgress(UserProfile profiles[], int n, Achievement achievements[], int m) {
    //za sekoj achiev. kje pechati ime i opis negovo i procentot na korisinci koi go dobile toa
    double total=0.0;
    int c=0;
    for (int i=0;i<m;i++) {
        achievements[i].print();
        cout<<"---Percentage of users who have this achievement: ";
        c=0;
        for (int j=0;j<n;j++) {
            for (int k=0;k<profiles[j].n;k++) {
                if (profiles[j].a[k].isEqual(achievements[i])) {
                    c++;
                    break;
                }
            }
        }
        total+=double(c)/n;
        cout<<double(c)*100/n<<"%"<<endl;
    }
    cout<<"------Average completion rate of the game: "<<total*100.0/m<<"%"<<endl;
}
int main() {
    char testcase[100];
    cin.getline(testcase, 100);

    int n;
    cin >> n;
    cin.ignore();

    char ignore[100];
    cin.getline(ignore, 100);
    UserProfile users[100];
    for (int i = 0; i < n; ++i) {
        char name[100];
        cin >> name;
        users[i] = UserProfile(name);
    }

    int m;
    cin >> m;
    cin.ignore();

    cin.getline(ignore, 100);
    Achievement achievements[100];
    for (int i = 0; i < m; ++i) {
        char name[100], description[100];
        cin.getline(name, 100);
        cin.getline(description, 100);
        achievements[i] = Achievement(name, description);
    }

    int k;
    cin >> k;
    cin.ignore();

    cin.getline(ignore, 100);
    for (int i = 0; i < k; ++i) {
        int numUser, numAchievement;
        cin >> numUser >> numAchievement;
        numUser -= 1;
        numAchievement -= 1;
        users[numUser].addAchievement(achievements[numAchievement]);
    }

    if (testcase[8] == 'A') {  // Testing Achievement methods.
        for (int i = 0; i < m; ++i) {
            achievements[i].print();
        }
        Achievement::incrementTotalUserAchievements();
    } else if (testcase[8] == 'U') {  // Testing UserProfile methods.
        for (int i = 0; i < n; ++i) {
            users[i].print();
        }
    } else {  // Testing showAchievementsProgress function.
        showAchievementsProgress(users, n, achievements, m);
    }

    return 0;
}