# Recursion --- Notes, Code Explanations & Interview Preparation

These notes cover the concepts and three problems completed so far: sum
of natural numbers, factorial, and reversing an array.

------------------------------------------------------------------------

## 1. Recursion fundamentals

### Definition

Recursion is a technique in which a function calls itself to solve a
smaller instance of the same problem.

### Two essential parts

**Base condition** - The stopping condition. - Prevents further
recursive calls. - Must be reachable.

**Recursive case** - The part where the function calls itself. - The
input should move towards the base condition.

Example:

``` cpp
int sum(int n) {
    if (n == 0) {       // Base condition
        return 0;
    }

    return n + sum(n - 1);  // Recursive case
}
```

### The two phases

1.  **Calling phase:** calls are made and placed on the call stack.
2.  **Returning phase / stack unwinding:** once the base case returns,
    pending calls resume in reverse order.

The call stack follows **LIFO --- Last In, First Out**.

For `sum(3)`:

``` text
Calling:
sum(3)
  -> sum(2)
      -> sum(1)
          -> sum(0)

Returning:
sum(0) returns 0
sum(1) returns 1
sum(2) returns 3
sum(3) returns 6
```

A call that has not received the result of its recursive call remains
suspended, with its local state stored in its stack frame.

------------------------------------------------------------------------

## 2. Functional recursion vs parameterised recursion

These are two common ways to structure a recursive solution.

### A. Functional recursion

The recursive function returns a value. The current call combines that
returned value with its own work.

``` cpp
int sumFunctional(int n) {
    if (n == 0) {
        return 0;
    }

    return n + sumFunctional(n - 1);
}
```

Call:

``` cpp
cout << sumFunctional(3);
```

Evaluation:

``` text
sumFunctional(3)
= 3 + sumFunctional(2)
= 3 + 2 + sumFunctional(1)
= 3 + 2 + 1 + sumFunctional(0)
= 3 + 2 + 1 + 0
= 6
```

**Remember:** the addition is completed while the recursive calls
return.

### B. Parameterised recursion

An extra parameter carries the partial answer (an accumulator). Each
call updates the accumulator before making the next call.

``` cpp
#include <iostream>
using namespace std;

void sumParameterized(int n, int total) {
    if (n == 0) {
        cout << total;
        return;
    }

    sumParameterized(n - 1, total + n);
}

int main() {
    sumParameterized(3, 0);
    return 0;
}
```

Parameter progression:

  Call     `n`   `total`
  ------ ----- ---------
  1          3         0
  2          2         3
  3          1         5
  4          0         6

At `n == 0`, the accumulated result is `6`.

### Main difference

  -----------------------------------------------------------------------
  Functional recursion                Parameterised recursion
  ----------------------------------- -----------------------------------
  Recursive call returns a value      Accumulator parameter carries the
                                      partial result

  Current call combines the returned  Each call updates the accumulator
  result                              

  Example: `n + sum(n - 1)`           Example: `sum(n - 1, total + n)`

  Often easier to express             Often useful when carrying state
  mathematical relationships          through recursive calls
  -----------------------------------------------------------------------

Both versions take `O(n)` time and `O(n)` auxiliary call-stack space in
these examples. Parameterised recursion does not automatically mean
constant space: ordinary C++ recursive calls still use stack frames.

------------------------------------------------------------------------

## 3. Problem 1 --- Sum of first n natural numbers

### Question

Given a non-negative integer `n`, calculate:

``` text
1 + 2 + 3 + ... + n
```

For `n = 3`, the answer is `6`.

### Code --- functional recursion

``` cpp
#include <iostream>
using namespace std;

int sum(int n) {
    if (n == 0) {
        return 0;
    }

    return n + sum(n - 1);
}

int main() {
    int n = 3;
    cout << sum(n);
    return 0;
}
```

### Explanation

1.  `sum(3)` checks whether `3 == 0`. It is false.
2.  It returns `3 + sum(2)`, so it must first obtain `sum(2)`.
3.  `sum(2)` calls `sum(1)`.
4.  `sum(1)` calls `sum(0)`.
5.  `sum(0)` reaches the base condition and returns `0`.
6.  The pending calls complete: `sum(1) = 1`, `sum(2) = 3`, and
    `sum(3) = 6`.

### Trace

  Call       Pending expression     Returned value
  ---------- -------------------- ----------------
  `sum(3)`   `3 + sum(2)`                        6
  `sum(2)`   `2 + sum(1)`                        3
  `sum(1)`   `1 + sum(0)`                        1
  `sum(0)`   Base case                           0

### Complexity

-   **Time:** `O(n)` --- one call for each value from `n` down to `0`.
-   **Auxiliary space:** `O(n)` --- up to `n + 1` active recursive calls
    on the call stack.

### Important observation

