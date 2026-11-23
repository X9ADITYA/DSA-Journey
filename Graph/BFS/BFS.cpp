#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Breadth-First Search (BFS) using an adjacency list.
// This version handles disconnected graphs as well.

void bfsFromNode(int start, const vector<vector<int>>& adj,
                 vector<bool>& visited) {
    queue<int> q;

    visited[start] = true;
    q.push(start);

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        cout << node << " ";

        // Visit every unvisited neighbour.
        for (int neighbour : adj[node]) {
            if (!visited[neighbour]) {
                visited[neighbour] = true; // Mark when enqueued.
                q.push(neighbour);
            }
        }
    }
}

void bfs(const vector<vector<int>>& adj) {
    int n = static_cast<int>(adj.size());
    vector<bool> visited(n, false);

    // Start a BFS from every unvisited vertex so that
    // all connected components are covered.
    for (int vertex = 0; vertex < n; vertex++) {
        if (!visited[vertex]) {
            bfsFromNode(vertex, adj, visited);
        }
    }
}

int main() {
    int vertices = 7;

    // Graph represented using an adjacency list.
    vector<vector<int>> adj(vertices);

    // Undirected edges.
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

    cout << "BFS traversal: ";
    bfs(adj);
    cout << '\n';

    return 0;
}
