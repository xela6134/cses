#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    string s;
    cin >> s;
    sort(s.begin(), s.end());

    vector<string> perms;
    perms.push_back(s);
    while (next_permutation(s.begin(), s.end())) {
        perms.push_back(s);
    }

    cout << perms.size() << "\n";
    for (const auto& p : perms) {
        cout << p << "\n";
    }
}
