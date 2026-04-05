#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;

    ll sum = 0;
    ll x;
    for (ll i = 1; i < n; ++i) {
        cin >> x;
        sum += x;
    }

    ll ans = n * (n + 1) / 2 - sum;
    cout << ans << '\n';

    return 0;
}
