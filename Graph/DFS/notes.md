# Depth-First Search (DFS) — Complete Notes

## 1. What is DFS?

Depth-First Search (DFS) is a graph traversal algorithm that explores one path as deeply as possible before backtracking to explore another path.

DFS is commonly implemented using:
- **Recursion**, which uses the program's call stack.
- An explicit **stack**, which follows LIFO (Last In, First Out).

DFS belongs to:
- Data Structures and Algorithms (DSA)
- Graphs
- Graph Traversal Algorithms
- Tree traversal (preorder, inorder and postorder are DFS-based traversals)

> DFS is an algorithm, not a data structure. It uses a stack (explicitly or through recursion).

## 2. Important terminology

- **Vertex / Node:** An individual point in a graph.
- **Edge:** A connection between two vertices.
- **Adjacent vertices:** Vertices connected directly by an edge.
- **Visited:** A vertex already discovered.
- **Backtracking:** Returning to an earlier vertex when the current path has no unvisited neighbour.
- **Connected component:** A maximal set of vertices that are mutually reachable.
- **Cycle:** A path that starts and ends at the same vertex, without repeating other vertices (under the usual simple-cycle definition).

## 3. How DFS works

Consider the undirected graph with edges:

`0-1, 0-2, 1-3, 1-4, 2-5, 2-6`

```text
             0
           /   \
          1     2
         / \   / \
        3   4 5   6
```

Starting at `0`, one possible DFS traversal is:

`0 1 3 4 2 5 6`

DFS follows the path `0 -> 1 -> 3`. When node 3 has no unvisited neighbour, it backtracks to 1, visits 4, backtracks to 0, and then explores 2.

The exact order depends on the order of neighbours in the adjacency list.

## 4. Recursive DFS algorithm

1. Start at a source vertex.
2. Mark it as visited.
3. Process the vertex.
4. Visit each unvisited neighbour recursively.
5. Return (backtrack) when no unvisited neighbour remains.

### Pseudocode

```text
DFS(graph, vertex, visited):
    visited[vertex] = true
    process(vertex)

    for each neighbour of vertex:
        if visited[neighbour] is false:
            DFS(graph, neighbour, visited)
```

### DFS for a disconnected graph

A DFS starting from one vertex only reaches its connected component. To cover every component:

```text
visited = all false

for each vertex in graph:
    if visited[vertex] is false:
        DFS(graph, vertex, visited)
```

## 5. Iterative DFS using a stack

Recursive DFS uses the call stack. You can also implement DFS explicitly:

```cpp
void iterativeDFS(int start, const vector<vector<int>>& adj) {
    vector<bool> visited(adj.size(), false);
    stack<int> st;

    st.push(start);

    while (!st.empty()) {
        int node = st.top();
        st.pop();

        if (visited[node]) continue;

        visited[node] = true;
        cout << node << " ";

        // Reverse iteration can help preserve the recursive
        // traversal order when neighbours are stored in ascending order.
        for (int i = static_cast<int>(adj[node].size()) - 1; i >= 0; i--) {
            int neighbour = adj[node][i];
            if (!visited[neighbour]) {
                st.push(neighbour);
            }
        }
    }
}
```

Add `#include <stack>` when using this version. Notice that vertices are marked when popped here; duplicate stack entries can occur. An alternative is to mark when pushing, but that can change the traversal order in graphs with cross edges.

## 6. Graph representation

### A. Adjacency list

```cpp
vector<vector<int>> adj(n);

adj[0].push_back(1);
adj[1].push_back(0); // Reverse edge for an undirected graph.
```

Space: `O(V + E)`. It is usually efficient for sparse graphs.

### B. Adjacency matrix

```cpp
vector<vector<int>> adj(n, vector<int>(n, 0));
adj[0][1] = 1;
adj[1][0] = 1;
```

Space: `O(V²)`. Finding all neighbours of a vertex takes `O(V)` time.

## 7. C++ implementation

See **[DFS.cpp](DFS.cpp)** for a complete recursive implementation using:
- `vector<vector<int>>` as an adjacency list
- `vector<bool>` as a visited array
- Recursion for depth-first exploration
- An outer loop to cover disconnected components

Compile and run:

```bash
g++ -std=c++17 DFS.cpp -o dfs
./dfs
```

Expected output for the supplied graph:

```text
DFS traversal: 0 1 3 4 2 5 6
```

## 8. Time and space complexity

Let `V` be the number of vertices and `E` be the number of edges.

| Representation / resource | Complexity |
|---|---:|
| DFS with adjacency list | `O(V + E)` |
| DFS with adjacency matrix | `O(V²)` |
| Visited array | `O(V)` |
| Recursion stack (worst case) | `O(V)` |
| Adjacency list storage | `O(V + E)` |

