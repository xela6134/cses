#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    int n;
    cin >> n;

    // 3 2 5 1 7
    vector<int> nums;
    nums.reserve(n);
    int x;

    for (int i = 0; i < n; ++i) {
        cin >> x;
        nums.push_back(x);
    }

    ll sum = 0;
    int diff;

    for (int i = 1; i < n; ++i) {
        diff = nums[i - 1] - nums[i];
        if (diff > 0) {
            sum += diff;
            nums[i] = nums[i - 1];
        }
    }

    cout << sum << '\n';

    return 0;
}
