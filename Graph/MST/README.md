# Minimum Spanning Tree (MST) — C++

A DSA learning project covering the two major greedy algorithms for finding a **Minimum Spanning Tree**: Prim's Algorithm and Kruskal's Algorithm.

## Project structure

```text
MST-DSA-Project/
├── MST.cpp       # Prim's and Kruskal's implementations
├── notes.md      # Theory, pseudocode, complexity, viva Q&A and practice
└── README.md     # Project documentation
```

## What is an MST?

An MST is a minimum-weight set of edges connecting every vertex in a connected, weighted, undirected graph without cycles. It contains exactly `V - 1` edges.

## Implementations

### Prim's Algorithm
- Adjacency list and min-priority queue.
- Grows one tree from a starting vertex.
- Time: `O(E log V)` with a binary heap.

### Kruskal's Algorithm
- Sorts an edge list by weight.
- Uses DSU (Union-Find) with path compression and union by rank.
- Time: `O(E log E)`.

Both implementations detect disconnected graphs.

## Requirements

- GCC, Clang, or another C++ compiler.
- C++17 recommended.

## Compile and run

Linux / macOS:
```bash
g++ -std=c++17 MST.cpp -o mst
./mst
```

Windows (MinGW):
```bash
g++ -std=c++17 MST.cpp -o mst.exe
mst.exe
```

## Sample result

Both algorithms find an MST with total weight:

```text
Total MST weight: 16
```

The selected edges and their display order may differ.

## Complexity

| Algorithm | Time |
|---|---:|
| Prim (adjacency list + binary heap) | `O(E log V)` |
| Kruskal (sorting + DSU) | `O(E log E)` |

`V` is the number of vertices and `E` is the number of edges.

## Learning checklist

1. Understand weighted, undirected graphs.
2. Learn spanning trees and the `V - 1` edge property.
3. Implement Prim using a min-heap.
4. Learn DSU: `find`, `union`, path compression and union by rank.
5. Implement Kruskal.
6. Compare MST with shortest path trees.
7. Practise MST and DSU problems.

See [notes.md](notes.md) for detailed theory, pseudocode, applications, common mistakes, 32 viva/interview questions with answers, and intermediate-to-advanced practice problems.

## Important note

MST minimises the total cost of connecting all vertices. It does not generally find shortest paths from a source. For shortest paths, study BFS (unweighted graphs) and Dijkstra (non-negative weighted edges).

---

Happy learning and happy coding!
