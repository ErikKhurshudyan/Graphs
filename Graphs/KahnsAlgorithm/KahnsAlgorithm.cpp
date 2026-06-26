#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void
topologicalSort(const int V, const vector<vector<int>>& adj)
{
    vector<int> inDegree(V, 0);

    for (int u = 0; u < V; u++) {
        for (const int v : adj[u]) {
            inDegree[v]++;
        }
    }

    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (0 == inDegree[i]) {
            q.push(i);
        }
    }

    vector<int> topoOrder;

    while (!q.empty()) {
        const int u = q.front();
        q.pop();

        topoOrder.push_back(u);

        for (const int v : adj[u]) {
            inDegree[v]--;

            if (0 == inDegree[v]) {
                q.push(v);
            }
        }
    }
    if (topoOrder.size() != size_t(V)) {
        cout << "Error 1: Invalid Graph" << endl;
        return;
    }

    cout << "Topological Order: ";
    for (const int node : topoOrder) {
        cout << node << " ";       
    }
    cout << endl;
}

int
main()
{
    const int V = 6;

    vector<vector<int>> adj(V);

    adj[5].push_back(2);
    adj[5].push_back(0);
    adj[4].push_back(0);
    adj[4].push_back(1);
    adj[2].push_back(3);
    adj[3].push_back(1);

    topologicalSort(V, adj);

    return 0;
}
