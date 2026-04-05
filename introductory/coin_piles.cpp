#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll a, b, n, k;
    cin >> n;

    for (ll i = 0; i < n; ++i) {
        cin >> a >> b;
        k = a + b;

        // 1. k is divisible by 3
        // 2. k/3 < a, b < 2k/3

        // cout << a << ", " << b << ": ";

        if (k % 3 == 0 && 
            k/3 <= a && a <= 2*k/3 && 
            k/3 <= b && b <= 2*k/3) cout << "YES\n";
        else cout << "NO\n";
    }

    return 0;
}
