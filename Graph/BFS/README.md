# BFS — Breadth-First Search (C++)

A beginner-to-advanced learning resource for **Breadth-First Search (BFS)**, a graph traversal algorithm in Data Structures and Algorithms.

## Project contents

```text
BFS-DSA-Project/
├── BFS.cpp       # Complete C++ implementation
├── notes.md      # Concepts, pseudocode, complexity and practice list
└── README.md     # Project guide
```

## What is BFS?

BFS explores a graph level by level. It uses a **queue (FIFO)** to process the earliest discovered vertex first.

## Features of the implementation

- Graph represented using an adjacency list.
- Queue-based BFS traversal.
- Visited tracking to prevent repeated visits.
- Handles disconnected undirected graphs by starting BFS from each unvisited vertex.
- Written in standard C++.

## Requirements

- A C++ compiler such as GCC or Clang.
- C++11 or later (the included compile command uses C++17).

## Compile and run

### Linux / macOS

```bash
g++ -std=c++17 BFS.cpp -o bfs
./bfs
```

### Windows (MinGW)

```bash
g++ -std=c++17 BFS.cpp -o bfs.exe
bfs.exe
```

## Sample output

```text
BFS traversal: 0 1 2 3 4 5 6
```

The traversal order depends on the order in which neighbours are inserted into the adjacency list.

## Complexity

For an adjacency-list representation:

- **Time:** `O(V + E)` for a complete traversal, where `V` is the number of vertices and `E` is the number of edges.
- **Auxiliary space:** `O(V)` for the visited array and queue.

## Learning path

1. Understand graph terminology and adjacency lists.
2. Trace the queue manually for a small graph.
3. Implement BFS for a connected graph.
4. Extend it to disconnected graphs.
5. Practise shortest paths in unweighted graphs.
6. Learn multi-source BFS and state-space BFS.
7. Explore 0-1 BFS and bitmask BFS.

See **[notes.md](notes.md)** for detailed explanations, pseudocode, common mistakes, BFS vs DFS, and a curated LeetCode practice list.

## Practice problems

A few recommended starting points:

- [102 — Binary Tree Level Order Traversal](https://leetcode.com/problems/binary-tree-level-order-traversal/)
- [994 — Rotting Oranges](https://leetcode.com/problems/rotting-oranges/)
- [542 — 01 Matrix](https://leetcode.com/problems/01-matrix/)
- [127 — Word Ladder](https://leetcode.com/problems/word-ladder/)
- [847 — Shortest Path Visiting All Nodes](https://leetcode.com/problems/shortest-path-visiting-all-nodes/)
- [2290 — Minimum Obstacle Removal to Reach Corner](https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/)

## Important note

BFS finds a shortest path by number of edges in an **unweighted graph** (or equal-weight edges). For general weighted shortest paths, use an appropriate algorithm such as Dijkstra's algorithm; for edge weights 0 and 1, 0-1 BFS is useful.

---

Happy learning and happy coding!