For a complete traversal of a disconnected graph, each vertex and edge is still examined a constant number of times, so adjacency-list DFS takes `O(V + E)` overall.

## 9. DFS vs BFS

| DFS | BFS |
|---|---|
| Explores deeply, then backtracks | Explores level by level |
| Uses recursion or a stack | Uses a queue |
| Does not generally find shortest paths | Finds shortest paths in unweighted graphs |
| Useful for cycle detection, components, backtracking | Useful for level order and minimum edge count |
| Can be natural for exhaustive path exploration | Can be natural for nearest-target exploration |

## 10. Applications of DFS

1. Finding connected components.
2. Detecting cycles in directed and undirected graphs.
3. Topological sorting (DFS finishing-time method).
4. Finding paths between vertices.
5. Maze solving and backtracking.
6. Finding strongly connected components (Kosaraju's and Tarjan's algorithms).
7. Finding bridges and articulation points.
8. Flood fill and grid-region exploration.
9. Checking whether a graph is bipartite (BFS is also common).
10. Tree traversals such as preorder, inorder and postorder.

## 11. Common mistakes

- Forgetting to mark a node visited.
- Marking a node only after recursively exploring its neighbours.
- Forgetting reverse edges in an undirected graph.
- Assuming a DFS from one source visits a disconnected graph.
- Not accounting for recursion depth on very large or chain-shaped graphs.
- Confusing a directed edge with an undirected edge.
- Assuming the traversal order is unique.
- Using only a parent check for cycle detection in directed graphs; directed cycle detection needs different state tracking (for example, three colours).

## 12. Interview and viva questions with answers

### Basic viva questions

**Q1. What is DFS?**  
DFS is a graph traversal algorithm that explores a path as deeply as possible before backtracking.

**Q2. Which data structure is used in DFS?**  
A stack. Recursive DFS uses the system call stack, while iterative DFS uses an explicit stack.

**Q3. What does LIFO mean?**  
Last In, First Out. The last element inserted is the first one removed.

**Q4. What is backtracking in DFS?**  
It is the process of returning to a previous vertex when the current vertex has no unvisited neighbour to explore.

**Q5. Is DFS a data structure or an algorithm?**  
It is an algorithm. It uses a stack or recursion to manage traversal.

**Q6. What is the time complexity of DFS?**  
With an adjacency list, `O(V + E)`. With an adjacency matrix, `O(V²)`.

**Q7. What is the space complexity of DFS?**  
`O(V)` auxiliary space for the visited structure and worst-case stack/recursion depth.

**Q8. Does DFS find the shortest path?**  
Not in general. BFS finds a shortest path by number of edges in an unweighted graph.

**Q9. What happens if a graph is disconnected?**  
A DFS from one source visits only its component. Run DFS from every unvisited vertex to cover the whole graph.

**Q10. Why do we use a visited array?**  
To avoid revisiting vertices, prevent infinite traversal in cyclic graphs, and avoid repeated work.

### Intermediate interview questions

**Q11. What is the difference between a tree and a graph?**  
A tree is a connected, acyclic, undirected graph. A general graph may contain cycles, may be disconnected, and may be directed.

**Q12. How can DFS detect a cycle in an undirected graph?**  
During DFS, if a visited neighbour is found that is not the current node's parent, a cycle exists (for a standard undirected graph).

**Q13. How can DFS detect a cycle in a directed graph?**  
Use three states: unvisited, visiting (currently in the recursion path), and visited/finished. An edge to a visiting node indicates a directed cycle.

**Q14. What is a DFS tree?**  
It is the tree formed by the discovery edges used by DFS to reach vertices from a starting vertex.

**Q15. What is the difference between a visited array and recursion-stack state?**  
Visited means a vertex has been discovered or processed. Recursion-stack state means it is currently active in the DFS path. Directed cycle detection needs to distinguish these states.

**Q16. Can DFS be implemented without recursion?**  
Yes. Use an explicit stack.

**Q17. What is topological sorting?**  
A linear ordering of vertices in a directed acyclic graph (DAG) such that for every edge `u -> v`, `u` appears before `v`. DFS finishing order, reversed, can produce it.

**Q18. Can DFS be used to find connected components?**  
Yes. Start DFS at each unvisited vertex; each run discovers one connected component in an undirected graph.

### Advanced interview questions

**Q19. What are discovery time and finishing time in DFS?**  
Discovery time is when a vertex is first entered. Finishing time is when all its outgoing/neighbour explorations are complete.

**Q20. What are the four common edge classifications in directed DFS?**  
Tree edges, back edges, forward edges, and cross edges. These classifications are based on DFS discovery/finishing relationships.

