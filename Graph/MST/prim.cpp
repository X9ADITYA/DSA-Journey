// Prim's Algorithm - Minimum Spanning Tree (adjacency list + min-heap)
// Compile: g++ -std=c++17 -O2 prim.cpp -o prim
// Run:     ./prim

#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <stdexcept>
using namespace std;

struct Edge {
    int u, v, w;
};

// Returns {mst_edges, total_weight}. Vertices are 0..n-1.
pair<vector<Edge>, long long> primMST(int n, const vector<Edge>& edges, int start = 0) {
    // adjacency list: adj[u] = list of (weight, neighbour)
    vector<vector<pair<int, int>>> adj(n);
    for (const Edge& e : edges) {
        adj[e.u].push_back({e.w, e.v});
        adj[e.v].push_back({e.w, e.u});
    }

    vector<bool> visited(n, false);
    // min-heap of (weight, vertex, parent)
    priority_queue<tuple<int, int, int>,
                   vector<tuple<int, int, int>>,
                   greater<tuple<int, int, int>>> pq;
    pq.push({0, start, -1});

    vector<Edge> mst;
    long long total = 0;

    while (!pq.empty()) {
        auto [w, u, parent] = pq.top();
        pq.pop();
        if (visited[u]) continue;   // already in the tree
        visited[u] = true;

        if (parent != -1) {
            mst.push_back({parent, u, w});
            total += w;
        }
        for (auto [nw, v] : adj[u]) {
            if (!visited[v]) pq.push({nw, v, u});
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

    auto [mst, total] = primMST(n, edges, 0);

    cout << "Prim's MST edges (u - v : weight)\n";
    for (const Edge& e : mst)
        cout << "  " << e.u << " - " << e.v << " : " << e.w << "\n";
    cout << "Total weight: " << total << "\n";
    return 0;
}
