#include <iostream>
#define MAX 10
#define INF 999
using namespace std;

class Graph {
    int adjMatrix[MAX][MAX];
    int vn;
    int en;

public:
    Graph(int v = 0, int e = 0) {
        vn = v;
        en = e;
        for (int i = 0; i < vn; i++) {
            for (int j = 0; j < vn; j++) {
                adjMatrix[i][j] = INF;
            }
        }
    }

    void readGraph() {
        int vi, vj, w;
        for (int i = 0; i < en; i++) {
            cout << "\nEnter pair of offices (1-based index) and cost in rupees to connect them: ";
            cin >> vi >> vj >> w;
            if (vi > 0 && vi <= vn && vj > 0 && vj <= vn) {
                adjMatrix[vi - 1][vj - 1] = w;
                adjMatrix[vj - 1][vi - 1] = w;
            } else {
                cout << "Invalid input, re-enter." << endl;
                i--;
            }
        }
    }

    void spanningTree(int root) {
        int dist[MAX], closest[MAX];
        bool visited[MAX] = {false};
        int mincost = 0;

        root--;  // Convert to 0-based index
        for (int i = 0; i < vn; i++) {
            dist[i] = adjMatrix[root][i];
            closest[i] = root;
        }
        visited[root] = true;

        for (int i = 0; i < vn - 1; i++) {
            int minDist = INF, current = -1;

            for (int v = 0; v < vn; v++) {
                if (!visited[v] && dist[v] < minDist) {
                    minDist = dist[v];
                    current = v;
                }
            }

            if (current == -1) {
                cout << "Graph is disconnected. MST cannot be formed completely." << endl;
                return;
            }

            cout << "Connection between Office " << closest[current] + 1
                 << " and Office " << current + 1 << "." << endl;
            mincost += adjMatrix[closest[current]][current];
            visited[current] = true;

            for (int v = 0; v < vn; v++) {
                if (!visited[v] && adjMatrix[current][v] < dist[v]) {
                    dist[v] = adjMatrix[current][v];
                    closest[v] = current;
                }
            }
        }

        cout << "Total minimum cost is Rs." << mincost << endl;
    }
};

int main() {
    int V, E, s;
    cout << "Enter Office Details:\n";
    cout << "Enter Number of Offices: ";
    cin >> V;
    cout << "Enter Number of connections between offices: ";
    cin >> E;

    Graph g(V, E);
    g.readGraph();

    cout << "Enter start Office (1-based index): ";
    cin >> s;

    cout << "Connections required for minimum total cost:\n";
    g.spanningTree(s);

    return 0;
}

