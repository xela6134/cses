#include <bits/stdc++.h>
using namespace std;

class Stream {
public:
    Stream() {
        reservoir = 0;
        count = 0;
    }

    void add(int num) {
        ++count;

        if (rand() % count == 0) reservoir = num;

        if (low.empty() || num <= low.top()) low.push(num);
        else high.push(num);

        balance();
    }

    int getRandom() const {
        return reservoir;
    }

    double median() const {
        if (low.size() == 0 && high.size() == 0) return 0.0;

        if (low.size() == high.size()) return (low.top() + high.top()) / 2.0;
        return low.size() > high.size() ? low.top() : high.top();
    }
private:
    int reservoir;
    int count;

    // max heap (lower half)
    // min heap (higher half)
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int>> high;

    void balance() {
        if (low.size() > high.size() + 1) { 
            high.push(low.top()); 
            low.pop(); 
        } else if (high.size() > low.size() + 1) {
            low.push(high.top());
            high.pop();
        }
    }
};

int main() {
    
    return 0;
}
