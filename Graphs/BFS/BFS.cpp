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
bfs(vector<vector<int>>& adj, const int startNode)
{
    const int V = adj.size();

    vector<bool> visited(V, false);

    queue<int> queue1;

    visited[startNode] = true;
    queue1.push(startNode);

    while (!queue1.empty()) {
        const int currentNode = queue1.front();
        queue1.pop();

        cout << currentNode << ' ';

        for (int neighbor : adj[currentNode]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                queue1.push(neighbor);
            }
        }
    }
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

    bfs(adj, 0);
    return 0;
}
