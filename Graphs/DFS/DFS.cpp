#include <iostream>
using namespace std;

#include <vector>
#include <queue>


void
addEdge(vector<vector<int> >& adj, const int u, const int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}

void
printGraph(vector<vector<int> >& adj)
{
    for (std::size_t i = 0; i < adj.size(); ++i) {
        cout << "Edge " << i << " neighbors: ";

        for (int neighbor : adj[i]) {
            cout << neighbor << " ";
        }
        cout << endl;
    }
}

void
dfsRecursive(vector<vector<int >>& adj, const int currentNode, vector<bool>& visited) 
{
    visited[currentNode] = true;
    cout << currentNode << ' ';

    for (int neighbor : adj[currentNode]) {
        if (!visited[neighbor]) {
            dfsRecursive(adj, neighbor, visited);
        }
    }
}

void
dfs(vector<vector<int>>& adj, const int startNode)
{
    const int V = adj.size();

    vector<bool> visited(V, false);

    cout << "Visit start in (" << startNode << " edge): ";

    dfsRecursive(adj, startNode, visited);
    cout << endl;
}

int
main()
{
    int V = 6; /// Edge
    vector<vector<int> > adj(V);

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 5);

//    printGraph(adj);

    dfs(adj, 0);
    return 0;
}
