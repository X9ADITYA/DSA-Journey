# Hashing --- Detailed Notes, Examples, Complexity & Interview Questions

These notes organise the hashing topics shown in the class material and
extend them with common DSA implementations and interview practice.

------------------------------------------------------------------------

## 1. What is hashing?

Hashing is a technique that maps a key to an index in a table using a
hash function.

The purpose is to make operations such as searching, insertion and
deletion efficient on average.

### Important terms

  Term                 Meaning
  -------------------- ----------------------------------------------------------
  Key                  The value used to identify or access an item
  Hash function        A function that converts a key into a table index
  Hash table           The storage structure in which data is placed
  Hash value / index   The calculated table position
  Collision            Two different keys map to the same index
  Bucket               A table position; in chaining it may hold multiple items
  Load factor          Number of stored keys divided by table capacity

Example:

``` text
Table size = 10
Hash function: h(key) = key % 10

h(2)  = 2
h(5)  = 5
h(16) = 6
h(28) = 8
h(18) = 8
```

The keys `28` and `18` both map to index `8`. This is a collision.

A good hash function distributes keys across the table reasonably
evenly. A hash function cannot guarantee that collisions never happen
when the key range is larger than the table.

------------------------------------------------------------------------

## 2. Types and methods in hashing

It is useful to separate two ideas:

1.  **Hash-function construction:** how the initial table index is
    calculated.
2.  **Collision resolution:** what happens when the calculated slot is
    already occupied.

### A. Direct addressing

In direct addressing, the key itself is used as the array index.

``` cpp
int frequency[100] = {0};
frequency[x]++;
```

This is suitable when keys are non-negative integers from a small, known
range.

**Advantages** - Very simple. - `O(1)` access and update. - No hash
collisions for distinct valid direct indexes.

**Disadvantages** - Can waste a lot of memory when the key range is
large and only a few keys occur. - Cannot directly index negative
values. - Requires a known, manageable key range.

### B. Division method

Formula:

``` text
h(key) = key % table_size
```

Example with table size 10:

    Key Calculation     Index
  ----- ------------- -------
      2 `2 % 10`            2
      5 `5 % 10`            5
     16 `16 % 10`           6
     28 `28 % 10`           8
     13 `13 % 10`           3
     39 `39 % 10`           9
     38 `38 % 10`           8
     48 `48 % 10`           8
     18 `18 % 10`           8

**Advantages** - Easy to calculate. - Fast. - Simple to implement.

**Disadvantages** - Poor table-size choices or patterns in keys can
cause many collisions. - The remainder depends on the chosen table
size. - It does not solve collisions; a separate collision strategy is
required.

A prime table size is often chosen to help avoid some regular patterns,
but it is not a universal guarantee of good distribution.

### C. Folding method

Split the key into groups, add the groups, and use the result (usually
reduced to the table range) as the index.

Example:

``` text
Key = 123456789
Groups = 123, 456, 789
Sum = 123 + 456 + 789 = 1368
For table size 100: index = 1368 % 100 = 68
```

**Advantages** - Can use digits from across a long key. - Useful for
long numeric identifiers. - Simple arithmetic.

**Disadvantages** - Different keys can produce the same sum. - Result
depends on how groups are split. - Poor grouping can lead to uneven
distribution.

### D. Mid-square method

Square the key and take selected middle digits or bits as the hash
value. Reduce to the table range if necessary.

Example:

``` text
Key = 44
44 × 44 = 1936
Middle two digits = 93
```

For a table with 100 slots, index 93 is valid.

**Advantages** - Digits from different parts of the key can influence
the result. - Can spread some patterns better than simply taking the
last digit.

**Disadvantages** - Squaring may produce large values. - Selecting the
middle portion requires a consistent rule. - It can still produce
collisions and is not automatically uniform.

> Division, folding and mid-square are hash-function methods, not
> collision-resolution methods.

------------------------------------------------------------------------

## 3. Collision resolution techniques

A collision occurs when two or more different keys produce the same hash
index.

### A. Separate chaining (linear chaining)

Each table slot stores a collection of entries that hash to that index.
A linked list is a traditional implementation; a vector can also be used
for learning.

Example using `h(key) = key % 10`:

``` text
Index 2:  2
Index 5:  5
Index 6:  16
Index 8:  28 -> 38 -> 48 -> 18
Index 9:  39
```

