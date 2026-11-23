#include <iostream>
#include <vector>
using namespace std;

// Recursive Depth-First Search.
// Marks a vertex before exploring its neighbours.
void dfsFromNode(int node, const vector<vector<int>>& adj,
                vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";

    for (int neighbour : adj[node]) {
        if (!visited[neighbour]) {
            dfsFromNode(neighbour, adj, visited);
        }
    }
}

// Traverses every connected component of the graph.
void dfs(const vector<vector<int>>& adj) {
    int n = static_cast<int>(adj.size());
    vector<bool> visited(n, false);

    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            dfsFromNode(vertex, adj, visited);
        }
    }
}

int main() {
    int vertices = 7;
    vector<vector<int>> adj(vertices);

    // Undirected graph.
    vector<pair<int, int>> edges = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4},
        {2, 5}, {2, 6}
    };

    for (const auto& edge : edges) {
        int u = edge.first;
        int v = edge.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "DFS traversal: ";
    dfs(adj);
    cout << '\n';

    return 0;
}
