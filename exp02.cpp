#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class Word {
private:
    string word;
    string meaning;
    int chain;

public:
    Word() {
        word = "NULL";
        meaning = "NULL";
        chain = -1;
    }

    void input() {
        cout << "\nEnter word and meaning below:\nWord: ";
        cin >> word;
        cout << "Meaning: ";
        cin >> meaning;
    }

    void display() {
        cout << setw(10) << word << setw(30) << meaning << setw(7) << chain << endl;
    }

    friend class Dictionary;
};

class Dictionary {
private:
    Word hashTable[10];

public:
    Dictionary() {
        Word w;
        for (int i = 0; i < 10; i++) {
            hashTable[i] = w;
        }
    }

    int hashFunction(string key) {
        int sum = 0;
        for (char ch : key) {
            sum += ch;
        }
        return sum % 10;
    }

    bool insert(Word w) {
        int index = hashFunction(w.word);

        // Case 1: Direct insertion
        if (hashTable[index].word == "NULL") {
            hashTable[index] = w;
            return true;
        }

        // Case 2: Replacement needed
        if (hashFunction(hashTable[index].word) != index) {
            Word temp = hashTable[index];
            int tempHash = hashFunction(temp.word);

            // Insert new word at correct place
            hashTable[index] = w;

            // Reinsert old word
            insert(temp);
            return true;
        }

        // Case 3: Collision with chaining
        int current = index;
        while (hashTable[current].chain != -1) {
            current = hashTable[current].chain;
        }

        // Find empty slot
        for (int i = 0; i < 10; i++) {
            if (hashTable[i].word == "NULL") {
                hashTable[i] = w;
                hashTable[current].chain = i;
                return true;
            }
        }

        cout << "Dictionary full." << endl;
        return false;
    }

    bool find(string word) {
        int index = hashFunction(word);
        int comparisons = 1;

        if (hashTable[index].word == word) {
            cout << "Search successful!\n";
            cout << hashTable[index].word << ": " << hashTable[index].meaning << endl;
            cout << "Comparisons: " << comparisons << endl;
            return true;
        }

        int next = hashTable[index].chain;
        while (next != -1) {
            comparisons++;
            if (hashTable[next].word == word) {
                cout << "Search successful!\n";
                cout << hashTable[next].word << ": " << hashTable[next].meaning << endl;
                cout << "Comparisons: " << comparisons << endl;
                return true;
            }
            next = hashTable[next].chain;
        }

        cout << "Search unsuccessful.\n";
        return false;
    }

    bool dlt(string word) {
        Word empty;
        int index = hashFunction(word);

        if (hashTable[index].word == word) {
            int next = hashTable[index].chain;
            hashTable[index] = empty;
            hashTable[index].chain = next;
            cout << "Deletion successful!" << endl;
            return true;
        }

        int prev = index;
        int curr = hashTable[index].chain;

        while (curr != -1) {
            if (hashTable[curr].word == word) {
                hashTable[prev].chain = hashTable[curr].chain;
                hashTable[curr] = empty;
                cout << "Deletion successful!" << endl;
                return true;
            }
            prev = curr;
            curr = hashTable[curr].chain;
        }

        cout << "Deletion unsuccessful." << endl;
        return false;
    }

    void show() {
        cout << setw(7) << "Index" << setw(10) << "Word" << setw(30) << "Meaning" << setw(7) << "Chain" << endl;
        for (int i = 0; i < 10; i++) {
            cout << setw(7) << i;
            hashTable[i].display();
        }
    }
};

int main() {
    Word w;
    Dictionary d;
    int choice;
    string wrd;

    do {
        cout << "\nEnter your choice:\n1. Insert\n2. Find\n3. Delete\n4. Display\n5. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            w.input();
            if (d.insert(w))
                cout << "Data inserted successfully.\n";
            else
                cout << "Data insertion unsuccessful.\n";
            break;

        case 2:
            cout << "Enter word to search: ";
            cin >> wrd;
            d.find(wrd);
            break;

        case 3:
            cout << "Enter word to delete: ";
            cin >> wrd;
            d.dlt(wrd);
            break;

        case 4:
            cout << "\nDisplaying Dictionary:\n";
            d.show();
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid input.\n";
        }

    } while (choice != 5);

    return 0;
}

