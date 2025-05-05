#include<iostream>
#include<queue>
#include<stack>
#include<string>
using namespace std;

#define MAX 10

//graph using adjacency list
class Node{
    private:
    int data;
    Node* next;

    public:
    Node(int d = 0)
    {
        data = d;
        next = NULL;
    }

    friend class Graph;
};

class Graph{
    private:
    int vn, en;
    Node vertexList[MAX];
    string landmarks[MAX];

    public:
    Graph(int v=0, int e=0)
    {
        vn = v;
        en = e;
        for(int i=0; i<vn; i++)
        {
            vertexList[i] = Node(i);
        }
    }

    void landmarksInput()
    {
        cout<<"Enter names of all landmarks:- "<<endl;
        for(int i = 0; i<vn; i++)
        {
            cout<<"Landmark "<<i+1<<": ";
            cin>>landmarks[i];
        }
        cout<<"Displaying list of landmarks: ";
        for(int i = 0; i<vn; i++)
        {
            cout<<landmarks[i]<<"  ";
        }
        cout<<endl;

    }

    int landmarkVertex(string landmark)
    {
        for(int i = 0; i<vn; i++)
        {
            if(landmarks[i] == landmark)
                return i;
        }
        return -1;
    }

    void readGraph()
    {
        Node* pnew;
        string lm;
        for (int vi = 0; vi < vn; vi++) {
            cout << "Enter landmarks adjacent to " << landmarks[vi] << " (enter -1 to stop):" << endl;
            
            while (true) {
                cin >> lm;
                if (lm == "-1")
                    break;
        
                pnew = new Node(landmarkVertex(lm));
                pnew->next = vertexList[vi].next;
                vertexList[vi].next = pnew;
            }
        }
        
    }

    void display()
    {
        Node* temp;
        for(int vi=0; vi<vn; vi++)
        {
            cout<<"|"<<landmarks[vi]<<"|->";
            temp = vertexList[vi].next;
            while(temp != NULL)
            {
                cout<<landmarks[temp->data]<<"->";
                temp = temp->next;
            }
            cout<<"NULL"<<endl;
        }
    }

    void BFS(string start)
    {
        queue<int>q;
        int visited[MAX] = {0};
        Node* temp;
        int vi = landmarkVertex(start);
        q.push(vi);
        visited[vi] = 1;
        while(!q.empty())
        {
            vi = q.front();
            q.pop();
            cout<<landmarks[vi]<<"  ";
            temp = vertexList[vi].next;
            while(temp != NULL)
            {
                if(visited[temp->data] == 0)
                {
                    q.push(temp->data);
                    visited[temp->data] = 1;
                }
                temp = temp->next;
            }
        }
        cout<<endl;
    }

    void DFS(string start)
    {
        stack<int>s;
        int visited[MAX] = {0};
        Node* temp;
        int vi = landmarkVertex(start);
        s.push(vi);
        visited[vi] = 1;
        while(!s.empty())
        {
            vi = s.top();
            s.pop();
            cout<<landmarks[vi]<<"  ";
            temp = vertexList[vi].next;
            while(temp != NULL)
            {
                if(visited[temp->data] == 0)
                {
                    s.push(temp->data);
                    visited[temp->data] = 1;
                }
                temp = temp->next;
            }
        }
        cout<<endl;
    }

};

int main()
{
    int v,e;
    cout<<"Enter number of landmarks and connections: "<<endl;
    cin>>v>>e;
    Graph g(v, e);
    g.landmarksInput();
    g.readGraph();
    cout<<"Displaying adjacency list:"<<endl;
    g.display();
    cout<<"Displaying BFS:"<<endl;
    g.BFS("A");
    cout<<"Displaying DFS:"<<endl;
    g.DFS("A");
    return 0;
}
