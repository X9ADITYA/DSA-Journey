# Recursion in C++

A beginner-friendly learning module covering the recursion concepts and
problems studied so far.

## Topics covered

-   What recursion is
-   Base condition and recursive call
-   How recursive calls are stored in the call stack
-   The two phases of recursion: calling and returning
-   Functional recursion
-   Parameterised recursion
-   Sum of first `n` natural numbers
-   Factorial of a number
-   Reversing an array using recursion

## What is recursion?

Recursion is a programming technique in which a function calls itself to
solve a smaller version of the same problem.

A recursive function generally contains two important parts:

1.  **Base condition:** tells the function when to stop calling itself.
2.  **Recursive call:** calls the same function with a smaller or
    simpler input.

Without a reachable base condition, recursion may continue until the
program runs out of call-stack memory.

## How recursion works

A recursive function works in two broad phases:

1.  **Calling phase:** function calls keep getting added to the call
    stack until the base condition is reached.
2.  **Returning phase (stack unwinding):** calls return in reverse
    order, completing any pending calculations.

The call stack follows **LIFO (Last In, First Out)**.

## Types of recursion studied

### 1. Functional recursion

In functional recursion, the recursive call returns a value. The current
call uses that returned value to complete its calculation.

Example:

``` cpp
int sum(int n) {
    if (n == 0) {
        return 0;
    }

    return n + sum(n - 1);
}
```

Here, `sum(n - 1)` returns a value, and the current call adds `n` to it.

### 2. Parameterised recursion

In parameterised recursion, an additional parameter carries the result
accumulated so far. The recursive function updates that parameter as it
moves towards the base condition.

Example:

``` cpp
void sum(int n, int total) {
    if (n == 0) {
        cout << total;
        return;
    }

    sum(n - 1, total + n);
}
```

Call it using:

``` cpp
sum(3, 0);
```

The accumulated values are:

``` text
sum(3, 0)
sum(2, 3)
sum(1, 5)
sum(0, 6)
```

At the base condition, the answer is `6`.

> The key distinction: functional recursion builds the answer from
> returned values; parameterised recursion carries an accumulator
> through function parameters.

## Problems completed so far

  -----------------------------------------------------------------------
  Problem                 Main idea               Base condition
  ----------------------- ----------------------- -----------------------
  Sum of first `n`        Add `n` to the sum of   `n == 0`
  natural numbers         smaller numbers         

  Factorial               Multiply `n` by the     `n == 0`
                          factorial of `n - 1`    

  Reverse an array        Swap the elements at    `start >= end`
                          both ends, then move    
                          inward                  
  -----------------------------------------------------------------------

### 1. Sum of first `n` natural numbers

``` cpp
int sum(int n) {
    if (n == 0) {
        return 0;
    }

    return n + sum(n - 1);
}
```

For `sum(3)`:

``` text
sum(3) = 3 + sum(2)
       = 3 + 2 + sum(1)
       = 3 + 2 + 1 + sum(0)
       = 3 + 2 + 1 + 0
       = 6
```

### 2. Factorial of a number

``` cpp
int factorial(int n) {
    if (n == 0) {
        return 1;
    }

    return n * factorial(n - 1);
}
```

For `factorial(4)`:

``` text
factorial(4) = 4 * factorial(3)
             = 4 * 3 * factorial(2)
             = 4 * 3 * 2 * factorial(1)
             = 4 * 3 * 2 * 1 * factorial(0)
             = 4 * 3 * 2 * 1 * 1
             = 24
```

The base case returns `1` because multiplying by `1` does not change the
product. Mathematically, `0! = 1`.

### 3. Reverse an array using recursion

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

Output:

``` text
Reversed array: 5 4 3 2 1
```

The function swaps the first and last elements, then recursively
processes the smaller section between them. When `start >= end`, no more
swaps are needed.

## Important reminders

-   Every recursive function must make progress towards its base
    condition.
-   Each recursive call has its own parameters and local execution
    state.
-   A call waits when it needs the result of a deeper recursive call.
-   Calls return in reverse order because the call stack is LIFO.
-   Recursion uses call-stack memory.
-   Check edge cases such as `n = 0`, `n = 1`, and an empty or
    single-element array.
-   For factorial and sum examples, assume non-negative integer input.
    The `int` type can overflow for sufficiently large inputs.

## Complexity overview

  Problem                      Time complexity   Auxiliary space complexity
  -------------------------- ----------------- ----------------------------
  Sum of first `n` numbers              `O(n)`                       `O(n)`
  Factorial                             `O(n)`                       `O(n)`
  Reverse array                         `O(n)`                       `O(n)`

The auxiliary space for these recursive implementations comes from the
call stack. The array-reversal function performs about `n / 2` swaps,
which is still `O(n)` time, and uses `O(n)` stack space.

## Suggested next topics

-   Print numbers from `1` to `n` and from `n` to `1`
-   Fibonacci sequence
-   Check whether a string is a palindrome
-   Reverse a string using recursion
-   Find the maximum element in an array
-   Binary search using recursion
-   Recursion on subsequences and backtracking
