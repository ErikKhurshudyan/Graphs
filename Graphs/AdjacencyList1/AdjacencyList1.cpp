#include <iostream>
using namespace std;

#include <vector>

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

int
main()
{
    int V = 5; /// nodes
    vector<vector<int> > adj(V);

    addEdge(adj, 0, 1);
    addEdge(adj, 0, 4);
    addEdge(adj, 1, 2);
    addEdge(adj, 1, 3);
    addEdge(adj, 1, 4);
    addEdge(adj, 2, 3);
    addEdge(adj, 3, 4);
    
    printGraph(adj);
    return 0;
}
