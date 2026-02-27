#include <bits/stdc++.h>
using namespace std;

bool isValidBoard(int col, int row, int colSize, int rowSize) {
    return (col >= 0 && col < colSize && row >= 0 && row < rowSize);
}

char connectFour(const vector<vector<char>>& board) {
    const int K = 4;
    
    vector<pair<int, int>> directions = {
        {0, 1},
        {1, 0},
        {1, 1},
        {1, -1}
    };

    int m = board.size();
    int n = board[0].size();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            char player = board[i][j];
            if (player == '.') continue;

            for (const auto& d : directions) {
                int count = 1;

                for (int k = 1; k < K; ++k) {
                    int newCol = i + d.first * k;
                    int newRow = j + d.second * k;

                    if (!isValidBoard(newCol, newRow, m, n)) break;
                    if (board[newCol][newRow] != player) break;

                    ++count;
                }

                if (count == 4) return player;
            }
        }
    }

    return 'X';
}

int main() {

}