#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    string s;
    cin >> s;
    int n = s.size();
    
    int l = 0;
    int ans = 1;

    for (int r = 1; r < n; ++r) {
        if (s[r - 1] != s[r]) {
            l = r;
        }

        ans = max(ans, (r - l + 1));
    }

    cout << ans << '\n';
    
    return 0;
}
