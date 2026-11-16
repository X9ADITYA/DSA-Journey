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


