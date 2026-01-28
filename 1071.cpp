#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;

    ll x, y, z, ans;
    for (int i = 0; i < n; ++i) {
        cin >> x >> y;

        z = max(x, y);
        if ((z & 1) == 0) {
            if (x < y) {
                ans = (y - 1) * (y - 1) + x;
            } else {
                ans = x * x - (y - 1);
            }
        } else {
            if (x < y) {
                ans = y * y - (x - 1);
            } else {
                ans = (x - 1) * (x - 1) + y;
            }
        }

        cout << ans << '\n';
    }

    return 0;
}
