#include<iostream>
using namespace std;

#define MAX 100  

class Heap {
private:
    int marks[MAX];
    int lastIndex;

public:
    Heap() {
        for (int i = 0; i < MAX; i++) {
            marks[i] = 0;
        }
        lastIndex = -1;
    }

    int size() {
        return lastIndex + 1;
    }
    
    void insert(int value) {
        if (size() >= MAX) {
            cout << "Heap is full!\n";
            return;
        }
        int index = size();
        marks[index] = value;
        lastIndex++;
        ReheapUp(index);
    }

    void ReheapUp(int index) {
        int child = index;
        int parent;

        while (child > 0) {
            parent = (child - 1) / 2;
            if (marks[child] > marks[parent]) {
                int temp = marks[child];
                marks[child] = marks[parent];
                marks[parent] = temp;
            } else {
                break;
            }
            child = parent;
        }
    }
    
    int FindMax() {
        if (size() > 0) {
            return marks[0];
        } else {
            return -1;
        }
    }

    int FindMin() {
        if (size() == 0) return -1;

        int minVal = marks[0];
        for (int i = 1; i <= lastIndex; i++) {
            if (marks[i] < minVal)
                minVal = marks[i];
        }
        return minVal;
    }

    void displayHeap() {
        cout << "Current Marks in Heap: ";
        for (int i = 0; i <= lastIndex; i++) {
            cout << marks[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Heap H;
    int value, choice = 0;

    while (choice != 4) {
        cout << "\n===== HEAP MENU =====\n";
        cout << "1. Insert element\n";
        cout << "2. Maximum Marks\n";
        cout << "3. Minimum Marks\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter value to be inserted: ";
            cin >> value;
            H.insert(value);
            H.displayHeap();
            break;

        case 2:
            cout << "Maximum Marks: " << H.FindMax() << endl;
            break;

        case 3:
            cout << "Minimum Marks: " << H.FindMin() << endl;
            break;

        case 4:
            cout << "End of the program!" << endl;
            return 0;

        default:
            cout << "Please enter a valid choice!" << endl;
            break;
        }
    }

    return 0;
}
