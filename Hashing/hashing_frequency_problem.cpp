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
