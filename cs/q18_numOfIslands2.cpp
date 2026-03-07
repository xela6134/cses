#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Return how many islands there were
    vector<int> numIslands2(int m, int n, vector<vector<int>>& positions) {
        // parent -1: water
        //   rank  0: default
        for (int i = 0; i < m * n; ++i) {
            parent.push_back(-1);
            rank.push_back(0);
        }

        // Result vector
        vector<int> result;
        vector<pair<int, int>> dirs = {{0,1},{1,0},{0,-1},{-1,0}};

        // Go through each position
        for (auto& pos : positions) {
            int r = pos[0];
            int c = pos[1];
            int idx = r * n + c;

            // duplicate, skip
            if (parent[idx] != -1) {
                result.push_back(islands);
                continue;
            }

            // Add island by default, assume root node
            parent[idx] = idx;
            ++islands;

            // For each direction
            for (auto& d : dirs) {
                int nr = r + d.first;
                int nc = c + d.second;
                int nidx = nr * n + c;

                if (nr < 0 || nr >= m || nc < 0 || nc >= n) continue;

                // Dont traverse if its water anyways
                if (parent[nidx] == -1) continue;

                unite(idx, nidx);
            }

            result.push_back(islands);
        }

        return result;
    }

private:
    vector<int> parent;
    vector<int> rank;

    int islands = 0;

    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }

    void unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);

        if (rank[rx] < rank[ry]) swap(rx, ry);
        parent[ry] = parent[rx];
        if (rx == ry) ++rank[rx];

        --islands;
    }
};