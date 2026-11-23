# DFS — Depth-First Search (C++)

A practical learning project for **Depth-First Search (DFS)**, a fundamental graph traversal algorithm in Data Structures and Algorithms.

## Project contents

```text
DFS-DSA-Project/
├── DFS.cpp       # Complete recursive C++ implementation
├── notes.md      # Theory, pseudocode, viva/interview Q&A and practice list
└── README.md     # Project guide
```

## What is DFS?

DFS explores one path as deeply as possible before backtracking. It uses a stack, either explicitly or through recursion.

## Features

- Adjacency-list graph representation.
- Recursive DFS implementation.
- Visited array to prevent repeated traversal.
- Traverses disconnected components.
- Standard C++ implementation.

## Requirements

- GCC, Clang, or another C++ compiler.
- C++11 or later (the command below uses C++17).

## Compile and run

### Linux / macOS

```bash
g++ -std=c++17 DFS.cpp -o dfs
./dfs
```

### Windows (MinGW)

```bash
g++ -std=c++17 DFS.cpp -o dfs.exe
dfs.exe
```

## Sample output

```text
DFS traversal: 0 1 3 4 2 5 6
```

The order depends on the order in which neighbours are inserted into the adjacency list.

## Complexity

For an adjacency-list representation:

- **Time:** `O(V + E)` for a complete traversal.
- **Auxiliary space:** `O(V)` for visited tracking and the worst-case recursion stack.

Here, `V` is the number of vertices and `E` is the number of edges.

## What you will learn

1. Graph representation using adjacency lists.
2. Recursive DFS and backtracking.
3. Iterative DFS using a stack.
4. Traversal of disconnected graphs.
5. DFS applications such as cycle detection and connected components.
6. Advanced topics such as topological sorting, strongly connected components, bridges and articulation points.

## Viva and interview preparation

The accompanying **[notes.md](notes.md)** includes:
- Basic, intermediate and advanced viva questions with answers.
- DFS pseudocode and complexity analysis.
- Common implementation mistakes.
- A curated intermediate-to-advanced LeetCode problem list.

## Important note

Recursive DFS can use `O(V)` call-stack space in the worst case. For very deep graphs, consider iterative DFS with an explicit stack to avoid call-stack overflow.

---

Happy learning and happy coding!
