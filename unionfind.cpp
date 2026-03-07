#include <bits/stdc++.h>
using namespace std;

class UnionFind {
public:
    // Initialize n elements, each in its own set
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }

    // Union by rank — returns false if already in same set
    bool unite(int x, int y) {
        int rx = find(x);
        int ry = find(y);
        if (rx == ry) return false; // already connected

        // Ensure rx has the taller root
        if (rank[rx] < rank[ry]) std::swap(rx, ry);

        // Attach smaller under larger
        parent[ry] = rx;            

        // Only increase rank
        if (rank[rx] == rank[ry]) rank[rx]++;

        return true;
    }

    // Check if two elements are in the same set
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
private:
    vector<int> parent;
    vector<int> rank;

    // Find with path compression
    int find(int x) {
        if (parent[x] != x) {
            // Intentionally compress path to root
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }
};
