#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
class List {
private:
	int *numbers;
	int n;
	void copy(const List &l) {
		n=l.n;
		numbers=new int[l.n];
		for (int i=0;i<l.n;i++) {
			numbers[i]=l.numbers[i];
		}
	}
public:
	int getN() {
		return n;
	}
	List(int *numbers=nullptr, int n=0) {
		this->n=n;
		this->numbers=new int[n];
		for (int i=0;i<n;i++) {
			this->numbers[i]=numbers[i];
		}
	}
	List(const List &l) {
		copy(l);
	}
	List &operator=(const List &l) {
		if (this != &l) {
			delete [] numbers;
			copy(l);
		}
		return *this;
	}
	~List() {
		delete [] numbers;
	}
	void pecati() {
		cout<<n<<": ";
		for (int i=0;i<n;i++) {
			cout<<numbers[i]<<" ";
		}
		cout<<"sum: "<<sum()<<" average: "<<average()<<endl;
	}
	int sum() {
		int sum=0;
		for (int i=0;i<n;i++) {
			sum+=numbers[i];
		}
		return sum;
	}
	double average() {
		int sum=0;
		for (int i=0;i<n;i++) {
			sum+=numbers[i];
		}
		if (n==0) {
			return 0;
		}
		return double(sum)/double(n);
	}
};
class ListContainer {
private:
	List *lists;
	int n;
	int attempts;
	void copy(const ListContainer &l) {
		n=l.n;
		lists=new List[l.n];
		for (int i=0;i<n;i++) {
			lists[i]=l.lists[i];
		}
		attempts=l.attempts;
	}
public:
	ListContainer() {
		this->n=0;
		this->lists=nullptr;
		this->attempts=0;
	}
	ListContainer(const ListContainer &l) {
		copy(l);
	}
	ListContainer &operator=(const ListContainer &l) {
		if (this != &l) {
			delete [] lists;
			copy(l);
		}
		return *this;
	}
	~ListContainer() {
		delete [] lists;
	}
	void print() {
		if (n==0) {
			cout<<"The list is empty"<<endl;
			return;
		}
		for (int i=0;i<n;i++) {
			cout<<"List number: "<<i+1<<" List info: ";
			lists[i].pecati();
		}
		cout<<"Sum: "<<sum()<<" Average: "<<average()<<endl;
		cout<<"Successful attempts: "<<n<<" Failed attempts: "<<attempts-n<<endl;
	}
	void addNewList(List l) {
		attempts++;
		for (int i=0;i<n;i++) {
			if (lists[i].sum()==l.sum()) {
				return;
			}
		}
		List *new_list = new List[n+1];
		for (int i=0;i<n;i++) {
			new_list[i]=lists[i];
		}
		new_list[n]=l;
		delete [] lists;
		lists=new_list;
		n++;
	}
	int sum() {
		int sum=0;
		for (int i=0;i<n;i++) {
			sum+=lists[i].sum();
		}
		return sum;
	}
	double average() {
		int count=0;
		for (int i=0;i<n;i++) {
			count+=lists[i].getN();
		}
		if (count==0) {
			return 0;
		}
		return double(sum())/double(count);
	}
};
int main() {

	ListContainer lc;
	int N;
	cin>>N;

	for (int i=0;i<N;i++) {
		int n;
		int niza[100];

		cin>>n;

		for (int j=0;j<n;j++){
			cin>>niza[j];

		}

		List l=List(niza,n);

		lc.addNewList(l);
	}


	int testCase;
	cin>>testCase;

	if (testCase==1) {
		cout<<"Test case for operator ="<<endl;
		ListContainer lc1;
		lc1.print();
		cout<<lc1.sum()<<" "<<lc.sum()<<endl;
		lc1=lc;
		lc1.print();
		cout<<lc1.sum()<<" "<<lc.sum()<<endl;
		lc1.sum();
		lc1.average();

	}
	else {
		lc.print();
	}
}