Illustrative C++ structure:

``` cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    const int SIZE = 10;
    vector<int> table[SIZE];

    int values[] = {2, 5, 16, 28, 13, 39, 38, 48, 18};

    for (int x : values) {
        int index = x % SIZE;
        table[index].push_back(x);
    }

    for (int i = 0; i < SIZE; i++) {
        cout << i << ": ";
        for (int x : table[i]) {
            cout << x << " -> ";
        }
        cout << "NULL\n";
    }

    return 0;
}
```

**Advantages** - Simple collision handling. - The table can store more
keys than the number of buckets. - Deletion is relatively
straightforward. - Performance degrades gradually as chains become
longer.

**Disadvantages** - Extra memory is needed for links or bucket
containers. - Pointer-based linked lists can have poor cache locality. -
A long chain makes lookup slow.

**Complexity** - Expected search/insert/delete: `O(1 + α)` with a good
hash function, where `α = n / m`. - Worst case: `O(n)` if all keys land
in one bucket. - Space: `O(m + n)` for `m` buckets and `n` stored keys.

### B. Open addressing

All entries are stored in the hash table array itself. When a slot is
occupied, the algorithm probes other slots.

The table needs an empty slot for insertion. Its load factor must remain
below 1.

#### 1. Linear probing

Try the next slot until an empty slot is found.

Formula:

``` text
h(key, i) = (h(key) + i) % table_size
```

where `i = 0, 1, 2, ...`.

Example with table size 10 and `h(key) = key % 10`:

-   `28` goes to index 8.
-   `38` first tries index 8, which is occupied, then index 9.
-   `48` tries 8, then 9, then 0.

**Advantages** - Easy to implement. - No separate linked-list storage. -
Good cache locality because nearby slots are checked.

**Disadvantages** - Causes primary clustering: long groups of occupied
slots form. - Search can become slow as the table fills. - Deletion
needs special handling (often a tombstone marker), not simply marking a
slot empty.

#### 2. Quadratic probing

Probe using quadratic offsets.

A common form is:

``` text
h(key, i) = (h(key) + c1*i + c2*i*i) % table_size
```

A simplified example uses offsets `0², 1², 2², 3², ...`.

**Advantages** - Reduces primary clustering compared with linear
probing. - Stores all entries in the table itself.

**Disadvantages** - May still have secondary clustering: keys with the
same initial hash follow the same probe sequence. - Depending on table
size and constants, it may not visit every slot. - Choosing table size
and constants correctly matters.

#### 3. Double hashing

Use a second hash function to determine the step size.

``` text
h(key, i) = (h1(key) + i * h2(key)) % table_size
```

The second hash must produce a non-zero step that is relatively prime to
the table size if the probe sequence is to visit every slot.

**Advantages** - Usually reduces clustering more effectively than linear
or quadratic probing. - Probe sequences can differ for keys with the
same first hash.

**Disadvantages** - More complex to implement. - Requires careful design
of both hash functions. - Still has worst-case `O(n)` operations.

### Collision-resolution comparison

  -----------------------------------------------------------------------
  Method            Main idea         Advantages        Disadvantages
  ----------------- ----------------- ----------------- -----------------
  Separate chaining Store a           Easy deletion;    Extra memory;
                    collection at     can exceed bucket long chains
                    each bucket       count             

  Linear probing    Check next slot   Simple;           Primary
                                      cache-friendly    clustering

  Quadratic probing Check quadratic   Reduces primary   Secondary
                    offsets           clustering        clustering; probe
                                                        coverage concerns

  Double hashing    Use second hash   Better spread of  More complex;
                    as step size      probe sequences   second hash must
                                                        be chosen
                                                        carefully
  -----------------------------------------------------------------------

------------------------------------------------------------------------

## 4. Load factor and rehashing

Load factor measures how full a hash table is.

``` text
α = number of stored keys / number of table slots
```

For example, if 7 keys are stored in a table with 10 slots:

``` text
α = 7 / 10 = 0.7
```

A high load factor generally increases collisions and probing work.

**Rehashing** means creating a larger table and inserting the existing
keys again using the new table size/hash calculation.

Rehashing is used to keep hash-table operations efficient as the number
of entries grows. The exact load-factor threshold depends on the
implementation.

