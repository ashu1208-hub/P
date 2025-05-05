#include <iostream>
using namespace std;

class Node {
public:
    string word, meaning;
    Node* left;
    Node* right;

    Node(string w, string m) {
        word = w;
        meaning = m;
        left = NULL;
        right = NULL;
    }
};

class AVL {
private:
    Node* root;

    int height(Node* node) {
        if (node == NULL)
            return 0;
        int leftHeight = height(node->left);
        int rightHeight = height(node->right);
        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }

    int balanceFactor(Node* node) {
        if (node == NULL)
            return 0;
        return height(node->left) - height(node->right);
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        y->left = x->right;
        x->right = y;
        return x;
    }

    Node* balance(Node* node) {
        int bf = balanceFactor(node);
        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            node = rotateRight(node);
        } else if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            node = rotateLeft(node);
        }
        return node;
    }

    Node* insert(Node* node, string w, string m) {
        if (node == NULL)
            return new Node(w, m);

        if (w < node->word)
            node->left = insert(node->left, w, m);
        else if (w > node->word)
            node->right = insert(node->right, w, m);
        else {
            cout << "Word already exists. Duplicate entries not allowed.\n";
            return node;
        }

        return balance(node);
    }

    Node* findMin(Node* node) {
        while (node->left != NULL)
            node = node->left;
        return node;
    }

    Node* deleteNode(Node* node, string w) {
        if (node == NULL)
            return NULL;

        if (w < node->word)
            node->left = deleteNode(node->left, w);
        else if (w > node->word)
            node->right = deleteNode(node->right, w);
        else {
            if (node->left == NULL)
                return node->right;
            else if (node->right == NULL)
                return node->left;

            Node* temp = findMin(node->right);
            node->word = temp->word;
            node->meaning = temp->meaning;
            node->right = deleteNode(node->right, temp->word);
        }

        return balance(node);
    }

    void inorder(Node* node) {
        if (node != NULL) {
            inorder(node->left);
            cout << node->word << ": " << node->meaning << endl;
            inorder(node->right);
        }
    }

    void reverseInorder(Node* node) {
        if (node != NULL) {
            reverseInorder(node->right);
            cout << node->word << ": " << node->meaning << endl;
            reverseInorder(node->left);
        }
    }

    bool search(Node* node, string w, int& count) {
        while (node != NULL) {
            count++;
            if (w == node->word) {
                cout << "Meaning: " << node->meaning << endl;
                return true;
            } else if (w < node->word) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }

    bool update(Node* node, string w, string newMeaning) {
        while (node != NULL) {
            if (w == node->word) {
                node->meaning = newMeaning;
                return true;
            } else if (w < node->word) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }

public:
    AVL() {
        root = NULL;
    }

    void insert(string w, string m) {
        root = insert(root, w, m);
        cout << "Inserted successfully.\n";
    }

    void remove(string w) {
        root = deleteNode(root, w);
        cout << "Deleted if present.\n";
    }

    void displayAscending() {
        cout << "Dictionary in Ascending Order:\n";
        inorder(root);
    }

    void displayDescending() {
        cout << "Dictionary in Descending Order:\n";
        reverseInorder(root);
    }

    void search(string w) {
        int count = 0;
        bool found = search(root, w, count);
        if (found)
            cout << "Found in " << count << " comparisons.\n";
        else
            cout << "Not found after " << count << " comparisons.\n";
    }

    void updateMeaning(string w, string newMeaning) {
        bool updated = update(root, w, newMeaning);
        if (updated)
            cout << "Meaning updated successfully.\n";
        else
            cout << "Word not found in dictionary.\n";
    }

    void maxComparisons() {
        int h = height(root);
        cout << "Maximum comparisons to find a keyword: " << h << endl;
    }
};


int main() {
    AVL dict;
    int ch;
    string w, m;

    do {
        cout << "\nMenu:\n1.Insert\n2.Delete\n3.Search\n4.Update Meaning\n5.Display Asc\n6.Display Desc\n7.Max Comparisons\n8.Exit\n";
        cin >> ch;
        switch (ch) {
            case 1:
                cout << "Word: ";
                cin >> w;
                cout << "Meaning: ";
                cin.ignore(); getline(cin, m);
                dict.insert(w, m);
                break;
            case 2:
                cout << "Word to delete: ";
                cin >> w;
                dict.remove(w);
                break;
            case 3:
                cout << "Word to search: ";
                cin >> w;
                dict.search(w);
                break;
            case 4:
                cout << "Word to update: ";
                cin >> w;
                cout << "New meaning: ";
                cin.ignore(); getline(cin, m);
                dict.updateMeaning(w, m);
                break;
            case 5:
                dict.displayAscending();
                break;
            case 6:
                dict.displayDescending();
                break;
            case 7:
                dict.maxComparisons();
                break;
            case 8:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (ch != 8);

    return 0;
}
