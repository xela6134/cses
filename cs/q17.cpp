#include <bits/stdc++.h>
using namespace std;

map<string, vector<int>> roundRobin(vector<string> workers, int tasks) {
    int n = workers.size();
    unordered_map<int, string> names;

    // 1. Map the strings to IDs
    for (int i = 0; i < workers.size(); ++i) {
        names[i] = workers[i];
    }

    map<string, vector<int>> result;

    // 2. Loop
    for (int i = 0; i < tasks; ++i) {
        int turn = i % n;
        result[names[turn]].push_back(i + 1);
    }

    return result;
}

int main() {
    map<string, vector<int>> res = roundRobin({"A", "B", "C"}, 7);

    for (const auto& [worker, tasks] : res) {
        cout << "Worker " << worker << ": ";

        for (int task : tasks) {
            cout << task << ", ";
        }
        cout << '\n';
    }
}