------------------------------------------------------------------------

## 5. Frequency hashing --- arrays

### Problem 1: Count frequency of each value

**Example**

``` text
Input array: 1 3 2 1 3 2 1
Frequency:
1 -> 3
2 -> 2
3 -> 2
```

Code for values in the range `0` to `100000`:

``` cpp
#include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    const int MAX_VALUE = 100000;
    int hash[MAX_VALUE + 1] = {0};

    for (int i = 0; i < n; i++) {
        hash[arr[i]]++;
    }

    for (int x = 0; x <= MAX_VALUE; x++) {
        if (hash[x] > 0) {
            cout << x << " -> " << hash[x] << '\n';
        }
    }

    return 0;
}
```

For production-quality standard C++, a `vector<int>` with a fixed size
is preferable to a variable-length array such as `int arr[n]`, which is
not standard C++.

**Complexity** - Building the frequency table: `O(n)`. - Querying one
valid value: `O(1)`. - Frequency-array space: `O(U)`, where `U` is the
size of the value range. - Printing all possible indexes as above:
`O(U)`.

### Problem 2: Answer multiple frequency queries

If the array has already been preprocessed, each query can be answered
in constant time.

``` cpp
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    const int MAX_VALUE = 100000;
    vector<int> hash(MAX_VALUE + 1, 0);

    for (int x : arr) {
        hash[x]++;
    }

    int q;
    cin >> q;

    while (q--) {
        int number;
        cin >> number;

        if (number >= 0 && number <= MAX_VALUE) {
            cout << hash[number] << '\n';
        } else {
            cout << 0 << '\n';
        }
    }

    return 0;
}
```

**Complexity** - Preprocessing: `O(n + U)` including initialization of
the frequency array. - Each query: `O(1)`. - `q` queries: `O(q)` after
preprocessing. - Space: `O(U)` for the frequency array, plus `O(n)` for
the input vector.

> In a fixed-size global array, initialization and storage details
> differ from a dynamically sized vector. Always state whether the cost
> of initializing the table is included.

### When to use an array or a map

Use a frequency array when: - Values are integers. - The value range is
small and known. - Values can safely be used as indexes.

Use `unordered_map` when: - Values may be negative or very large. - The
range is unknown or sparse. - You want to store counts for only keys
that occur.

------------------------------------------------------------------------

## 6. Frequency hashing --- strings

### Problem 3: Count each character in a string

``` cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s;
    cin >> s;

    int hash[256] = {0};

    for (char ch : s) {
        hash[(unsigned char)ch]++;
    }

    int q;
    cin >> q;

    while (q--) {
        char ch;
        cin >> ch;
        cout << hash[(unsigned char)ch] << '\n';
    }

    return 0;
}
```

Example:

``` text
String: abcdabehf
Queries:
a -> 2
g -> 0
h -> 1
b -> 2
c -> 1
```

**Complexity** - Preprocessing: `O(n + 256)`, which is `O(n)` for a
fixed byte alphabet. - Each query: `O(1)`. - Space: `O(256) = O(1)` for
the fixed table.

The `unsigned char` conversion ensures the index is in the range `0` to
`255`.

This example handles byte values, not full Unicode characters.

------------------------------------------------------------------------

## 7. Using `unordered_map` for general keys

For values outside a small fixed range, use a hash map.

### Problem 4: Count frequencies using `unordered_map`

``` cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> arr(n);
    unordered_map<int, int> freq;

    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        freq[arr[i]]++;
    }

    for (auto p : freq) {
        cout << p.first << " -> " << p.second << '\n';
    }

    return 0;
}
```

**Complexity** - Expected build time: `O(n)`. - Worst-case build time:
`O(n²)` under severe collisions. - Space: `O(k)`, where `k` is the
number of distinct values. - Iterating over the map: `O(k)`.

The iteration order of `unordered_map` is not sorted and is not
guaranteed to be the same across runs.

------------------------------------------------------------------------

## 8. Common hashing interview problems

### Problem 5: Find duplicates in an array

**Idea:** Count each value. A value is a duplicate if its frequency is
greater than 1.

``` cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {1, 2, 3, 2, 4, 1, 5};
    unordered_map<int, int> freq;

    for (int x : arr) {
        freq[x]++;
    }

    for (auto p : freq) {
        if (p.second > 1) {
            cout << p.first << " ";
        }
    }

    return 0;
}
```

