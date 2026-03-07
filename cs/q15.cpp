#include <bits/stdc++.h>
using namespace std;

// store 4-bit exponent per cell
long long encode(vector<vector<int>>& board) {
    long long coded = 0;

    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int n = board[i][j];

            long long exponent = 0;
            if (n != 0) {    
                while (n > 1) {
                    ++exponent;
                    n = n >> 1;
                }
            }

            coded = coded << 4;
            coded = coded | exponent;
        }
    }

    return coded;
}

// extract 4-bit exponent per cell
void decode(long long coded, vector<vector<int>>& board) {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            int k = 15 - (i * 4 + j);

            long long block = coded >> (k * 4);

            int exponent = block & 15;
            if (exponent == 0) {
                board[i][j] = 0;
            } else {
                board[i][j] = 1 << exponent;
            }
        }
    }
}

// decode → apply move → merge tiles → encode
long long simulate(long long state, int direction) {
    
}
