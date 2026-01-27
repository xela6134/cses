#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;

    if (n == 1) {
        cout << "1\n";
        return 0;
    } else if (n < 4) {
        cout << "NO SOLUTION\n";
        return 0;
    } else if (n == 4) {
        cout << "3 1 4 2 \n";
        return 0;
    }

    // 1 _ 2 _ 3 _
    int k = (n + 1) / 2;

    for (int i = 1; i < k; ++i) {
        cout << i << ' ';
        cout << i + k << ' ';
    }

    cout << k << ' ';
    if ((n & 1) == 0) cout << k * 2 << '\n';
    else cout << '\n';

    return 0;
}