Expected time: `O(n)`. Space: `O(k)`.

### Problem 6: Two Sum

**Question:** Given an array and a target, find two different elements
whose sum equals the target.

**Idea:** For each number `x`, check whether `target - x` has already
been seen.

``` cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {2, 7, 11, 15};
    int target = 9;

    unordered_map<int, int> seen;

    for (int i = 0; i < (int)arr.size(); i++) {
        int need = target - arr[i];

        if (seen.find(need) != seen.end()) {
            cout << seen[need] << " " << i << '\n';
            return 0;
        }

        seen[arr[i]] = i;
    }

    cout << "No pair found\n";
    return 0;
}
```

Expected time: `O(n)`. Space: `O(n)`.

Checking before inserting the current value ensures that the same array
element is not used twice.

### Problem 7: First non-repeating character

**Idea:** Count character frequencies, then scan the string in original
order and return the first character with frequency 1.

``` cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string s = "swiss";
    int freq[256] = {0};

    for (unsigned char ch : s) {
        freq[ch]++;
    }

    for (unsigned char ch : s) {
        if (freq[ch] == 1) {
            cout << ch << '\n';
            return 0;
        }
    }

    cout << "No non-repeating character\n";
    return 0;
}
```

Expected time: `O(n + 256) = O(n)`. Auxiliary space: `O(256) = O(1)`.

### Problem 8: Check whether two strings are anagrams

**Idea:** If both strings contain the same characters with the same
frequencies, they are anagrams.

``` cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string a = "listen";
    string b = "silent";

    if (a.size() != b.size()) {
        cout << "Not anagrams\n";
        return 0;
    }

    int freq[256] = {0};

    for (unsigned char ch : a) {
        freq[ch]++;
    }

    for (unsigned char ch : b) {
        freq[ch]--;
    }

    for (int x : freq) {
        if (x != 0) {
            cout << "Not anagrams\n";
            return 0;
        }
    }

    cout << "Anagrams\n";
    return 0;
}
```

Expected time: `O(n + 256) = O(n)`. Auxiliary space: `O(256) = O(1)`.

This version is case-sensitive and works on byte characters.

### Problem 9: Count pairs with a given sum

**Idea:** For each value `x`, the required complement is `target - x`.
Add the number of previously seen complements to the answer, then record
`x`.

``` cpp
#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

int main() {
    vector<int> arr = {1, 5, 7, -1, 5};
    int target = 6;

    unordered_map<int, int> freq;
    long long pairs = 0;

    for (int x : arr) {
        pairs += freq[target - x];
        freq[x]++;
    }

    cout << pairs << '\n';
    return 0;
}
```

For this input, the number of index pairs is `3`.

Expected time: `O(n)`. Space: `O(k)`, where `k` is the number of
distinct values.

The algorithm counts pairs of indices `i < j`, including different
occurrences of the same value when appropriate.

### Problem 10: Intersection of two arrays (unique values)

**Idea:** Put the values from the first array into a set. Check values
from the second array against the set, and erase a matched value to
avoid printing it more than once.

``` cpp
#include <iostream>
#include <unordered_set>
#include <vector>
using namespace std;

int main() {
    vector<int> a = {1, 2, 2, 3, 4};
    vector<int> b = {2, 2, 4, 5};

    unordered_set<int> values(a.begin(), a.end());

    for (int x : b) {
        if (values.erase(x)) {
            cout << x << " ";
        }
    }

    return 0;
}
```

Expected time: `O(n + m)`. Space: `O(n)`.

This version returns unique common values, not the intersection with
duplicate counts.

------------------------------------------------------------------------

## 9. Time and space complexity summary

