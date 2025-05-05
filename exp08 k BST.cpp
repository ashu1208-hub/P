#include <iostream>
#include <iomanip>
using namespace std;

const int MAX = 10;

class Node {
public:
    int data;
    Node *left, *right;

    Node(int val = 0) {
        data = val;
        left = right = NULL;
    }
};

class OBST {
private:
    int N;             // Total number of keys + 1
    int a[MAX];        // Sorted keys
    float p[MAX];      // Success probabilities
    float q[MAX];      // Failure probabilities
    float W[MAX][MAX]; // Weight matrix
    float C[MAX][MAX]; // Cost matrix
    int R[MAX][MAX];   // Root matrix
    Node* root;

public:
    OBST(int n = 0) {
        N = n + 1; // for q[0] to q[n]
        root = NULL;
    }

    void read() {
        cout << "Enter " << N - 1 << " sorted keys:\n";
        for (int i = 1; i < N; i++)
            cin >> a[i];

        cout << "Enter success probabilities (p[i]):\n";
        for (int i = 1; i < N; i++)
            cin >> p[i];

        cout << "Enter failure probabilities (q[i]):\n";
        for (int i = 0; i < N; i++)
            cin >> q[i];
    }

    void construct_obst() {
        for (int i = 0; i < N; i++) {
            W[i][i] = q[i];
            C[i][i] = 0;
            R[i][i] = 0;

            if (i < N - 1) {
                W[i][i + 1] = q[i] + p[i + 1] + q[i + 1];
                C[i][i + 1] = W[i][i + 1];
                R[i][i + 1] = i + 1;
            }
        }

        for (int m = 2; m < N; m++) {
            for (int i = 0; i < N - m; i++) {
                int j = i + m;
                W[i][j] = W[i][j - 1] + p[j] + q[j];
                float minCost = 9999;
                int kmin = 0;

                for (int k = i + 1; k <= j; k++) {
                    float cost = C[i][k - 1] + C[k][j];
                    if (cost < minCost) {
                        minCost = cost;
                        kmin = k;
                    }
                }
                C[i][j] = W[i][j] + minCost;
                R[i][j] = kmin;
            }
        }
    }

    Node* build(int i, int j) {
        if (R[i][j] == 0) return NULL;
        int k = R[i][j];
        Node* node = new Node(a[k]);
        node->left = build(i, k - 1);
        node->right = build(k, j);
        return node;
    }

    void build_obst() {
        root = build(0, N - 1);
    }

    void inorder(Node* temp) {
        if (temp) {
            inorder(temp->left);
            cout << temp->data << " ";
            inorder(temp->right);
        }
    }

    void display_results() {
        cout << "\nCost Matrix (C):\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << setw(6) << fixed << setprecision(2) << C[i][j] << " ";
            cout << endl;
        }

        cout << "\nWeight Matrix (W):\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << setw(6) << fixed << setprecision(2) << W[i][j] << " ";
            cout << endl;
        }

        cout << "\nRoot Matrix (R):\n";
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                cout << setw(10) << R[i][j] << " ";
            cout << endl;
        }

        cout << "\nInorder Traversal of OBST: ";
        inorder(root);
        cout << endl;
    }
};

int main() {
    int n;
    cout << "Enter number of keys: ";
    cin >> n;

    OBST tree(n);
    tree.read();
    tree.construct_obst();
    tree.build_obst();
    tree.display_results();

    return 0;
}

