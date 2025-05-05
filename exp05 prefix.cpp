#include <iostream>
#include <stack>

using namespace std;

class Node {
public:
    char data;
    Node* left;
    Node* right;

    Node(char data = '0') {
        this->data = data;
        left = NULL;
        right = NULL;
    }
};

class ExpressionTree {
private:
    Node* root;
    
public:
    ExpressionTree() {
        root = NULL;
    }

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/');
    }

    // Build expression tree using void return type
    void buildTree(string exp) {
        stack<Node*> st;

        // Loop from right to left for prefix expression
        for (int i = exp.length() - 1; i >= 0; i--) {
            char ch = exp[i];

            Node* newNode = new Node(ch);

            if (isOperator(ch)) {
                if (!st.empty()) {
                    newNode->left = st.top();
                    st.pop();
                }
                if (!st.empty()) {
                    newNode->right = st.top();
                    st.pop();
                }
            }

            st.push(newNode);
        }
        // Set root from stack
        if (!st.empty()) {
            root = st.top();
            st.pop();
        }
    }

    // Post-order traversal (non-recursive)
    void postOrderTraversal() {
        if (root == NULL) {
            cout << "Tree is empty.\n";
            return;
        }

        stack<Node*> s1, s2;
        Node* temp = root;

        s1.push(temp);

        while (!s1.empty()) {
            temp = s1.top();
            s1.pop();
            s2.push(temp);

            if (temp->left != NULL)
                s1.push(temp->left);
            if (temp->right != NULL)
                s1.push(temp->right);
        }

        cout << "Post-order traversal: ";
        while (!s2.empty()) {
            cout << s2.top()->data << " ";
            s2.pop();
        }
        cout << endl;
    }

    // Delete the tree (non-recursive)
    void deleteTree() {
        if (root == NULL) return;

        stack<Node*> st;
        st.push(root);

        while (!st.empty()) {
            Node* temp = st.top();
            st.pop();

            if (temp->left)
                st.push(temp->left);
            if (temp->right)
                st.push(temp->right);

            delete temp;
        }

        root = NULL;
        cout << "Tree deleted successfully.\n";
    }
};

int main() {
    ExpressionTree tree;
    string expr;

    cout << "Enter prefix expression: ";
    cin >> expr;

    tree.buildTree(expr);
    tree.postOrderTraversal();
    tree.deleteTree();
    tree.postOrderTraversal();
    return 0;
}

