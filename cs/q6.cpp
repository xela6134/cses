#include <bits/stdc++.h>
using namespace std;

int minimumTalentWindow(vector<int> talents) {
    unordered_set<int> distincts;

    for (int t : talents) {
        distincts.insert(t);
    }

    int target = distincts.size();
    int n = talents.size();

    unordered_map<int, int> counts;
    int minWindow = INT_MAX;

    int left = 0;
    for (int right = 0; right < n; ++right) {
        ++counts[talents[right]];

        while (counts.size() == target) {
        
            minWindow = min(minWindow, right - left + 1);
        
            int leftTalent = talents[left];
            ++left;
            int leftCount = --counts[leftTalent];
            if (leftCount == 0) counts.erase(leftTalent);
        }
    }

    return (minWindow == INT_MAX) ? -1 : minWindow;
}

int main() {
    vector<int> talents = {1,1,3,2,2,1,1,4,1,2,3,1,2,3};
    cout << minimumTalentWindow(talents) << '\n';
}
