#include <iostream>
#include <string>
using namespace std;

class client {
    private:
        string name;
        string tele;

    public:
        client() {
            name = "";
            tele = "";
        }

        void getinfo() {
            cout << "Enter the name: ";
            cin >> name;
            cout << "Enter telephone no.: ";
            cin >> tele;
        }

        friend class hashing;
};

class hashing {
    private:
        client table[10];

    public:
        hashing() {
            client c;
            for (int i = 0; i < 10; i++) {
                table[i] = c;
            }
        }

        int hashfn(string key) {
            int index, sum = 0;
            for (int i = 0; i < key.length(); i++) {
                sum = sum + key[i];
            }
            index = sum % 10;
            return index;
        }

        void insertLP(client c) {
            int homeindex = hashfn(c.name);
            if (table[homeindex].name == "") {
                table[homeindex] = c;
                return;
            } else {
                int probe = 1;
                int nextindex = (homeindex + probe) % 10;
                while (nextindex != homeindex) {
                    if (table[nextindex].name == "") {
                        table[nextindex] = c;
                        return;
                    } else {
                        probe++;
                        nextindex = (homeindex + probe) % 10;
                    }
                }
            }
            cout << "No space available" << endl;
        }

        bool searchLP(string name) {
            int homeindex = hashfn(name);
            int count = 1;

            if (table[homeindex].name == name) {
                cout << "Found at index " << homeindex << " in " << count << " comparison(s)." << endl;
                cout << "Name: " << table[homeindex].name << ", Phone: " << table[homeindex].tele << endl;
                return true;
            } else {
                int probe = 1;
                int nextindex = (homeindex + probe) % 10;
                count++;

                while (nextindex != homeindex) {
                    if (table[nextindex].name == name) {
                        cout << "Found at index " << nextindex << " in " << count << " comparison(s)." << endl;
                        cout << "Name: " << table[nextindex].name << ", Phone: " << table[nextindex].tele << endl;
                        return true;
                    } else {
                        count++;
                        probe++;
                        nextindex = (homeindex + probe) % 10;
                    }
                }
            }
            cout << "Not found after " << count << " comparison(s)." << endl;
            return false;
        }

        void display() {
            for (int i = 0; i < 10; i++) {
                cout << i << ": " << table[i].name << " " << table[i].tele << endl;
            }
        }
};

int main() {
    int n;
    cout << "Enter number of clients (max 10): ";
    cin >> n;

    hashing h;
    for (int i = 0; i < n; i++) {
        client temp;
        cout << "\nEnter details for client " << i + 1 << ":\n";
        temp.getinfo();
        h.insertLP(temp);
    }

    cout << "\nCurrent Hash Table:\n";
    h.display();

    char choice;
    string searchname;

    do {
        cout << "\nDo you want to search for a client by name? (y/n): ";
        cin >> choice;

        if (choice == 'y' || choice == 'Y') {
            cout << "Enter name to search: ";
            cin >> searchname;
            h.searchLP(searchname);
        }

    } while (choice == 'y' || choice == 'Y');

    return 0;
}

