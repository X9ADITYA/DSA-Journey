# Minimum Spanning Tree (MST) — Complete Notes

## 1. Definition

A **Minimum Spanning Tree (MST)** is a subset of edges of a connected, weighted, undirected graph that connects every vertex, contains no cycle, has exactly `V - 1` edges, and has the minimum possible total edge weight.

MST is an optimisation problem on graphs, not a traversal algorithm like BFS or DFS.

## 2. Example

For the sample graph in `MST.cpp`:

| Edge | Weight |
|---|---:|
| 0–1 | 2 |
| 0–3 | 6 |
| 1–2 | 3 |
| 1–3 | 8 |
| 1–4 | 5 |
| 2–4 | 7 |
| 3–4 | 9 |

One MST selects `0–1`, `1–2`, `1–4`, and `0–3`.

Total cost = `2 + 3 + 5 + 6 = 16`.

## 3. Important terms and properties

- **Weighted graph:** Each edge has a cost or weight.
- **Spanning tree:** A connected, acyclic subgraph containing every vertex.
- **MST:** A spanning tree with minimum total edge weight.
- **Cut:** A partition of vertices into two non-empty groups.
- **DSU / Union-Find:** Maintains disjoint sets and supports merging and finding representatives.
- A tree with `V` vertices has exactly `V - 1` edges.
- An MST has no cycle and connects all vertices.
- A graph may have multiple MSTs when edge weights tie.
- If all edge weights are distinct, the MST is unique.
- Negative edge weights are allowed.
- A disconnected graph has no single spanning tree; it can have a minimum spanning forest.

## 4. Prim's Algorithm

### Concept
Prim's algorithm grows one tree from a starting vertex. At each step, it chooses the minimum-weight edge that connects the current tree to a vertex outside it.

**Common data structures:** adjacency list, min-priority queue, visited array.

### Steps
1. Start from any vertex (usually 0).
2. Push `{0, start}` into a min-heap.
3. Extract the minimum-weight candidate.
4. Skip it if its vertex is already visited.
5. Otherwise mark the vertex visited and add its weight to the total.
6. Push edges to all unvisited neighbours.
7. Continue until all vertices are selected or the heap becomes empty.
8. If fewer than `V` vertices were selected, the graph is disconnected.

### Pseudocode
```text
PRIM(graph, start):
    visited = all false
    minHeap = empty
    push (0, start)
    total = 0
    count = 0

    while minHeap is not empty:
        (weight, u) = extract minimum
        if visited[u]: continue

        visited[u] = true
        total += weight
        count += 1

        for each (v, edgeWeight) adjacent to u:
            if not visited[v]:
                push (edgeWeight, v)

    if count != V: report disconnected graph
    else return total
```

### Complexity
- Adjacency list + binary min-heap: `O(E log V)` (often expressed as `O((V+E) log V)`).
- Adjacency matrix + simple minimum-key selection: `O(V²)`.
- The implementation's graph storage is `O(V+E)`; visited is `O(V)` and heap can hold `O(E)` candidates.

## 5. Kruskal's Algorithm

### Concept
Kruskal's algorithm sorts all edges by increasing weight. It adds an edge only when its endpoints belong to different components, preventing cycles.

**Common data structures:** edge list and Disjoint Set Union (DSU).

### Steps
1. Sort edges by increasing weight.
2. Initially place each vertex in its own DSU set.
3. Consider edges in sorted order.
4. Find the representative of both endpoints.
5. If representatives differ, add the edge and union the two sets.
6. If representatives are equal, skip the edge because it creates a cycle.
7. Stop after `V - 1` edges.
8. If fewer than `V - 1` edges were selected, the graph is disconnected.

### Pseudocode
```text
KRUSKAL(V, edges):
    sort edges by increasing weight
    initialise DSU
    total = 0
    count = 0

    for each edge (u, v, w):
        if FIND(u) != FIND(v):
            add edge to MST
            UNION(u, v)
            total += w
            count += 1
        if count == V - 1: break

    if count != V - 1: report disconnected graph
    else return total
```

### DSU operations
- `find(x)`: returns the representative/root of x's set.
- `union(a,b)`: merges the sets containing a and b.
- **Path compression:** makes nodes point closer to the root during find.
- **Union by rank/size:** attaches the smaller/shallower tree under the larger/taller one.

