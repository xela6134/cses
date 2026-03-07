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

class LFUCache {
public:
    LFUCache(int c) : capacity(c) {}
    
    int get(int key) {
        if (cache.find(key) == cache.end()) return -1;
        
        increaseFreqs(key);        
        return cache[key].first;
    }
    
    void put(int key, int value) {
        if (cache.count(key)) {
            cache[key].first = value;
            increaseFreqs(key);
            return;
        }

        if (cache.size() >= capacity) resize();

        cache[key] = {value, 1};
        freqs[1].push_front(key);
        iters[key] = freqs[1].begin();

        minFreq = 1;
    }

private:
    int capacity;
    int minFreq = 0;

    // {key, {val, freq}}
    unordered_map<int, pair<int, int>> cache;
    // {freq, list_of_keys}
    unordered_map<int, list<int>> freqs;
    unordered_map<int, list<int>::iterator> iters;

    void increaseFreqs(int key) {
        int oldFreq = cache[key].second;
        
        // 1. Remove from old frequency list
        freqs[oldFreq].erase(iters[key]);

        // 2. If old list is empty, we might need to increment minFreq
        if (freqs[oldFreq].empty()) {
            freqs.erase(oldFreq);
            if (minFreq == oldFreq) {
                ++minFreq;
            }
        }

        // 3. Add to new frequency list
        int newFreq = oldFreq + 1;
        cache[key].second = newFreq;
        freqs[newFreq].push_front(key);
        iters[key] = freqs[newFreq].begin();
    }

    void resize() {
        int keyToEvict = freqs[minFreq].back();
        
        // 2. Remove from frequency list
        freqs[minFreq].pop_back();
        if (freqs[minFreq].empty()) {
            freqs.erase(minFreq);
        }

        // 3. Remove from cache and iterators
        cache.erase(keyToEvict);
        iters.erase(keyToEvict);
    }
};


int main() {
    
    return 0;
}
