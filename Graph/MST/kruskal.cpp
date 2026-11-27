// Kruskal's Algorithm - Minimum Spanning Tree (edge sort + DSU)
// Compile: g++ -std=c++17 -O2 kruskal.cpp -o kruskal
// Run:     ./kruskal

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>
using namespace std;

struct Edge {
    int u, v, w;
};

// Disjoint Set Union with path compression + union by rank
class DSU {
    vector<int> parent, rnk;
public:
    DSU(int n) : parent(n), rnk(n, 0) {
        iota(parent.begin(), parent.end(), 0);   // parent[i] = i
    }

    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);          // path compression
        return parent[x];
    }

    bool unite(int a, int b) {
        int ra = find(a), rb = find(b);
        if (ra == rb) return false;               // same set -> cycle
        if (rnk[ra] < rnk[rb]) swap(ra, rb);
        parent[rb] = ra;                          // attach shorter under taller
        if (rnk[ra] == rnk[rb]) rnk[ra]++;
        return true;
    }
};

// Returns {mst_edges, total_weight}. Vertices are 0..n-1.
pair<vector<Edge>, long long> kruskalMST(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) { return a.w < b.w; });

    DSU dsu(n);
    vector<Edge> mst;
    long long total = 0;

    for (const Edge& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mst.push_back(e);
            total += e.w;
            if ((int)mst.size() == n - 1) break;
        }
    }

    if ((int)mst.size() != n - 1)
        throw runtime_error("Graph is disconnected; no spanning tree exists.");
    return {mst, total};
}

int main() {
    int n = 6;
    vector<Edge> edges = {
        {0, 1, 4}, {0, 2, 3}, {1, 2, 1}, {1, 3, 2},
        {2, 3, 4}, {3, 4, 2}, {4, 5, 6}
    };

    auto [mst, total] = kruskalMST(n, edges);

    cout << "Kruskal's MST edges (u - v : weight)\n";
    for (const Edge& e : mst)
        cout << "  " << e.u << " - " << e.v << " : " << e.w << "\n";
    cout << "Total weight: " << total << "\n";
    return 0;
}
