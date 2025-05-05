#include <iostream>
#include <fstream>
using namespace std;

struct Student {
    int rollNo;
    char name[50];
    float marks;
    bool isActive;
};

class DirectAccessFile {
    const string fileName;
    const int recordSize;

public:
    DirectAccessFile(const string& fName) : fileName(fName), recordSize(sizeof(Student)) {}

    void createFile() {
        ofstream file(fileName, ios::binary);
        Student empty = {0, "", 0.0f, false};
        for (int i = 0; i < 100; ++i)
            file.write(reinterpret_cast<char*>(&empty), recordSize);
        cout << "File initialized with empty records.\n";
    }

    void accessRecord(int rollNo, Student& stu, ios::openmode mode, bool write = false) {
        fstream file(fileName, ios::binary | mode);
        if (!file) return void(cout << "Error opening file!\n");
        int pos = (rollNo - 1) * recordSize;
        file.seekg(pos);
        file.read(reinterpret_cast<char*>(&stu), recordSize);
        if (write) {
            file.seekp(pos);
            file.write(reinterpret_cast<char*>(&stu), recordSize);
        }
        file.close();
    }

    void addRecord(const Student& s) {
        Student temp;
        accessRecord(s.rollNo, temp, ios::in | ios::out);
        if (temp.isActive) cout << "Record exists!\n";
        else {
            Student newStu = s;
            accessRecord(s.rollNo, newStu, ios::in | ios::out, true);
            cout << "Record added.\n";
        }
    }

    void readRecord(int rollNo) {
        Student s;
        accessRecord(rollNo, s, ios::in);
        if (s.isActive)
            cout << "\nRoll No: " << s.rollNo << "\nName: " << s.name << "\nMarks: " << s.marks << endl;
        else
            cout << "Record not found!\n";
    }

    void modifyRecord(int rollNo, const Student& newData) {
        Student s;
        accessRecord(rollNo, s, ios::in | ios::out);
        if (s.isActive) {
            Student updated = newData;
            updated.rollNo = rollNo;
            updated.isActive = true;
            accessRecord(rollNo, updated, ios::in | ios::out, true);
            cout << "Record modified.\n";
        } else cout << "Record not found!\n";
    }

    void deleteRecord(int rollNo) {
        Student s;
        accessRecord(rollNo, s, ios::in | ios::out);
        if (s.isActive) {
            s.isActive = false;
            accessRecord(rollNo, s, ios::in | ios::out, true);
            cout << "Record deleted.\n";
        } else cout << "Record not found!\n";
    }

    void displayAllRecords() {
        ifstream file(fileName, ios::binary);
        Student s;
        bool found = false;
        cout << "\nRoll No.  Name                           Marks\n";
        cout << "-----------------------------------------------\n";
        while (file.read(reinterpret_cast<char*>(&s), recordSize))
            if (s.isActive) {
                found = true;
                cout << s.rollNo << "  " << s.name << "  " << s.marks << endl;
            }
        if (!found) cout << "No active records.\n";
        file.close();
    }
};

int main() {
    DirectAccessFile file("students.data");
    file.createFile();

    int choice, rollNo;
    Student s;

    while (true) {
        cout << "\n1.Add 2.Read 3.Modify 4.Delete 5.Display 6.Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Roll No: "; cin >> s.rollNo;
                cout << "Name: "; cin.ignore(); cin.getline(s.name, 50);
                cout << "Marks: "; cin >> s.marks;
                s.isActive = true;
                file.addRecord(s); break;
            case 2:
                cout << "Enter Roll No: "; cin >> rollNo;
                file.readRecord(rollNo); break;
            case 3:
                cout << "Enter Roll No to Modify: "; cin >> rollNo;
                cout << "New Name: "; cin.ignore(); cin.getline(s.name, 50);
                cout << "New Marks: "; cin >> s.marks;
                s.isActive = true;
                file.modifyRecord(rollNo, s); break;
            case 4:
                cout << "Enter Roll No to Delete: "; cin >> rollNo;
                file.deleteRecord(rollNo); break;
            case 5:
                file.displayAllRecords(); break;
            case 6:
                return 0;
        }
    }
}