**Q21. What is a back edge?**  
An edge from a vertex to one of its ancestors in the active DFS recursion path. In a directed graph, a back edge indicates a cycle.

**Q22. What are strongly connected components (SCCs)?**  
In a directed graph, an SCC is a maximal set of vertices where every vertex can reach every other vertex. Algorithms such as Kosaraju's and Tarjan's use DFS.

**Q23. What is an articulation point?**  
A vertex whose removal (with its incident edges) increases the number of connected components in an undirected graph.

**Q24. What is a bridge?**  
An edge whose removal increases the number of connected components in an undirected graph.

**Q25. What is the risk of recursive DFS on a very deep graph?**  
It may exceed the program's call-stack limit and cause stack overflow. Iterative DFS can avoid relying on the call stack.

**Q26. When would you choose DFS over BFS?**  
DFS is often convenient for exhaustive exploration, backtracking, cycle detection, topological sorting, SCCs, bridges and articulation points. The choice depends on the problem's requirements.

## 13. Intermediate-to-advanced DFS practice questions

Difficulty labels are approximate and can vary by platform.

### Intermediate

| Problem | Main concept |
|---|---|
| [LeetCode 200 — Number of Islands](https://leetcode.com/problems/number-of-islands/) | Grid DFS, connected components |
| [LeetCode 547 — Number of Provinces](https://leetcode.com/problems/number-of-provinces/) | Connected components |
| [LeetCode 733 — Flood Fill](https://leetcode.com/problems/flood-fill/) | Grid traversal |
| [LeetCode 841 — Keys and Rooms](https://leetcode.com/problems/keys-and-rooms/) | Reachability |
| [LeetCode 797 — All Paths From Source to Target](https://leetcode.com/problems/all-paths-from-source-to-target/) | DFS path exploration |
| [LeetCode 130 — Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) | Boundary DFS |
| [LeetCode 133 — Clone Graph](https://leetcode.com/problems/clone-graph/) | DFS + hash map |

### Upper-intermediate

| Problem | Main concept |
|---|---|
| [LeetCode 207 — Course Schedule](https://leetcode.com/problems/course-schedule/) | Directed cycle detection |
| [LeetCode 210 — Course Schedule II](https://leetcode.com/problems/course-schedule-ii/) | DFS topological sorting |
| [LeetCode 802 — Find Eventual Safe States](https://leetcode.com/problems/find-eventual-safe-states/) | Directed graph states / cycle detection |
| [LeetCode 417 — Pacific Atlantic Water Flow](https://leetcode.com/problems/pacific-atlantic-water-flow/) | Reverse grid DFS |
| [LeetCode 695 — Max Area of Island](https://leetcode.com/problems/max-area-of-island/) | Component size |
| [LeetCode 236 — Lowest Common Ancestor of a Binary Tree](https://leetcode.com/problems/lowest-common-ancestor-of-a-binary-tree/) | Recursive tree DFS |

### Advanced

| Problem | Main concept |
|---|---|
| [LeetCode 1192 — Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/) | Bridges, discovery/low times |
| [LeetCode 332 — Reconstruct Itinerary](https://leetcode.com/problems/reconstruct-itinerary/) | DFS + Eulerian path |
| [LeetCode 1466 — Reorder Routes to Make All Paths Lead to the City Zero](https://leetcode.com/problems/reorder-routes-to-make-all-paths-lead-to-the-city-zero/) | DFS on transformed graph |
| [LeetCode 2360 — Longest Cycle in a Graph](https://leetcode.com/problems/longest-cycle-in-a-graph/) | Directed graph traversal / state |
| [LeetCode 1376 — Time Needed to Inform All Employees](https://leetcode.com/problems/time-needed-to-inform-all-employees/) | Tree/graph DFS |
| [LeetCode 104 — Maximum Depth of Binary Tree](https://leetcode.com/problems/maximum-depth-of-binary-tree/) | Recursive tree DFS |

### Suggested solving order

1. Start with 733 and 200 to learn grid traversal.
2. Solve 547 and 841 for graph reachability.
3. Solve 695 and 130 for component exploration and boundary traversal.
4. Solve 207, 210 and 802 for directed cycle detection and topological sorting.
5. Finish with 1192 for discovery time, low-link values and bridges.

## 14. Quick revision

- DFS = Depth-First Search.
- Main idea = Explore deeply, then backtrack.
- Data structure = Stack (explicit or call stack).
- Stack principle = LIFO.
- Adjacency-list time = `O(V + E)`.
- Adjacency-matrix time = `O(V²)`.
- Auxiliary space = `O(V)`.
- Disconnected graph = Start DFS from every unvisited vertex.
- Directed cycle detection = Track active recursion path / three states.
- Common advanced uses = Topological sorting, SCCs, bridges and articulation points.