The expression `n + sum(n - 1)` cannot finish its addition until
`sum(n - 1)` returns.

------------------------------------------------------------------------

## 4. Problem 2 --- Factorial of a number

### Question

Calculate the factorial of a non-negative integer `n`.

``` text
n! = n × (n - 1) × (n - 2) × ... × 1
```

Special case:

``` text
0! = 1
```

For `n = 4`:

``` text
4! = 4 × 3 × 2 × 1 = 24
```

### Code

``` cpp
#include <iostream>
using namespace std;

int factorial(int n) {
    if (n == 0) {
        return 1;
    }

    return n * factorial(n - 1);
}

int main() {
    int n = 4;
    cout << factorial(n);
    return 0;
}
```

### Explanation

1.  `factorial(4)` calls `factorial(3)`.
2.  `factorial(3)` calls `factorial(2)`.
3.  `factorial(2)` calls `factorial(1)`.
4.  `factorial(1)` calls `factorial(0)`.
5.  `factorial(0)` returns `1`.
6.  The pending multiplications complete as the calls return.

### Trace

``` text
factorial(4) = 4 × factorial(3)
             = 4 × 3 × factorial(2)
             = 4 × 3 × 2 × factorial(1)
             = 4 × 3 × 2 × 1 × factorial(0)
             = 4 × 3 × 2 × 1 × 1
             = 24
```

### Why does the base condition return 1?

Because `1` is the multiplicative identity:

``` text
number × 1 = number
```

Returning `0` would make the entire product zero. Also, by mathematical
definition, `0! = 1`.

### Complexity

-   **Time:** `O(n)` --- there are `n + 1` function calls.
-   **Auxiliary space:** `O(n)` --- recursive call-stack depth is
    proportional to `n`.

### Important note about data types

The `int` type overflows for relatively small factorial inputs. For
larger values, use a suitable big-integer approach; `long long` only
extends the range and does not support arbitrarily large factorials. The
example assumes `n >= 0`.

------------------------------------------------------------------------

## 5. Problem 3 --- Reverse an array using recursion

### Question

Reverse the order of elements in an array.

Input:

``` text
1 2 3 4 5
```

Output:

``` text
5 4 3 2 1
```

### Approach

Use two indexes:

-   `start` points to the first element of the current section.
-   `end` points to the last element of the current section.

Steps:

1.  If `start >= end`, stop.
2.  Swap `arr[start]` and `arr[end]`.
3.  Move `start` one position forward.
4.  Move `end` one position backward.
5.  Recursively process the remaining middle section.

### Complete code

``` cpp
#include <iostream>
using namespace std;

void reverse(int arr[], int start, int end) {
    if (start >= end) {
        return;
    }

    swap(arr[start], arr[end]);

    reverse(arr, start + 1, end - 1);
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int n = 5;

    reverse(arr, 0, n - 1);

    cout << "Reversed array: ";

    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
```

### Step-by-step trace

Initial array:

``` text
Index:  0  1  2  3  4
Array:  1  2  3  4  5
```

  Call                     Start   End Operation
  ---------------------- ------- ----- ----------------------
  `reverse(arr, 0, 4)`         0     4 Swap 1 and 5
  `reverse(arr, 1, 3)`         1     3 Swap 2 and 4
  `reverse(arr, 2, 2)`         2     2 Base condition; stop

Array after the swaps:

``` text
5 4 3 2 1
```

### Why is the base condition `start >= end`?

When `start == end`, both indexes point to the same middle element. It
does not need to be swapped.

When `start > end`, the indexes have crossed, so every required pair has
already been swapped.

### Complexity

-   **Time:** `O(n)` --- approximately `n / 2` swaps are performed.
    Big-O ignores constant factors.
-   **Auxiliary space:** `O(n)` --- the recursive call stack has depth
    proportional to `n / 2`, which is also `O(n)`.
-   **Extra array space:** `O(1)` --- the original array is modified in
    place; no second array is created.

### Edge cases

  -----------------------------------------------------------------------
  Array                               Expected result
  ----------------------------------- -----------------------------------
  `{1, 2, 3}`                         `{3, 2, 1}`

  `{1, 2, 3, 4}`                      `{4, 3, 2, 1}`

  `{7}`                               `{7}`

  `{}`                                `{}` --- no recursive call is
                                      needed if handled with an
                                      appropriate length check
  -----------------------------------------------------------------------

------------------------------------------------------------------------

## 6. Comparison of all problems

  ----------------------------------------------------------------------------------------------------
  Problem      Recursive call                       Base condition               Time  Auxiliary space
  ------------ ------------------------------------ ---------------- ---------------- ----------------
  Sum          `n + sum(n - 1)`                     `n == 0`                   `O(n)`           `O(n)`

  Factorial    `n * factorial(n - 1)`               `n == 0`                   `O(n)`           `O(n)`

  Reverse      `reverse(arr, start + 1, end - 1)`   `start >= end`             `O(n)`           `O(n)`
  array                                                                               
  ----------------------------------------------------------------------------------------------------

