#include <iostream>
#include <queue>
using namespace std;

class Node {
    Node *left;
    int data;
    Node *right;

public:
    Node() : left(NULL), data(-1), right(NULL) {}
    Node(int data) : left(NULL), data(data), right(NULL) {}

    friend class BST;
};

class BST {
    Node *root;

public:
    BST() : root(NULL) {}

    void display() {
        display(root);
    }

    void display(Node *node) {
        if (node != NULL) {
            display(node->left);
            cout << node->data << " ";
            display(node->right);
        }
    }

    bool insertBST(int value) {
        if (root == NULL) {
            root = new Node(value);
            cout << value << " inserted at root." << endl;
            return true;
        }

        Node *temp = root;
        while (temp != NULL) {
            if (value < temp->data) {
                if (temp->left == NULL) {
                    temp->left = new Node(value);
                    cout << value << " inserted in left subtree of " << temp->data << "." << endl;
                    return true;
                }
                temp = temp->left;
            } else if (value > temp->data) {
                if (temp->right == NULL) {
                    temp->right = new Node(value);
                    cout << value << " inserted in right subtree of " << temp->data << "." << endl;
                    return true;
                }
                temp = temp->right;
            } else {
                cout << "Duplicate value." << endl;
                return false;
            }
        }
        return false;
    }

    int findmin() {
        if (root == NULL) {
            cout << "Tree is empty." << endl;
            return -1;
        }

        Node *temp = root;
        while (temp->left != NULL) {
            temp = temp->left;
        }
        return temp->data;
    }

    int findmax() {
        if (root == NULL) {
            cout << "Tree is empty." << endl;
            return -1;
        }

        Node *temp = root;
        while (temp->right != NULL) {
            temp = temp->right;
        }
        return temp->data;
    }

    bool search(int value) {
        Node *temp = root;

        while (temp != NULL) {
            if (value < temp->data) {
                temp = temp->left;
            } else if (value > temp->data) {
                temp = temp->right;
            } else {
                cout << "Search successful." << endl;
                return true;
            }
        }
        cout << "Search unsuccessful." << endl;
        return false;
    }

    int heightRecursive() {
        return heightRecursive(root);
    }

    int heightRecursive(Node *node) {
        if (node == NULL) return 0;
        return max(heightRecursive(node->left), heightRecursive(node->right)) + 1;
    }

    int heightBFT() {
        if (root == NULL) return 0;

        queue<Node *> q;
        q.push(root);
        q.push(NULL);
        int height = 1;

        while (!q.empty()) {
            Node *temp = q.front();
            q.pop();

            if (temp != NULL) {
                if (temp->left) q.push(temp->left);
                if (temp->right) q.push(temp->right);
            } else if (!q.empty()) {
                q.push(NULL);
                height++;
            }
        }
        return height;
    }

    void mirror() {
        mirror(root);
    }

    void mirror(Node *node) {
        if (node != NULL) {
            mirror(node->left);
            mirror(node->right);
            swap(node->left, node->right);
        }
    }
};

int main() {
    BST b;
    int choice, v;
    do {
        cout << "\nEnter your choice:\n";
        cout << "1. Display (Inorder)\n";
        cout << "2. Insert\n";
        cout << "3. Display minimum value\n";
        cout << "4. Display maximum value\n";
        cout << "5. Search\n";
        cout << "6. Height (Recursive)\n";
        cout << "7. Height (BFT / Level-order)\n";
        cout << "8. Mirror the tree\n";
        cout << "9. Exit\n";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Inorder Traversal: ";
                b.display();
                cout << endl;
                break;
            case 2:
                cout << "Enter the value to insert: ";
                cin >> v;
                b.insertBST(v);
                break;
            case 3:
                cout << "Minimum value: " << b.findmin() << endl;
                break;
            case 4:
                cout << "Maximum value: " << b.findmax() << endl;
                break;
            case 5:
                cout << "Enter value to search: ";
                cin >> v;
                b.search(v);
                break;
            case 6:
                cout << "Height (recursive): " << b.heightRecursive() << endl;
                break;
            case 7:
                cout << "Height (level-order): " << b.heightBFT() << endl;
                break;
            case 8:
                b.mirror();
                cout << "Tree mirrored successfully." << endl;
                break;
            case 9:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice!" << endl;
        }
    } while (choice != 9);
    return 0;
}