With both optimisations, DSU operations take amortised `O(α(V))`, where α is the very slowly growing inverse Ackermann function.

### Complexity
- Sorting: `O(E log E)`.
- DSU work: `O(E α(V))` total.
- Overall: `O(E log E)`.
- DSU auxiliary space: `O(V)`.

## 6. Prim vs Kruskal

| Prim | Kruskal |
|---|---|
| Grows one tree | Builds and merges a forest |
| Chooses cheapest edge leaving current tree | Chooses cheapest global edge that joins different components |
| Min-heap + adjacency list | Sorting + DSU |
| Often convenient with dense graphs / matrix implementation | Often convenient with sparse graphs |
| Does not require DSU | Uses DSU |

Both are greedy algorithms and find an MST for a connected weighted undirected graph.

## 7. MST vs shortest path tree

An MST minimises the **sum of all selected tree-edge weights**. A shortest path tree minimises distances from one chosen source to each reachable vertex. An MST does not necessarily provide shortest paths between pairs of vertices.

For unweighted shortest paths, use BFS. For non-negative weighted shortest paths, study Dijkstra's algorithm.

## 8. Applications

1. Designing low-cost computer and communication networks.
2. Connecting cities with minimum total road or cable cost.
3. Planning electrical grids, pipelines and utility networks.
4. Clustering and image segmentation.
5. Building network backbones.
6. Approximation algorithms for some network optimisation problems.

## 9. Common mistakes

- Applying standard Prim/Kruskal directly to a directed graph.
- Forgetting the `V - 1` edge condition.
- Adding a cycle-forming edge in Kruskal.
- Forgetting to check disconnected graphs.
- Confusing MST with Dijkstra's shortest path tree.
- Assuming edge weights must be positive.
- Using a max-heap instead of a min-heap in Prim.
- Marking a Prim vertex visited when pushing it rather than when selecting it from the heap.
- Forgetting path compression / union by rank in DSU.

## 10. C++ implementation

See [MST.cpp](MST.cpp). It contains:
- Prim's algorithm with an adjacency list and min-priority queue.
- Kruskal's algorithm with an edge list and DSU using path compression and union by rank.
- Disconnected-graph checks.

Compile and run:
```bash
g++ -std=c++17 MST.cpp -o mst
./mst
```

Both algorithms report a total MST weight of `16` for the sample graph.

---

# 11. Viva and interview questions with answers

## Basic questions

**Q1. What is a Minimum Spanning Tree?**  
A spanning tree of a connected weighted undirected graph whose total edge weight is minimum.

**Q2. How many edges are present in an MST?**  
Exactly `V - 1`.

**Q3. Can an MST contain a cycle?**  
No. A spanning tree is acyclic.

**Q4. Name two algorithms to find an MST.**  
Prim's and Kruskal's algorithms.

**Q5. Is MST a greedy algorithm problem?**  
Yes. Both standard algorithms make safe greedy choices.

**Q6. Can a graph have multiple MSTs?**  
Yes, especially when equal-weight alternatives exist.

**Q7. When is an MST guaranteed to be unique?**  
When all edge weights are distinct.

**Q8. Can MST contain negative edge weights?**  
Yes. Negative weights are valid.

**Q9. What if the graph is disconnected?**  
A single spanning tree does not exist. We can find a minimum spanning forest.

**Q10. What is a spanning tree?**  
A connected, acyclic subgraph that contains all vertices.

## Intermediate questions

**Q11. Explain Prim's algorithm.**  
It starts at a vertex and repeatedly adds the minimum-weight edge connecting the current tree to an unvisited vertex.

**Q12. Explain Kruskal's algorithm.**  
It sorts edges by weight and adds an edge if its endpoints are in different DSU components.

**Q13. Which data structure is used in Prim's algorithm?**  
A min-priority queue (min-heap), usually with an adjacency list.

**Q14. Which data structure is used in Kruskal's algorithm?**  
Disjoint Set Union (Union-Find), along with a sorted edge list.

**Q15. What is DSU?**  
A data structure that maintains disjoint sets and supports finding a representative and merging sets.

