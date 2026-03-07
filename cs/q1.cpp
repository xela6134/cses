#include <bits/stdc++.h>
using namespace std;

struct Trade {
    int tradeId;
    int time;
    bool isBuy;
};

vector<pair<int, int>> stockExposure(vector<Trade>& trades) {
    vector<pair<int, int>> intervals;
    unordered_map<int, int> temps;

    for (const auto& t : trades) {
        if (temps.count(t.tradeId)) {
            int startTime = min(t.time, temps[t.tradeId]);
            int endTime = max(t.time, temps[t.tradeId]);
            intervals.push_back(make_pair(startTime, endTime));
        } else {
            temps[t.tradeId] = t.time;
        }
    }

    if (intervals.size() == 0) return intervals;

    sort(intervals.begin(), intervals.end());

    // Return all the pairs
    vector<pair<int, int>> merged;

    merged.push_back({intervals[0].first, intervals[0].second});

    for (int i = 1; i < intervals.size(); ++i) {
        int& currEnd = merged.back().second;
        
        // Separate intervals
        if (currEnd < intervals[i].first) {
            merged.push_back(intervals[i]);
        }
        
        // Merge
        else {
            currEnd = max(currEnd, intervals[i].second);
        }
    }

    return merged;
}

int main() {
    
    return 0;
}
