#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;

    ll total = n * (n + 1) / 2;
    if (total % 2 != 0) {
        cout << "NO\n";
        return 0;
    }

    ll target = total / 2;
    vector<ll> s1, s2;

    for (ll i = n; i >= 1; i--) {
        if (i <= target) {
            s1.push_back(i);
            target -= i;
        } else {
            s2.push_back(i);
        }
    }

    cout << "YES\n";
    cout << s1.size() << "\n";
    for (auto x : s1) cout << x << " ";
    cout << "\n";
    cout << s2.size() << "\n";
    for (auto x : s2) cout << x << " ";
    cout << "\n";
}
