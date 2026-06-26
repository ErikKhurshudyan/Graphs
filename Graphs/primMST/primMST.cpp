#include <iostream>
#include <vector>
#include <queue>
#include <limits>

using namespace std;
using WeightedGragh = vector<vector<pair<int, int>>>; 

void
addEdge(WeightedGragh& adj, const int u, pair<int, int> v)
{
    adj[u].push_back(v);
    adj[v.first].push_back({u, v.second});
}

void
primMST(const WeightedGragh& adj, const int V)
{
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    vector<bool> inMST(V, false);
    
    int mst_weight = 0;

    pq.push({0, 0});
    
    while (!pq.empty()) {
        const int weight = pq.top().first;
        const int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;

        inMST[u] = true;
        mst_weight += weight;

        if (weight > 0) {
            cout << u << " - " << weight << endl;
        }
        
        for (const auto& edge : adj[u]) {
            const int v = edge.first;
            const int w = edge.second;

            if (!inMST[v]) {
                pq.push({w, v});
            }
        }
    }
    cout << "MST weight: " << mst_weight << endl;
}

int
main()
{
    const int V = 5; /// Edge
    WeightedGragh adj(V);

    addEdge(adj, 0, {1, 1});
    addEdge(adj, 0, {3, 2});
    addEdge(adj, 1, {3, 3});
    addEdge(adj, 0, {2, 4});
    addEdge(adj, 2, {3, 5});
    addEdge(adj, 1, {4, 6});
    addEdge(adj, 3, {4, 7});

    primMST(adj, V);

    return 0;
}
