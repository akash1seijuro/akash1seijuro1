#include<iostream>
#include<iomanip>
#include<cstring>
#include<cctype>
#include<cmath>
#include<fstream>
using namespace std;
enum Extension { txt, pdf, exe };
class File {
private:
    char* name;
    char* owner;
    int size;
    Extension ext;
public:
    File(const char* fileName="", const char* fileOwner="", int fileSize=0, Extension ext=txt) {
        name = new char[strlen(fileName) + 1];
        strcpy(name, fileName);
        owner = new char[strlen(fileOwner) + 1];
        strcpy(owner, fileOwner);
        size = fileSize;
        this->ext = ext;
    }
    File(const File& f) {
        name = new char[strlen(f.name) + 1];
        strcpy(name, f.name);
        owner = new char[strlen(f.owner) + 1];
        strcpy(owner, f.owner);
        size = f.size;
        ext = f.ext;
    }
    ~File() {
        delete[] name;
        delete[] owner;
    }
    File& operator=(const File& f) {
        if (this != &f) {
            delete[] name;
            delete[] owner;
            name = new char[strlen(f.name) + 1];
            strcpy(name, f.name);
            owner = new char[strlen(f.owner) + 1];
            strcpy(owner, f.owner);
            size = f.size;
            ext = f.ext;
        }
        return *this;
    }
    void print() const {
        cout << "File name: " << name << ".";
        if (ext == 0) cout << "pdf";
        else if (ext == 1) cout << "txt";
        else cout << "exe";
        cout << "\nFile owner: " << owner;
        cout << "\nFile size: " << size << "\n";
    }
    bool equals(const File& that) const {
        return strcmp(name, that.name) == 0 && strcmp(owner, that.owner) == 0 && ext == that.ext;
    }
    bool equalsType(const File& that) const {
        return strcmp(name, that.name) == 0 && ext == that.ext;
    }
};
class Folder {
private:
    char* name;
    int fileCount;
    File* files;
public:
    Folder(const char* folderName) {
        name = new char[strlen(folderName) + 1];
        strcpy(name, folderName);
        fileCount = 0;
        files = nullptr;
    }
    ~Folder() {
        delete[] name;
        delete[] files;
    }
    void print() const {
        cout << "Folder name: " << name << "\n";
        for (int i = 0; i < fileCount; i++) {
            files[i].print();
        }
    }
    void add(const File& file) {
        File* temp = new File[fileCount + 1];
        for (int i = 0; i < fileCount; i++) {
            temp[i] = files[i];
        }
        temp[fileCount] = file;
        delete[] files;
        files = temp;
        fileCount++;
    }
    void remove(const File& file) {
        for (int i = 0; i < fileCount; i++) {
            if (files[i].equals(file)) {
                File* temp = new File[fileCount - 1];
                for (int j = 0, k = 0; j < fileCount; j++) {
                    if (j != i) {
                        temp[k++] = files[j];
                    }
                }
                delete[] files;
                files = temp;
                fileCount--;
                break;
            }
        }
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