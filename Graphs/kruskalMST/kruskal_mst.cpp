#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge {
    int u;
    int v;
    int weight;

    // Custom comparison for sorting edges by weight
    bool operator<(const Edge& rhv) const
    {
        return weight < rhv.weight;
    }
};

// DSU (Disjoint Set Union)
struct DSU {
    vector<int> parent;

    DSU(const int n)
    {
        parent.resize(n);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    int find(const int i)
    {
        if (parent[i] == i) {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    void unite(const int i, const int j)
    {
        const int root_i = find(i);
        const int root_j = find(j);
        if (root_i != root_j) {
            parent[root_i] = root_j;
        }
    }
};

void
printResult(const vector<Edge>& result, const int mst_weight)
{
    cout << "Edges in the Minimum Spanning Tree:" << endl;
    for (const Edge& edge : result) {
        cout << "(" << edge.u << ", " << edge.v << "): " << edge.weight << endl;
    }
    cout << "Total Weight: " << mst_weight << endl;
}

void
kruskal(const int V, vector<Edge>& edges)
{
    sort(edges.begin(), edges.end());

    DSU dsu(V);

    int mst_weight = 0;
    vector<Edge> result;

    for (const Edge& edge : edges) {
        if (dsu.find(edge.u) != dsu.find(edge.v)) {
            dsu.unite(edge.u, edge.v);
            mst_weight += edge.weight;
            result.push_back(edge);

            if (result.size() == static_cast<size_t>(V - 1)) break;
        }
    }

    printResult(result, mst_weight);
}

int 
main()
{
    const int V = 5;
    vector<Edge> edges = { 
        {0, 1, 1}, 
        {0, 3, 2}, 
        {1, 3, 3}, 
        {0, 2, 4}, 
        {2, 3, 5}, 
        {1, 4, 6},
        {3, 4, 7}
    };

    kruskal(V, edges);

    retur n 0;
}
