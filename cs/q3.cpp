#include <bits/stdc++.h>
using namespace std;

int cellInfection(vector<vector<int>>& cells) {

    // 1. Add all the 2s to queue
    // 2. Conduct BFS, {{x, y}, minute}
    // 3. Check for any 1s after traversal is finished

    queue<pair<pair<int, int>, int>> q;

    int m = cells.size();
    int n = cells[0].size();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (cells[i][j] == 2) q.push({{i, j}, 0});
        }
    }

    vector<pair<int, int>> directions = {
        {0, 1}, {0, -1}, {1, 0}, {-1, 0}
    };

    int max_time = 0;
    while (!q.empty()) {
        auto [coords, time] = q.front();
        auto [i, j] = coords;
        q.pop();

        max_time = max(max_time, time);

        for (const auto& d : directions) {
            int newI = i + d.first;
            int newJ = j + d.second;

            // Coords bound
            if (newI < 0 || newI >= m || newJ < 0 || newJ >= n) continue;

            // Change cells
            if (cells[newI][newJ] == 1) {
                cells[newI][newJ] = 2;
                q.push({{newI, newJ}, time + 1});
            }
        }
    }

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (cells[i][j] == 1) return -1;
        }
    }

    return max_time;
}

int main() {
    
    return 0;
}
