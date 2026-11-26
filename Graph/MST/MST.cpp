#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>
using namespace std;

struct Edge { int u, v, w; };

class DSU {
    vector<int> parent, rankSize;
public:
    DSU(int n) : parent(n), rankSize(n, 0) {
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]); // Path compression
        return parent[x];
    }
    bool unite(int a, int b) {
        a = find(a); b = find(b);
        if (a == b) return false;
        if (rankSize[a] < rankSize[b]) swap(a, b);
        parent[b] = a;
        if (rankSize[a] == rankSize[b]) rankSize[a]++;
        return true;
    }
};

void kruskalMST(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(),
         [](const Edge& a, const Edge& b) { return a.w < b.w; });
    DSU dsu(n);
    int total = 0, count = 0;
    cout << "Kruskal MST edges:\n";
    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            cout << e.u << " - " << e.v << " : " << e.w << '\n';
            total += e.w;
            if (++count == n - 1) break;
        }
    }
    if (count != n - 1) cout << "MST does not exist: graph is disconnected.\n";
    else cout << "Total MST weight: " << total << '\n';
}

void primMST(const vector<vector<pair<int,int>>>& adj) {
    int n = (int)adj.size();
    if (n == 0) { cout << "Graph is empty.\n"; return; }
    // Min-heap stores {edge weight, destination vertex}.
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<bool> used(n, false);
    pq.push({0, 0});
    int total = 0, count = 0;
    cout << "Prim MST edges:\n";
    while (!pq.empty()) {
        auto [w, u] = pq.top(); pq.pop();
        if (used[u]) continue;
        used[u] = true;
        total += w;
        count++;
        if (u != 0) cout << "Added vertex " << u << " using edge weight " << w << '\n';
        for (auto [v, weight] : adj[u])
            if (!used[v]) pq.push({weight, v});
    }
    if (count != n) cout << "MST does not exist: graph is disconnected.\n";
    else cout << "Total MST weight: " << total << '\n';
}

int main() {
    const int V = 5;
    vector<Edge> edges = {
        {0,1,2}, {0,3,6}, {1,2,3}, {1,3,8},
        {1,4,5}, {2,4,7}, {3,4,9}
    };
    vector<vector<pair<int,int>>> adj(V);
    for (const auto& e : edges) {
        adj[e.u].push_back({e.v, e.w});
        adj[e.v].push_back({e.u, e.w}); // Undirected edge
    }
    primMST(adj);
    cout << '\n';
    kruskalMST(V, edges);
    return 0;
}
