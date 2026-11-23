# Breadth-First Search (BFS) — Notes

## 1. What is BFS?

Breadth-First Search (BFS) is a graph traversal algorithm that explores a graph **level by level**. It visits a starting vertex, then all its unvisited neighbours, then the neighbours of those vertices, and continues until all reachable vertices have been visited.

BFS uses a **Queue**, which follows FIFO (First In, First Out).

BFS is commonly studied under:

- Data Structures and Algorithms (DSA)
- Graphs
- Graph Traversal Algorithms
- Tree Traversal (level-order traversal is BFS)

> BFS is an algorithm, not a data structure. It commonly uses a queue and a visited array/set.

## 2. Important terminology

- **Vertex / Node:** An individual point in a graph.
- **Edge:** A connection between two vertices.
- **Adjacent vertices:** Vertices directly connected by an edge.
- **Visited:** A vertex that has already been discovered/processed.
- **Connected component:** A maximal group of vertices where every vertex is reachable from every other vertex in that group.
- **Level / Distance:** In an unweighted graph, the minimum number of edges from the BFS source.

## 3. How BFS works

Suppose the graph has these edges:

`0-1, 0-2, 1-3, 1-4, 2-5, 2-6`

Starting from vertex `0`, one possible traversal is:

```text
             0
           /   \
          1     2
         / \   / \
        3   4 5   6
```

Levels:

- Level 0: `0`
- Level 1: `1, 2`
- Level 2: `3, 4, 5, 6`

BFS traversal: `0 1 2 3 4 5 6`

The exact order among vertices on the same level depends on the order in which neighbours are stored in the adjacency list.

## 4. Queue operations in BFS

1. Create a queue and a visited array.
2. Mark the source vertex as visited.
3. Insert the source into the queue.
4. While the queue is not empty:
   - Remove the front vertex.
   - Process or print it.
   - Visit each unvisited neighbour.
   - Mark each neighbour visited and insert it into the queue.
5. Stop when the queue becomes empty.

**Important:** Mark a vertex visited when it is enqueued, not later when it is dequeued. This prevents the same vertex from being inserted multiple times.

## 5. Pseudocode

```text
BFS(graph, source):
    create an empty queue
    create visited array and initialise all entries to false

    visited[source] = true
    enqueue(source)

    while queue is not empty:
        current = dequeue()
        process(current)

        for each neighbour of current:
            if visited[neighbour] is false:
                visited[neighbour] = true
                enqueue(neighbour)
```

### BFS for a disconnected graph

A single BFS only visits vertices reachable from its source. To traverse every component:

```text
visited = all false

for each vertex in graph:
    if visited[vertex] is false:
        BFS from that vertex using the same visited array
```

## 6. Graph representation

### A. Adjacency list

Each vertex stores a list of its neighbours.

```cpp
vector<vector<int>> adj(n);

adj[0].push_back(1);
adj[1].push_back(0); // Add reverse edge for an undirected graph.
```

Space: `O(V + E)`.

This is generally a good choice for sparse graphs and BFS.

### B. Adjacency matrix

A `V x V` matrix stores whether an edge exists between each pair of vertices.

```cpp
vector<vector<int>> adj(n, vector<int>(n, 0));
adj[0][1] = 1;
adj[1][0] = 1;
```

Space: `O(V²)`. Scanning all possible neighbours of a vertex takes `O(V)`.

## 7. C++ implementation

See **[BFS.cpp](BFS.cpp)** for a complete program using:

- `vector<vector<int>>` for the adjacency list
- `queue<int>` for FIFO processing
- `vector<bool>` for visited tracking
- An outer loop to handle disconnected components

Compile and run:

```bash
g++ -std=c++17 BFS.cpp -o bfs
./bfs
```

Expected output:

```text
BFS traversal: 0 1 3 4 2 5 6
```

Note: The exact traversal depends on neighbour insertion order. With the edge order in `BFS.cpp`, the output is `0 1 2 3 4 5 6` because both neighbours of 0 are queued before either is processed.

## 8. Time and space complexity

Let `V` be the number of vertices and `E` the number of edges.

| Representation / operation | Complexity |
|---|---:|
| BFS with adjacency list | `O(V + E)` |
| BFS with adjacency matrix | `O(V²)` |
| Queue space (worst case) | `O(V)` |
| Visited array | `O(V)` |
| Adjacency list storage | `O(V + E)` |

For a complete traversal of a disconnected graph using an adjacency list, every vertex and edge is examined a constant number of times, so the total time remains `O(V + E)`.

## 9. BFS vs DFS

| BFS | DFS |
|---|---|
| Breadth / level-wise exploration | Depth-wise exploration |
| Uses a queue | Uses recursion or a stack |
| Finds shortest paths in unweighted graphs | Does not generally guarantee shortest paths |
| Useful for level order and minimum edge count | Useful for backtracking, cycle detection and components |

