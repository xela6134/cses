#include <bits/stdc++.h>
using namespace std;

bool isOpposite(char c1, char c2) {
    return ((c1 == '^' && c2 == 'v') 
         || (c1 == 'v' && c2 == '^')
         || (c1 == '<' && c2 == '>')
         || (c1 == '>' && c2 == '<')
    );
}

bool isRectangle(string moves) {
    if (moves.empty()) return false;

    unordered_map<int, int> counts;
    char curr = moves[0];
    counts[curr] = 1;

    for (int i = 1; i < moves.length(); ++i) {
        if (moves[i] == curr) {
            curr = moves[i];
            ++counts[curr];
        } else {
            if (isOpposite(curr, moves[i])) return false;

            curr = moves[i];
            if (counts.count(curr)) return false;

            ++counts[curr];
        }
    }

    return (counts['^'] == counts['v']) 
        && (counts['<'] == counts['>'])
        && (counts['v'] > 0 && counts['^'] > 0 && counts['<'] > 0 && counts['>'] > 0);
}
