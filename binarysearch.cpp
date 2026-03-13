#include <bits/stdc++.h>
using namespace std;

struct Order {
    double price;
    int quantity;
    std::string symbol;
};

struct CompareByPrice {
    bool operator()(const Order& a, const Order& b) const {
        return a.price < b.price;
    }
};

int main() {
    std::vector<int> v = {1, 3, 5, 7, 9};
    std::binary_search(v.begin(), v.end(), 5);   // true
    std::binary_search(v.begin(), v.end(), 4);   // false

    std::vector<Order> book = {
        {10.0, 100, "AAPL"},
        {20.5, 200, "GOOG"},
        {30.0, 50,  "MSFT"},
        {45.0, 300, "TSLA"},
    };

    Order target{30.0, 0, ""};

    // Using binary_search with custom comparator
    bool found = std::binary_search(book.begin(), book.end(), target, CompareByPrice{});
    cout << boolalpha << found << '\n';

    // Using lower_bound with custom comparator
    auto it = std::lower_bound(book.begin(), book.end(), target, CompareByPrice{});
    cout << it->price << '\n';
}
