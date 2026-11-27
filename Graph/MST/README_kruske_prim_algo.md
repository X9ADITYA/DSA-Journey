# Minimum Spanning Tree: Prim's & Kruskal's (C++)

Two standalone C++17 implementations of classic MST algorithms.

| File           | Algorithm | Data structures                                          | Time         |
|----------------|-----------|----------------------------------------------------------|--------------|
| `prim.cpp`     | Prim's    | Adjacency list + `priority_queue` (min-heap)             | `O(E log V)` |
| `kruskal.cpp`  | Kruskal's | Sorted edge list + DSU (path compression, union by rank) | `O(E log E)` |

## Requirements
- A C++17 compiler (`g++` 7+ or `clang++`). No external libraries.

## Compile and run
```bash
g++ -std=c++17 -O2 prim.cpp -o prim
./prim

g++ -std=c++17 -O2 kruskal.cpp -o kruskal
./kruskal
```

On Windows (MinGW) run `prim.exe` / `kruskal.exe` instead.

Both use the same sample graph (6 vertices, 7 edges) and print an MST with
total weight **14**:

```
0 - 2 : 3
1 - 2 : 1
1 - 3 : 2
3 - 4 : 2
4 - 5 : 6
```
(Edge order and direction can differ between the two programs.)

## Using the functions
```cpp
vector<Edge> edges = {{0,1,4}, {0,2,3}, {1,2,1}};   // {u, v, weight}
auto [mst, total] = primMST(3, edges, 0);
auto [mst2, total2] = kruskalMST(3, edges);
```

Vertices are labelled `0..n-1`. Graphs are undirected. A disconnected graph
throws `runtime_error`.

## Files
- `prim.cpp` - Prim's algorithm
- `kruskal.cpp` - Kruskal's algorithm
- `NOTES.md` - concepts, complexity, C++ notes, and comparison
