#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ll n;
    cin >> n;

    while (n != 1) {
        cout << n << ' ';

        if ((n & 1) == 0) {
            n /= 2;
        } else {
            n *= 3;
            ++n;
        }
    }

    cout << n << '\n';

    return 0;
}
