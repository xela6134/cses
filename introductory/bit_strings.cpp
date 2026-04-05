#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;

    ll result = 1;
    for (ll i = 0; i < n; ++i) {
        result <<= 1;
        result %= 1000000007;
    }

    cout << result << '\n';
}
