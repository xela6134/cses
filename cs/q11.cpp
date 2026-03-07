#include <bits/stdc++.h>
using namespace std;

bool isYounger(vector<vector<char>> locations, char X, char Y) {
    unordered_map<char, vector<char>> graph;

    for (auto& loc : locations) {
        for (int i = 1; i < loc.size(); ++i) {
            graph[loc[i-1]].push_back(loc[i]);
        }
    }

    unordered_set<char> visited;
    queue<char> q;
    visited.insert(X);
    q.push(X);

    while (!q.empty()) {
        char curr = q.front();
        q.pop();

        for (char adj : graph[curr]) {
            if (!visited.count(adj)) {
                
                if (adj == Y) return true;
                
                visited.insert(X);
                q.push(adj);
            }
        }
    }

    return false;
}

int main() {
    cout << boolalpha << isYounger({{'A','B','C'},{'B','D','E'}}, 'A', 'E') << '\n';
}