Let: - `n` = number of input elements. - `q` = number of queries. - `U`
= size of the fixed value range / frequency table. - `k` = number of
distinct keys. - `m` = number of hash-table buckets.

  --------------------------------------------------------------------------
  Problem /              Expected time    Worst-case time    Auxiliary space
  operation                                               
  ----------------- ------------------ ------------------ ------------------
  Direct frequency          `O(n + U)`         `O(n + U)`             `O(U)`
  build for `n`              including                    
  items                 initialization                    

  One                           `O(1)`             `O(1)`       `O(1)` extra
  frequency-array                                         
  query                                                   

  `q`                     `O(q)` after             `O(q)`       `O(1)` extra
  frequency-array        preprocessing                    
  queries                                                 

  Character               `O(n + 256)`       `O(n + 256)`           `O(256)`
  frequency of a                                          
  string                                                  

  Build                         `O(n)`            `O(n²)`             `O(k)`
  `unordered_map`                                         
  frequencies                                             

  One                           `O(1)`             `O(n)`       `O(1)` extra
  `unordered_map`                                         
  lookup                                                  

  Find duplicates               `O(n)`            `O(n²)`             `O(k)`
  with a map                                              

  Two Sum with a                `O(n)`            `O(n²)`             `O(n)`
  map                                                     

  First                   `O(n + 256)`       `O(n + 256)`           `O(256)`
  non-repeating                                           
  character (fixed                                        
  byte table)                                             

  Anagram check           `O(n + 256)`       `O(n + 256)`           `O(256)`
  (fixed byte                                             
  table)                                                  

  Count pairs with              `O(n)`            `O(n²)`             `O(k)`
  target sum                                              

  Unique                    `O(n + m)`            `O(nm)`             `O(n)`
  intersection                                            
  using a set                                             
  --------------------------------------------------------------------------

For `unordered_map` and `unordered_set`, expected complexity assumes a
reasonable hash distribution. The standard library does not promise
constant worst-case lookup.

### `map` vs `unordered_map`

  -----------------------------------------------------------------------
  Feature                 `map`                   `unordered_map`
  ----------------------- ----------------------- -----------------------
  Underlying structure    Ordered balanced tree   Hash table

  Key order               Sorted                  No guaranteed order

  Search                  `O(log n)`              Expected `O(1)`, worst
                                                  `O(n)`

  Insert                  `O(log n)`              Expected `O(1)`, worst
                                                  `O(n)`

  Erase by key            `O(log n)`              Expected `O(1)`, worst
                                                  `O(n)`

  Best use                Need sorted keys /      Need fast average key
                          ordered traversal       lookup
  -----------------------------------------------------------------------

------------------------------------------------------------------------

## 10. Advantages and disadvantages of hashing

### Advantages

1.  Fast expected lookup, insertion and deletion.
2.  Useful for frequency counting.
3.  Helps solve duplicate detection and pair-sum problems efficiently.
4.  Useful for caching and indexing.
5.  Can reduce repeated searching in arrays and strings.

### Disadvantages

1.  Collisions must be handled.
2.  Worst-case operations can be linear.
3.  Hash tables may use extra memory.
4.  Unordered containers do not maintain sorted key order.
5.  A poor hash function can cause clustering or long chains.
6.  Resizing and rehashing can be costly when they occur.

------------------------------------------------------------------------

## 11. Interview questions and answers

### Q1. What is hashing?

Hashing maps a key to an index using a hash function so data can be
accessed efficiently on average.

### Q2. What is a hash function?

A function that converts a key into a hash-table index.

### Q3. What is a collision?

A collision occurs when two different keys produce the same hash-table
index.

### Q4. What is the division method?

It calculates an index using `key % table_size`.

### Q5. What is the folding method?

It divides a key into parts, adds those parts, and uses the result to
form an index.

### Q6. What is the mid-square method?

It squares the key and selects middle digits or bits to form the hash
value.

### Q7. Are division, folding and mid-square collision-resolution techniques?

No. They are hash-function construction methods. Chaining and open
addressing are collision-resolution techniques.

### Q8. What is separate chaining?

A collision-resolution method in which each bucket stores a collection
of keys that map to that bucket.

### Q9. What is open addressing?

A method in which all keys are stored inside the hash-table array and
another slot is probed when the initial slot is occupied.

### Q10. What is linear probing?

A form of open addressing that checks consecutive slots until an
available slot is found.

### Q11. What is primary clustering?

In linear probing, groups of consecutive occupied slots can grow,
causing more keys to follow long probe sequences.

### Q12. What is quadratic probing?

A probing technique that uses quadratic offsets to search for another
available slot.

### Q13. What is secondary clustering?

Keys with the same initial hash value can follow the same probe sequence
in quadratic probing.

### Q14. What is double hashing?

A probing method that uses a second hash function to determine the
interval between probes.

### Q15. What is the load factor?

