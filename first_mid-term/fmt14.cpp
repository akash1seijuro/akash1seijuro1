#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cstring>
#include <cctype>
#include <cmath>
#include <fstream>
using namespace std;
enum Extension {
	pdf=0, txt, exe
};
class File {
private:
	char *name;
	Extension ext;
	char *owner;
	int size;
	void copy(const File &f) {
		this->name = new char[strlen(f.name) + 1];
		strcpy(this->name, f.name);
		this->ext = f.ext;
		this->owner = new char[strlen(f.owner) + 1];
		strcpy(this->owner, f.owner);
		this->size = f.size;
	}
public:
	File(const char *name="", const char *owner="", int size=0, Extension ext=pdf) {
		this->name=new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->owner=new char[strlen(owner) + 1];
		strcpy(this->owner, owner);
		this->size=size;
		this->ext = ext;
	}
	File(const File &f) {
		copy(f);
	}
	File &operator=(const File &f) {
		if (this != &f) {
			delete [] name;
			delete [] owner;
			copy(f);
		}
		return *this;
	}
	~File() {
		delete [] name;
		delete [] owner;
	}
	void print() {
		cout<<"File name: "<<name;
		if (ext==pdf) {
			cout<<".pdf";
		}else if (ext==txt) {
			cout<<".txt";
		}else {
			cout<<".exe";
		}
		cout<<endl<<"File owner: "<<owner<<endl<<"File size: "<<size<<endl;
	}
	bool equals(const File &f) {
		return (strcmp(name, f.name)==0 && ext==f.ext && strcmp(owner, f.owner)==0);
	}
	bool equalsType(const File &f) {
		return (strcmp(name, f.name)==0 && ext==f.ext);
	}
};
class Folder {
private:
	char *name;
	File *files;
	int n;
public:
	Folder(const char *name="") {
		this->name=new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->n=0;
		files=nullptr;
	}
	~Folder() {
		delete [] name;
		delete [] files;
	}
	void print() {
		cout<<"Folder name: "<<name<<endl;
		for (int i=0; i<n; i++) {
			files[i].print();
		}
	}
	void remove(const File &f) {
		int k=0;
		File *new_files=new File[n-1]; //samo prvo najdenata kje ja izbrishe
		for (int i=0;i<n;i++) {
			if (files[i].equals(f)) {
				for (int j=0;j<n;j++) {
					if (j!=i) {
						new_files[k++]=files[j];
					}
				}
				delete [] files;
		        files=new_files;
		        n--;
		        break;
			}
		}
	}
	void add(const File &f) {
		File *new_files=new File[n+1];
		for (int i=0;i<n;i++) {
			new_files[i]=files[i];
		}
		new_files[n]=f;
		delete [] files;
		files=new_files;
		n++;
	}
};
int main() {
	char fileName[20];
	char fileOwner[20];
	int ext;
	int fileSize;

	int testCase;
	cin >> testCase;
	if (testCase == 1) {
		cout << "======= FILE CONSTRUCTORS AND = OPERATOR =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File created = File(fileName, fileOwner, fileSize, (Extension) ext);
		File copied = File(created);
		File assigned = created;

		cout << "======= CREATED =======" << endl;
		created.print();
		cout << endl;
        cout << "======= COPIED =======" << endl;
		copied.print();
		cout << endl;
        cout << "======= ASSIGNED =======" << endl;
		assigned.print();
	}
	else if (testCase == 2) {
		cout << "======= FILE EQUALS & EQUALS TYPE =======" << endl;
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File first(fileName, fileOwner, fileSize, (Extension) ext);
		first.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File second(fileName, fileOwner, fileSize, (Extension) ext);
		second.print();

		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File third(fileName, fileOwner, fileSize, (Extension) ext);
		third.print();

		bool equals = first.equals(second);
		cout << "FIRST EQUALS SECOND: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equals = first.equals(third);
		cout << "FIRST EQUALS THIRD: ";
		if (equals)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		bool equalsType = first.equalsType(second);
		cout << "FIRST EQUALS TYPE SECOND: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

		equalsType = second.equals(third);
		cout << "SECOND EQUALS TYPE THIRD: ";
		if (equalsType)
			cout << "TRUE" << endl;
		else
			cout << "FALSE" << endl;

	}
	else if (testCase == 3) {
		cout << "======= FOLDER CONSTRUCTOR =======" << endl;
		cin >> fileName;
		Folder folder(fileName);
		folder.print();

	}
	else if (testCase == 4) {
		cout << "======= ADD FILE IN FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		folder.print();
	}
	else {
		cout << "======= REMOVE FILE FROM FOLDER =======" << endl;
		char name[20];
		cin >> name;
		Folder folder(name);

		int iter;
		cin >> iter;

		while (iter > 0) {
			cin >> fileName;
			cin >> fileOwner;
			cin >> fileSize;
			cin >> ext;

			File file(fileName, fileOwner, fileSize, (Extension) ext);
			folder.add(file);
			iter--;
		}
		cin >> fileName;
		cin >> fileOwner;
		cin >> fileSize;
		cin >> ext;

		File file(fileName, fileOwner, fileSize, (Extension) ext);
		folder.remove(file);
		folder.print();
	}
	return 0;
}
