#include <bits/stdc++.h>

int main() {
    std::vector<int> data = {1, 3, 5, 5, 5, 8, 10};

    // Searching for 5
    auto lb = std::lower_bound(data.begin(), data.end(), 5);
    auto ub = std::upper_bound(data.begin(), data.end(), 5);

    std::cout << "lower_bound (>= 5): " << *lb << "\n"; // Points to 5
    std::cout << "upper_bound (>  5): " << *ub << "\n"; // Points to 8

    // Searching for a missing value (e.g., 4)
    // Both will point to the same element: 5
    auto lb_miss = std::lower_bound(data.begin(), data.end(), 4);
    auto ub_miss = std::upper_bound(data.begin(), data.end(), 4);
    std::cout << "lower_bound for 4: " << *lb_miss << "\n"; 
    std::cout << "upper_bound for 4: " << *ub_miss << "\n"; 
}