------------------------------------------------------------------------

## 7. Interview questions and answers

### Q1. What is recursion?

Recursion is a technique in which a function calls itself to solve
smaller instances of a problem.

### Q2. What are the two essential parts of recursion?

A base condition, which stops recursion, and a recursive case, which
makes progress towards that condition.

### Q3. What happens if there is no base condition?

The function may keep calling itself until the call stack runs out of
memory, commonly resulting in a stack overflow.

### Q4. What is a call stack?

It is the stack memory structure used to manage active function calls.
Each call has its own stack frame containing information such as
parameters, local variables, and where execution should resume.

### Q5. Which principle does the call stack follow?

LIFO --- Last In, First Out.

### Q6. What is stack unwinding?

It is the process of returning from recursive calls in reverse order
after the base condition has been reached.

### Q7. What is the difference between functional and parameterised recursion?

Functional recursion uses the value returned by a recursive call to
build the answer. Parameterised recursion carries a partial result in an
argument such as an accumulator.

### Q8. Why does factorial use `return 1` as its base case?

Because `1` is the multiplicative identity, and `0!` is defined as `1`.

### Q9. Why does sum use `return 0` as its base case?

Because `0` is the additive identity. Adding zero does not change the
result.

### Q10. Can an array be reversed using recursion?

Yes. Use two indexes, swap the elements at those indexes, and move both
indexes towards the centre until `start >= end`.

### Q11. Is recursion always better than iteration?

No. Recursion can make some problems easier to express, but it uses
call-stack memory and may add function-call overhead. An iterative
solution may be more memory-efficient.

### Q12. What is the space complexity of these recursive examples?

`O(n)` auxiliary space because the number of simultaneously active
recursive calls grows linearly with `n`. For array reversal, the maximum
depth is about `n / 2`, which is still `O(n)`.

### Q13. What is tail recursion?

A recursive function is tail-recursive when the recursive call is the
final operation performed by the function. The parameterised sum example
is tail-recursive in structure.

### Q14. Does C++ guarantee tail-call optimisation?

No. Tail-call optimisation is not guaranteed by the C++ language
standard. Do not assume a tail-recursive function will use constant
stack space.

### Q15. What is the difference between recursion and iteration?

Recursion repeats work through function calls; iteration repeats work
through loops such as `for` and `while`. Both can solve many of the same
problems.

------------------------------------------------------------------------

## 8. Practice questions

Try these in order:

### Beginner

1.  Print numbers from `1` to `n` using recursion.
2.  Print numbers from `n` to `1` using recursion.
3.  Find the sum of numbers from `1` to `n`.
4.  Find the factorial of a number.
5.  Calculate `a` raised to power `b` using recursion.

### Arrays and strings

6.  Reverse an array using recursion.
7.  Find the sum of all elements in an array.
8.  Find the maximum element in an array.
9.  Check whether a string is a palindrome.
10. Reverse a string using recursion.

### Intermediate

11. Find the nth Fibonacci number.
12. Implement binary search using recursion.
13. Check whether an array is sorted.
14. Count the occurrences of a given element in an array.
15. Find the greatest common divisor (GCD) using recursion.

------------------------------------------------------------------------

## 9. Complexity quick revision

  -----------------------------------------------------------------------
  Complexity              Meaning                 Example
  ----------------------- ----------------------- -----------------------
  `O(1)`                  Constant work           Accessing `arr[i]`

  `O(log n)`              Input reduces by a      Recursive binary search
                          constant factor         

  `O(n)`                  Work grows linearly     Sum and factorial
                          with input              recursion

  `O(n log n)`            Linear work across      Merge sort
                          logarithmic levels      

  `O(n²)`                 Quadratic work          Two nested loops over
                                                  `n` elements
  -----------------------------------------------------------------------

**Remember:** Time complexity measures how the amount of work grows.
Auxiliary space complexity measures the extra memory used by the
algorithm, including recursive call-stack frames, but excluding the
input itself unless stated otherwise.

------------------------------------------------------------------------

## 10. Quick revision checklist

-   [ ] I can identify the base condition.
-   [ ] I can identify the recursive call.
-   [ ] I understand the calling and returning phases.
-   [ ] I understand how the call stack works.
-   [ ] I can explain functional recursion.
-   [ ] I can explain parameterised recursion.
-   [ ] I can write the recursive sum program.
-   [ ] I can write the recursive factorial program.
-   [ ] I can reverse an array using two indexes and recursion.
-   [ ] I can calculate time and auxiliary space complexity.