## 10. Applications of BFS

1. Shortest path in an unweighted graph.
2. Level-order traversal of a binary tree.
3. Finding connected components.
4. Checking whether a graph is bipartite.
5. Finding minimum moves in puzzles and grids.
6. Finding the nearest target in an unweighted state space.
7. Multi-source spreading problems, such as Rotting Oranges.
8. Finding minimum transformations in word-ladder-style problems.

## 11. Common mistakes

- Forgetting to mark the source as visited.
- Marking vertices visited only after dequeuing them.
- Forgetting to add reverse edges for an undirected graph.
- Assuming one BFS visits a disconnected graph completely.
- Using BFS for weighted shortest paths without checking edge weights.
- Mixing up queue operations: BFS uses `push()` and `pop()` with `front()`.
- Assuming one fixed traversal order when adjacency ordering can vary.
- Confusing the number of vertices with the largest vertex label; arrays indexed by labels need an appropriate size or a mapping.

## 12. Intermediate-to-advanced BFS practice questions

The following problems are grouped by the main BFS pattern. Difficulty labels are approximate and can vary by platform.

### Intermediate

| Problem | Main concept / pattern |
|---|---|
| [LeetCode 102 — Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/) | Basic level-order BFS |
| [LeetCode 1091 — Shortest Path in Binary Matrix](https://leetcode.com/problems/shortest-path-in-binary-matrix/) | Grid BFS, shortest path |
| [LeetCode 994 — Rotting Oranges](https://leetcode.com/problems/rotting-oranges/) | Multi-source BFS |
| [LeetCode 542 — 01 Matrix](https://leetcode.com/problems/01-matrix/) | Multi-source BFS, distance |
| [LeetCode 752 — Open the Lock](https://leetcode.com/problems/open-the-lock/) | State-space BFS |
| [LeetCode 1162 — As Far from Land as Possible](https://leetcode.com/problems/as-far-from-land-as-possible/) | Multi-source BFS |
| [LeetCode 797 — All Paths From Source to Target](https://leetcode.com/problems/all-paths-from-source-to-target/) | Graph paths (DFS is also natural) |

### Upper-intermediate

| Problem | Main concept / pattern |
|---|---|
| [LeetCode 127 — Word Ladder](https://leetcode.com/problems/word-ladder/) | Shortest transformation path |
| [LeetCode 752 — Open the Lock](https://leetcode.com/problems/open-the-lock/) | Visited-state modelling |
| [LeetCode 863 — All Nodes Distance K in Binary Tree](https://leetcode.com/problems/all-nodes-distance-k-in-binary-tree/) | Convert tree to graph + BFS |
| [LeetCode 133 — Clone Graph](https://leetcode.com/problems/clone-graph/) | BFS + mapping original to clone |
| [LeetCode 130 — Surrounded Regions](https://leetcode.com/problems/surrounded-regions/) | Boundary-started BFS |
| [LeetCode 207 — Course Schedule](https://leetcode.com/problems/course-schedule/) | Topological sorting / Kahn's BFS |

### Advanced

| Problem | Main concept / pattern |
|---|---|
| [LeetCode 126 — Word Ladder II](https://leetcode.com/problems/word-ladder-ii/) | BFS levels + path reconstruction |
| [LeetCode 815 — Bus Routes](https://leetcode.com/problems/bus-routes/) | BFS on route/state graph |
| [LeetCode 847 — Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/) | Bitmask BFS |
| [LeetCode 1293 — Shortest Path in a Grid with Obstacles Elimination](https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/) | BFS with extra state |
| [LeetCode 1129 — Shortest Path with Alternating Colors](https://leetcode.com/problems/shortest-path-with-alternating-colors/) | BFS with state / edge colour |
| [LeetCode 2290 — Minimum Obstacle Removal to Reach Corner](https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/) | 0-1 BFS |
| [LeetCode 934 — Shortest Bridge](https://leetcode.com/problems/shortest-bridge/) | DFS/BFS + multi-source expansion |

### Suggested solving order

1. Start with 102 and 1091 to learn ordinary BFS.
2. Solve 994, 542 and 1162 to master multi-source BFS.
3. Solve 752 and 127 to learn state-space BFS.
4. Solve 863 and 133 to practise tree/graph modelling.
5. Solve 207 to understand Kahn's algorithm.
6. Finish with 126, 847, 1293 and 2290 for advanced state handling.

## 13. Quick revision

- BFS = Breadth-First Search.
- Data structure used = Queue.
- Queue principle = FIFO.
- Main use = Level-wise traversal.
- Unweighted shortest path = BFS.
- Adjacency-list complexity = `O(V + E)`.
- Disconnected graph = Start BFS from every unvisited vertex.
- Multi-source BFS = Put all starting sources into the queue initially.
- 0-1 BFS = Deque, for edge weights 0 and 1.
