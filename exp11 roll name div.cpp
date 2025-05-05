#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Student {
    int rollNo;
    string name, division, address;
    float marks;

public:
    Student() : rollNo(0), marks(0.0f) {}

    void readFromConsole() {
        cout << "Enter Roll No.: "; cin >> rollNo; cin.ignore();
        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Marks: "; cin >> marks; cin.ignore();
        cout << "Enter Division: "; getline(cin, division);
        cout << "Enter Address: "; getline(cin, address);
    }

    void display() const {
        cout << "Roll No.: " << rollNo << endl;
        cout << "Name    : " << name << endl;
        cout << "Marks   : " << marks << endl;
        cout << "Division: " << division << endl;
        cout << "Address : " << address << endl;
        cout << endl;
    }

    void writeToStream(ofstream& out) const {
        out << rollNo << '\n' << name << '\n' << marks << '\n'
            << division << '\n' << address << '\n';
    }

    bool readFromStream(ifstream& in) {
        string line;
    
        if (!getline(in, line)) return false;
        rollNo = stoi(line);
    
        if (!getline(in, name)) return false;
        if (!getline(in, line)) return false;
        marks = stof(line);
    
        if (!getline(in, division)) return false;
        if (!getline(in, address)) return false;
    
        return true;
    }    

    int getRollNo() const { return rollNo; }
};

class SequentialFile {
    const string fileName;

public:
    SequentialFile(const string& file) : fileName(file) {}

    void addRecord(const Student& s) {
        ofstream out(fileName, ios::app);
        if (!out) return void(cout << "File error!\n");
        s.writeToStream(out);
        cout << "Record added.\n";
    }

    bool searchRecord(int roll) {
        ifstream in(fileName);
        Student s;

        while (s.readFromStream(in)) {
            if (s.getRollNo() == roll) {
                cout << "\n--- Student Found ---\n";
                s.display();
                return true; // record found
            }
        }

        cout << "Record not found!\n";
        return false; // record not found
    }

    void deleteRecord(int roll) {
        ifstream in(fileName);
        ofstream temp("temp.txt");
        Student s;

        while (s.readFromStream(in)) {
            if (s.getRollNo() == roll) continue; // skip the record to be deleted
            s.writeToStream(temp);
        }

        in.close();
        temp.close();

        remove(fileName.c_str());
        rename("temp.txt", fileName.c_str());

        cout << "Delete operation completed.\n";
    }

    void displayAllRecords() {
        ifstream in(fileName);
        Student s;
    
        if (!s.readFromStream(in)) {
            cout << "No records found!\n";
            return;
        }
    
        cout << "\n--- All Student Records ---\n";
        s.display();
    
        while (s.readFromStream(in)) {
            s.display();
        }
    }

};

int main() {
    SequentialFile file("students_seq.txt");
    Student s;
    int choice, roll;

    while (true) {
        cout << "\n1.Add 2.Search 3.Delete 4.Display 5.Exit\nChoice: ";
        cin >> choice;
        switch (choice) {
            case 1: s.readFromConsole(); file.addRecord(s); break;
            case 2: cout << "Roll No.: "; cin >> roll; file.searchRecord(roll); break;
            case 3: cout << "Roll No.: "; cin >> roll; file.deleteRecord(roll); break;
            case 4: file.displayAllRecords(); break;
            case 5: return 0;
            default: cout << "Invalid choice.\n";
        }
    }
}
