#include <bits/stdc++.h>
using namespace std;

struct Entry {
    int timestamp;
    int delta;
    int k_index;
    int n_index;
};

struct EntryComparator {
    bool operator()(const Entry& e1, const Entry& e2) {
        return e1.timestamp > e2.timestamp;
    }
};

// {timestamp, delta}
vector<pair<int, int>> mergeFeeds(vector<vector<pair<int, int>>> feeds) {
    int K = feeds.size();

    priority_queue<Entry, vector<Entry>, EntryComparator> pq;

    for (int i = 0; i < K; ++i) {
        const auto& curr = feeds[i][0];
        pq.push({curr.first, curr.second, i, 0});
    }

    int sum = 0;
    vector<pair<int, int>> result;
    while (!pq.empty()) {
        int currTime = pq.top().timestamp;

        while (!pq.empty() && pq.top().timestamp == currTime) {
            auto [timestamp_, delta_, k_index_, n_index_] = pq.top();
            pq.pop();

            sum += delta_;
            ++n_index_;

            if (n_index_ < feeds[k_index_].size()) {
                auto& next = feeds[k_index_][n_index_];
                pq.push({next.first, next.second, k_index_, n_index_});
            }
        }

        result.push_back({currTime, sum});
    }

    return result;
}
