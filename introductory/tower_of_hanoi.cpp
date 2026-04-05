#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

void solve(int n, int src, int dest, int mid);
int num(int n);

int main() {
    int n;
    cin >> n;
    
    cout << num(n) << '\n';
    
    solve(n, 1, 3, 2);
    
    return 0;
}

int num(int n) {
    if (n == 1) return 1;
    return 2 * num(n - 1) + 1;
}

void solve(int n, int src, int dest, int mid) {
    if (n == 1) {
        cout << src << ' ' << dest << '\n';
        return;
    }

    solve(n - 1, src, mid, dest);
    cout << src << ' ' << dest << '\n';
    solve(n - 1, mid, dest, src);
}
