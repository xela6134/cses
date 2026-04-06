#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, x, child;
    cin >> n >> x;

    vector<ll> children;
    for (ll i = 0; i < n; ++i) {
        cin >> child;
        children.push_back(child);
    }

    sort(children.begin(), children.end());

    ll lo = 0, hi = n - 1, ans = 0;
    while (lo <= hi) {
        if (lo == hi) {
            ++ans;
            break;
        }
        if (children[lo] + children[hi] <= x) {
            ++lo;
        }
        --hi;
        ++ans;
    }

    cout << ans << "\n";

    return 0;
}
