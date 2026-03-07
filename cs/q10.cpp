#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    void solve(vector<vector<char>>& board) {
        if (board.empty() || board[0].empty()) return;
        
        int m = board.size();
        int n = board[0].size();

        vector<pair<int, int>> directions = {
            {0, 1}, {1, 0}, {0, -1}, {-1, 0}
        };

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] != 'O') continue;

                vector<pair<int, int>> coords;
                bool atBorder = false;
                queue<pair<int, int>> q;

                q.push({i, j});
                board[i][j] = 'V';  // Mark visited
                coords.push_back({i, j});

                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();

                    if (x == 0 || y == 0 || x == m - 1 || y == n - 1) {
                        atBorder = true;
                    }

                    // Explore neighbors
                    for (const auto& d : directions) {
                        int nx = x + d.first;
                        int ny = y + d.second;

                        if (nx >= 0 && nx < m && ny >= 0 && ny < n && board[nx][ny] == 'O') {
                            board[nx][ny] = 'V';
                            q.push({nx, ny});
                            coords.push_back({nx, ny});
                        }
                    }
                }

                // If connected component never hit the border, it's surrounded
                if (!atBorder) {
                    for (auto& p : coords) {
                        board[p.first][p.second] = 'X';
                    }
                }
            }
        }

        // Cleanup
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (board[i][j] == 'V') {
                    board[i][j] = 'O';
                }
            }
        }
    }
};
