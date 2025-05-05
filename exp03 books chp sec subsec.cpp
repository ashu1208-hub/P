#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string title;
    Node* left;
    Node* right;

    Node(string t) {
        title = t;
        left = NULL;
        right = NULL;
    }
};

class BookTree {
    Node* root;

public:
    BookTree(string name) {
        root = new Node(name);
    }

    void addChapter(string chapterName) {
        Node* chapter = new Node(chapterName);

        if (root->left == NULL) {
            root->left = chapter;
        } else {
            Node* temp = root->left;
            while (temp->right != NULL) {
                temp = temp->right;
            }
            temp->right = chapter;
        }

        cout << "Chapter \"" << chapterName << "\" added successfully.\n";
    }

    void addSection(string chapterName, string sectionName) {
        Node* temp = root->left;

        while (temp != NULL && temp->title != chapterName) {
            temp = temp->right;
        }

        if (temp != NULL) {
            Node* section = new Node(sectionName);

            if (temp->left == NULL) {
                temp->left = section;
            } else {
                Node* secTemp = temp->left;
                while (secTemp->right != NULL) {
                    secTemp = secTemp->right;
                }
                secTemp->right = section;
            }
            cout << "Section \"" << sectionName << "\" added under Chapter \"" << chapterName << "\".\n";
        } else {
            cout << "Chapter \"" << chapterName << "\" not found.\n";
        }
    }

    void addSubSection(string chapterName, string sectionName, string subSectionName) {
        Node* chapter = root->left;

        while (chapter != NULL && chapter->title != chapterName) {
            chapter = chapter->right;
        }

        if (chapter != NULL) {
            Node* section = chapter->left;
            while (section != NULL && section->title != sectionName) {
                section = section->right;
            }

            if (section != NULL) {
                Node* subSection = new Node(subSectionName);
                if (section->left == NULL) {
                    section->left = subSection;
                } else {
                    Node* subTemp = section->left;
                    while (subTemp->right != NULL) {
                        subTemp = subTemp->right;
                    }
                    subTemp->right = subSection;
                }
                cout << "Subsection \"" << subSectionName << "\" added under Section \"" << sectionName << "\".\n";
            } else {
                cout << "Section \"" << sectionName << "\" not found.\n";
            }
        } else {
            cout << "Chapter \"" << chapterName << "\" not found.\n";
        }
    }

    void display(Node* node, int level) {
        if (node == NULL) return;

        for (int i = 0; i < level; i++) cout << "    ";
        cout << "- " << node->title << endl;

        display(node->left, level + 1);  // Child
        display(node->right, level);     // Sibling
    }

    void showBook() {
        if (root == NULL) {
            cout << "Book is not created yet.\n";
        } else {
            cout << "\nBook Structure:\n";
            display(root, 0);
        }
    }
};

int main() {
    string bookName, chapterName, sectionName, subSectionName;
    int choice;

    cout << "Enter Book Title: ";
    getline(cin, bookName);
    BookTree book(bookName);

    do {
        cout << "\n========= MENU =========\n";
        cout << "1. Add Chapter\n";
        cout << "2. Add Section to a Chapter\n";
        cout << "3. Add Subsection to a Section\n";
        cout << "4. Show Book Structure\n";
        cout << "5. Exit\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // To avoid getline() issues after cin

        switch (choice) {
            case 1:
                cout << "Enter chapter name: ";
                getline(cin, chapterName);
                book.addChapter(chapterName);
                break;

            case 2:
                cout << "Enter chapter name to add section under: ";
                getline(cin, chapterName);
                cout << "Enter section name: ";
                getline(cin, sectionName);
                book.addSection(chapterName, sectionName);
                break;

            case 3:
                cout << "Enter chapter name: ";
                getline(cin, chapterName);
                cout << "Enter section name: ";
                getline(cin, sectionName);
                cout << "Enter subsection name: ";
                getline(cin, subSectionName);
                book.addSubSection(chapterName, sectionName, subSectionName);
                break;

            case 4:
                book.showBook();
                break;

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}

