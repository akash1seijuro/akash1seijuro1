#include <iostream>
using namespace std;
class List {
private:
    int* arr;
    int size;
public:
    int getSize() {
        return size;
    }
    List(int* values, int size) {
        this->size = size;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = values[i];
        }
    }
    List() {
        this->size = 0;
        arr = new int[size];
    }
    List(const List& other) {
        size = other.size;
        arr = new int[size];
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    ~List() {
        delete[] arr;
    }
    List& operator=(const List& other) {
        if (this != &other) {
            delete[] arr;
            size = other.size;
            arr = new int[size];
            for (int i = 0; i < size; i++) {
                arr[i] = other.arr[i];
            }
        }
        return *this;
    }
    void pecati() const {
        cout << size << ": ";
        for (int i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << "sum: " << sum() << " average: " << average() << endl;
    }
    int sum() const {
        int suma=0;
        for(int i=0;i<size;i++){
            suma+=arr[i];
        }
        return suma;
    }
    double average() const {
        if (size == 0) return 0;
        return (double)sum()/size*1.0;
    }
};

// Class to represent a container of lists
class ListContainer {
private:
    List* lists;
    int numberOfLists;
    int addAttempts;
    int failedAttempts;

public:
    ListContainer() {
        lists = nullptr;
        numberOfLists = 0;
        addAttempts = 0;
        failedAttempts = 0;
    }
    ListContainer(const ListContainer& other) {
        numberOfLists = other.numberOfLists;
        addAttempts = other.addAttempts;
        failedAttempts = other.failedAttempts;
        lists = new List[numberOfLists];
        for (int i = 0; i < numberOfLists; i++) {
            lists[i] = other.lists[i];
        }
    }
    ~ListContainer() {
        delete[] lists;
    }
    ListContainer& operator=(const ListContainer& other) {
        if (this != &other) {
            delete[] lists;
            numberOfLists = other.numberOfLists;
            addAttempts = other.addAttempts;
            failedAttempts = other.failedAttempts;
            lists = new List[numberOfLists];
            for (int i = 0; i < numberOfLists; i++) {
                lists[i] = other.lists[i];
            }
        }
        return *this;
    }
    void print() const {
        if (numberOfLists == 0) {
            cout << "The list is empty" << endl;
            return;
        } else {
            int totalSum = sum();
            double totalAverage = average();
            for (int i = 0; i < numberOfLists; i++) {
                cout << "List number: " << i + 1 << " List info: ";
                lists[i].pecati();
            }
            cout << "Sum: " << totalSum << " Average: " << totalAverage << endl;
        }
        cout << "Successful attempts: " << addAttempts << " Failed attempts: " << failedAttempts << endl;
    }
    void addNewList(const List &l){
        bool canAdd = true;
        for (int i = 0; i < numberOfLists; i++) {
            if (lists[i].sum() == l.sum()) {
                canAdd = false;
                break;
            }
        }
        if (canAdd) {
            List* temp = new List[numberOfLists + 1];
            for (int i = 0; i < numberOfLists; i++) {
                temp[i] = lists[i];
            }
            temp[numberOfLists] = l;
            delete[] lists;
            lists = temp;
            numberOfLists++;
            addAttempts++;
        } else {
            failedAttempts++;
        }
    }
    int sum() const {
        int totalSum = 0;
        for (int i = 0; i < numberOfLists; i++) {
            totalSum += lists[i].sum();
        }
        return totalSum;
    }
    double average() const{
        int totalSum = 0;
        int totalElements=0;
        for (int i = 0; i < numberOfLists; i++) {
            totalSum += lists[i].sum();
            totalElements+=lists[i].getSize();
        }
        return (double)totalSum/totalElements;
    }
};
int main() {
    ListContainer lc;
    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int n;
        int niza[100];

        cin >> n;

        for (int j = 0; j < n; j++) {
            cin >> niza[j];
        }

        List l = List(niza, n);

        lc.addNewList(l);
    }

    int testCase;
    cin >> testCase;

    if (testCase == 1) {
        cout << "Test case for operator =" << endl;
        ListContainer lc1;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1 = lc;
        lc1.print();
        cout << lc1.sum() << " " << lc.sum() << endl;
        lc1.sum();
        lc1.average();
    } else {
        lc.print();
    }

    return 0;
}
