#include <bits/stdc++.h>
using namespace std;

void dfs(int row, int col, vector<vector<int>>& grid, vector<vector<bool>>& visited) {
    int m = grid.size();
    int n = grid[0].size();

    if (row < 0 || row >= m || col < 0 || col >= n) return;

    visited[row][col] = true;

    dfs(row + 1, col, grid, visited);
    dfs(row - 1, col, grid, visited);
    dfs(row, col + 1, grid, visited);
    dfs(row, col - 1, grid, visited);
}

int distinctIslands(vector<vector<int>>& grid) {

}
