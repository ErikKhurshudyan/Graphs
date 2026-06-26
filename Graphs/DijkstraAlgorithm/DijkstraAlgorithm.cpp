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
dijikstra(const WeightedGragh& adj, const int startNode)
{
    const int V = adj.size();

    const int INF = numeric_limits<int>::max();
    vector<int> dist(V, INF);
 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[startNode] = 0;

    pq.push({0, startNode});

    while (!pq.empty()) {
        const int currentDist = pq.top().first;
        const int u = pq.top().second;
        pq.pop();

        if (currentDist > dist[u]) continue;

        for (auto& edge : adj[u]) {
            const int v = edge.first;
            const int weight = edge.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Start " << startNode << " : ";

    for (int i = 0; i < V; ++i) {
        if (dist[i] == INF) {
            cout << "Error: " << i << "edge" << endl;
            continue;
        }
        cout << "Distance " << i << " : " << dist[i] << endl; 
    }
}

int
main()
{
    int V = 5; /// Edge
    WeightedGragh adj(V);

    addEdge(adj, 0, {1, 10});
    addEdge(adj, 0, {4, 3});
    addEdge(adj, 1, {2, 2});
    addEdge(adj, 1, {4, 4});
    addEdge(adj, 2, {3, 9});
    addEdge(adj, 3, {4, 2});

//    printGraph(adj);

    dijikstra(adj, 0);

    return 0;
}
