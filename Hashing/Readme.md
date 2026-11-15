# Hashing in C++

A practical learning module for hashing in Data Structures and
Algorithms, based on the topics and examples started in class.

## Topics covered

-   Meaning and purpose of hashing
-   Hash tables, keys, values, hash functions and collisions
-   Direct addressing
-   Hash-function construction methods:
    -   Division method
    -   Folding method
    -   Mid-square method
-   Collision resolution:
    -   Separate chaining (linear chaining)
    -   Open addressing
    -   Linear probing
    -   Quadratic probing
    -   Double hashing
-   Load factor and rehashing
-   Frequency hashing for arrays and strings
-   Querying precomputed frequencies
-   Time and space complexity
-   Common interview questions and practice problems

## What is hashing?

Hashing maps a key to an index in a table using a hash function. The
table stores information at that index so that it can often be inserted,
searched for, or deleted quickly.

A simple example for non-negative integer keys is:

``` cpp
int index = key % 10;
```

The table has 10 slots, numbered 0 through 9. The remainder is used as
the index.

## Hashing workflow

1.  Choose a table size.
2.  Apply a hash function to a key.
3.  Use the resulting index to access the table.
4.  If two different keys map to the same index, handle the collision.
5.  Search by applying the same hash function and following the
    collision-resolution rule.

## Hash-function methods

### Division method

``` text
h(key) = key % table_size
```

Simple and fast. A prime table size is often a useful choice, depending
on the key distribution.

### Folding method

Split a key into parts, add the parts, and reduce the result to a valid
table index if needed.

Example:

``` text
Key: 123456789
Parts: 123 + 456 + 789
Sum: 1368
Index for table size 100: 68
```

The exact grouping and treatment of the final part must be defined
consistently.

### Mid-square method

Square the key, select one or more middle digits/bits, and use them as
the index (reducing to the table range if necessary).

Example:

``` text
Key: 44
44² = 1936
Select middle two digits: 93
```

The number of selected digits depends on the table size.

> These are methods for generating hash indexes. They do not, by
> themselves, resolve collisions.

## Collision resolution

### Separate chaining (linear chaining)

Each table index stores a collection (commonly a linked list or vector)
of all keys mapped to that index.

### Open addressing

All keys are stored directly inside the table. If a slot is occupied,
the algorithm probes other slots.

-   **Linear probing:** try the next slot.
-   **Quadratic probing:** use quadratic offsets such as 1², 2², 3².
-   **Double hashing:** use a second hash function to determine the step
    size.

## Frequency hashing

Frequency hashing counts how many times each value occurs.

``` cpp
int hash[100000] = {0};

for (int i = 0; i < n; i++) {
    hash[arr[i]]++;
}
```

Then the frequency of a value `x` is available as `hash[x]`, provided
`x` is a valid index.

For characters:

``` cpp
int hash[256] = {0};

for (int i = 0; i < s.size(); i++) {
    hash[(unsigned char)s[i]]++;
}
```

For general or negative integer keys, use a map such as
`unordered_map<int, int>` rather than directly indexing an array.

## Problems covered in the notes

1.  Count the frequency of each array element.
2.  Answer multiple frequency queries.
3.  Count character frequencies in a string.
4.  Find the first non-repeating character.
5.  Find duplicates in an array.
6.  Find the two-sum pair.
7.  Count pairs with a given sum.
8.  Check whether two strings are anagrams.
9.  Find the intersection of two arrays.
10. Find the majority element using a frequency map.

## Complexity overview

For a well-distributed hash table, insertion, lookup and deletion are
typically expected/average `O(1)`. In the worst case, many keys can
collide, making an operation `O(n)`.

  -------------------------------------------------------------------------
  Operation / technique       Expected or average                Worst case
  --------------------- ------------------------- -------------------------
  `unordered_map`                          `O(1)`                    `O(n)`
  lookup/insert/erase                             

  `map`                                `O(log n)`                `O(log n)`
  lookup/insert/erase                             

  Frequency array                          `O(1)`                    `O(1)`
  update/query                                    

  Build frequencies for                    `O(n)`                    `O(n)`
  `n` values                                      

  Separate chaining      `O(1 + α)` under uniform                    `O(n)`
  operation                               hashing 

  Open addressing            Expected `O(1)` at a                    `O(n)`
  operation                  suitable load factor 
  -------------------------------------------------------------------------

Here, `α` is the load factor. For chaining,
`α = number_of_keys / table_size`.

## Important distinction

-   **Hash-function methods** decide the initial index: division,
    folding and mid-square.
-   **Collision-resolution methods** decide what to do when multiple
    keys map to the same index: chaining or open addressing (linear
    probing, quadratic probing, double hashing).
-   **Frequency hashing** is a common use of a direct-index frequency
    array or a hash map.

## Suggested learning sequence

1.  Understand keys, hash functions, table indexes and collisions.
2.  Practise the division method by hand.
3.  Learn separate chaining and open addressing.
4.  Understand linear probing, quadratic probing and double hashing.
5.  Implement frequency arrays for small bounded values.
6.  Use `unordered_map` for general integer keys and character
    frequencies.
7.  Solve frequency, duplicate, pair-sum and string problems.
8.  Study load factor, rehashing and complexity.
