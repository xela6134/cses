#include <bits/stdc++.h>
using namespace std;

class SnapshotArray {
public:
    SnapshotArray(int length) {
        
    }
    
    void set(int index, int val) {
        cache[index] = val;
    }
    
    int snap() {
        ++snap_id;
        for (auto& [index, value] : cache) {
            snapshots[index][snap_id] = value;
        }

        return snap_id;
    }
    
    int get(int index, int snap_id) {
        auto it = snapshots[index].upper_bound(index);

        if (it == snapshots[index].begin()) return 0;

        it = prev(it);
        return it->second;
    }
private:
    int snap_id = -1;

    // {index, value}
    unordered_map<int, int> cache;

    // cache[index][snap_id]
    unordered_map<int, map<int, int>> snapshots;
};