The ratio of the number of stored keys to the number of table slots:
`α = n / m`.

### Q16. What is rehashing?

Creating a new, usually larger, table and inserting all existing keys
again using the new table configuration.

### Q17. What is the average time complexity of `unordered_map` lookup?

Expected `O(1)` under a reasonable distribution of hash values. Worst
case is `O(n)`.

### Q18. What is the difference between `map` and `unordered_map`?

`map` stores keys in sorted order and generally uses a balanced tree
with `O(log n)` operations. `unordered_map` uses hashing, has expected
`O(1)` operations, and does not guarantee key order.

### Q19. When should a frequency array be used instead of a hash map?

When keys are non-negative integers in a small, known range. It offers
direct `O(1)` indexing but may waste memory for a large sparse range.

### Q20. Can a hash function guarantee no collisions?

Not in general when many possible keys map to a smaller finite table.
Different keys can map to the same index.

### Q21. Why should the same hash function be used for insertion and lookup?

So that a key is searched for in the same bucket or probe sequence where
it was inserted.

### Q22. Why is deletion in open addressing not always as simple as marking a slot empty?

An empty slot can cause a later search to stop too early, even though
the searched key lies further along the probe sequence. Tombstones or a
carefully designed deletion procedure are used.

### Q23. Does `unordered_map` store elements in sorted order?

No. Its iteration order is unspecified.

### Q24. What happens when an `unordered_map` grows?

It may rehash, allocating a new bucket arrangement and redistributing
existing elements. This can make an individual insertion expensive,
although insertion is expected constant time on average over a sequence
of operations.

### Q25. What is the space complexity of a frequency array?

`O(U)`, where `U` is the size of the indexed value range, regardless of
how many distinct values actually occur.

------------------------------------------------------------------------

## 12. Practice problems

Solve these in order:

### Beginner --- frequency and lookup

1.  Count the frequency of every element in an array.
2.  Answer `q` frequency queries for an array.
3.  Count lowercase letters in a string.
4.  Find the element with the highest frequency.
5.  Find the element with the lowest frequency.
6.  Find all elements that occur only once.
7.  Find all duplicate elements.

### Intermediate --- maps and sets

8.  Two Sum.
9.  Check whether two strings are anagrams.
10. Find the first non-repeating character.
11. Find the intersection of two arrays.
12. Find the union of two arrays.
13. Count pairs with a given sum.
14. Find the longest consecutive sequence.
15. Find the majority element.

### Advanced

16. Subarray Sum Equals K.
17. Longest subarray with sum K.
18. Count subarrays with XOR K.
19. Group anagrams.
20. Longest substring without repeating characters.

For every problem, record: - Brute-force approach. - Hashing-based
approach. - Time complexity. - Auxiliary space complexity. - Edge cases.

------------------------------------------------------------------------

## 13. Quick revision checklist

-   [ ] I understand keys, hash functions, indexes and collisions.
-   [ ] I can apply the division method by hand.
-   [ ] I understand folding and mid-square methods.
-   [ ] I can explain separate chaining.
-   [ ] I can explain open addressing.
-   [ ] I understand linear probing, quadratic probing and double
    hashing.
-   [ ] I know what load factor and rehashing mean.
-   [ ] I can use a frequency array for bounded integer values.
-   [ ] I can count character frequencies.
-   [ ] I can use `unordered_map` and `unordered_set`.
-   [ ] I understand `map` vs `unordered_map`.
-   [ ] I can analyse average and worst-case complexity.
-   [ ] I have practised Two Sum and duplicate detection.

------------------------------------------------------------------------

## 14. Important C++ reminders

``` cpp
#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;
```

Useful operations:

``` cpp
unordered_map<int, int> freq;

freq[x]++;                  // Insert x if absent, then increment
freq[x] = 5;                // Assign a value
freq.find(x);               // Find an iterator
freq.count(x);              // 1 if key exists, otherwise 0
freq.erase(x);              // Erase key x
freq.size();                // Number of keys
freq.empty();               // Check whether empty
```

For safe lookup without inserting a missing key:

``` cpp
auto it = freq.find(x);

if (it != freq.end()) {
    cout << it->second;
}
```

Remember: `freq[x]` inserts `x` with a default value if it is not
already present. This matters when you only intend to check whether a
key exists.
