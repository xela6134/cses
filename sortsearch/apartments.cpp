#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    ll n, m, k;
    cin >> n >> m >> k;

    vector<ll> desired, sizes;
    ll d, s;

    for (ll i = 0; i < n; ++i) {
        cin >> d;
        desired.push_back(d);
    }

    for (ll i = 0; i < m; ++i) {
        cin >> s;
        sizes.push_back(s);
    }

    sort(desired.begin(), desired.end());
    sort(sizes.begin(), sizes.end());

    ll i = 0, j = 0;
    ll result = 0;

    // cout << desired.size() << ", " << sizes.size() << '\n';

    while (i < n && j < m) {
        // 1. desired > sizes + k
        // 2. desired + k < sizes

        if (desired[i] > sizes[j] + k) {
            ++j;
        } else if (desired[i] + k < sizes[j]) {
            ++i;
        } else {
            ++i; ++j;
            ++result;
        }
    }

    cout << result << '\n';
    return 0;
}
