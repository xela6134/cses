#include <bits/stdc++.h>
using namespace std;

class RateLimiter {
public:
    RateLimiter(int mc, int w) : maxCalls(mc), window(w) {

    }

    bool allow(int timestamp) {
        while (!times.empty() && timestamp - times.front() > window) {
            times.pop();
        }

        if (times.size() < maxCalls) return false;

        times.push(timestamp);

        return true;
    }
private:
    int maxCalls;
    int window;
    queue<int> times;
};