**Q16. What is path compression?**  
An optimisation that flattens the DSU parent structure during find operations.

**Q17. What is union by rank?**  
An optimisation that attaches the lower-rank root under the higher-rank root.

**Q18. What is Kruskal's time complexity?**  
`O(E log E)`, dominated by sorting.

**Q19. What is Prim's time complexity with a binary heap and adjacency list?**  
`O(E log V)` for a connected graph, commonly stated with equivalent heap-based bounds.

**Q20. Does Prim require DSU?**  
No. The common implementation uses a visited array and min-heap.

**Q21. Why does Kruskal skip an edge whose endpoints have the same DSU root?**  
They are already connected; adding the edge would create a cycle.

**Q22. Can Prim start from any vertex?**  
Yes, if the graph is connected.

## Advanced questions

**Q23. What is the cut property?**  
A minimum-weight edge crossing any cut is safe to include in some MST. With tied weights, it may not be in every MST.

**Q24. What is the cycle property?**  
A uniquely heaviest edge on a cycle cannot belong to an MST.

**Q25. Differentiate MST and Dijkstra's algorithm.**  
MST minimises total tree weight; Dijkstra finds shortest paths from a source when edge weights are non-negative.

**Q26. Which is better, Prim or Kruskal?**  
Neither is always better. The choice depends on graph density, representation and implementation.

**Q27. What is a minimum spanning forest?**  
A collection of MSTs, one for each connected component.

**Q28. Why does Kruskal produce an MST?**  
It repeatedly adds a lightest safe edge joining two components, following the cut property, without creating cycles.

**Q29. Why does Prim produce an MST?**  
At each step it selects a minimum-weight edge crossing the cut between the current tree and the remaining vertices.

**Q30. What is the inverse Ackermann function in DSU?**  
A very slowly growing function; optimised DSU operations take amortised `O(α(V))` time.

**Q31. What if all edges have equal weight?**  
Every spanning tree has the same total weight, so every spanning tree is an MST.

**Q32. Does an MST always give the shortest route between every pair of vertices?**  
No. It minimises total selected edge weight, not every pairwise path distance.

---

# 12. Intermediate-to-advanced practice questions

MST has fewer direct platform problems than general graph traversal. These problems cover MST and closely related DSU techniques. Difficulty labels are approximate.

## Intermediate

| Problem | Main pattern |
|---|---|
| [LeetCode 1584 — Min Cost to Connect All Points](https://leetcode.com/problems/min-cost-to-connect-all-points/) | Direct MST: Prim or Kruskal |
| [LeetCode 1135 — Connecting Cities With Minimum Cost](https://leetcode.com/problems/connecting-cities-with-minimum-cost/) | Direct MST |
| [LeetCode 1489 — Find Critical and Pseudo-Critical Edges in MST](https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/) | MST edge classification |

## Advanced

| Problem | Main pattern |
|---|---|
| [LeetCode 1579 — Remove Max Number of Edges to Keep Graph Fully Traversable](https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/) | DSU, shared connectivity |
| [LeetCode 1697 — Checking Existence of Edge Length Limited Paths](https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/) | Offline sorting + DSU |
| [LeetCode 1102 — Path With Maximum Minimum Value](https://leetcode.com/problems/path-with-maximum-minimum-value/) | Threshold connectivity / DSU-style reasoning |

### Suggested order
1. Solve 1584 to practise Prim and Kruskal.
2. Solve 1135 to reinforce MST construction.
3. Solve 1579 to strengthen DSU.
4. Solve 1697 for offline sorting with DSU.
5. Attempt 1489 for advanced MST edge analysis.

## 13. Quick revision

- MST = Minimum Spanning Tree.
- Graph = Weighted and undirected.
- Edges in MST = `V - 1`.
- MST = Connected + acyclic + minimum total weight.
- Prim = Grow one tree with a min-heap.
- Kruskal = Sort edges + DSU.
- Prim (heap + adjacency list) = `O(E log V)` commonly.
- Kruskal = `O(E log E)`.
- DSU optimisations = Path compression + union by rank/size.
- Disconnected graph = Minimum spanning forest.
- MST is not the same as a shortest path tree.
