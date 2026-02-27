#include <bits/stdc++.h>
using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : size(capacity) {
        
    }
    
    int get(int key) {
        if (!values.count(key)) return -1;

        // 1. If exists, move to front
        moveToRecent(key);

        // 2. Return value
        return values[key];
    }
    
    void put(int key, int value) {
        // 1. Update value
        values[key] = value;

        // 2. Move recents
        moveToRecent(key);

        // 3. If size is out of capacity, evict last in list
        if (values.size() > size) evict();
    }
private:
    int size;
    unordered_map<int, int> values;
    unordered_map<int, list<int>::iterator> iterators;
    list<int> orders;

    void moveToRecent(int key) {
        if (iterators.count(key)) {
            orders.erase(iterators[key]);
        }

        orders.push_front(key);
        iterators[key] = orders.begin();
    }

    void evict() {
        // Get back element

        int oldest = orders.back();
        orders.pop_back();
        iterators.erase(oldest);
        values.erase(oldest);
    }
};

int main() {
    
    return 0;
}
