#include <bits/stdc++.h>
using namespace std;

// Variadic templates
// accept any number of type/value parameters using the ... (parameter pack) syntax

// C++17 version
template<typename... Args>
void printing(const Args&... args) {
    ((std::cout << args << ", "), ...);
}

// Base case: single argument
template<typename T>
void print(const T& val) {
    std::cout << val << '\n';
}

// Recursive case: first arg + rest
template<typename T, typename... Args>
void print(const T& first, const Args&... rest) {
    std::cout << first << ", ";
    print(rest...);  // recursive instantiation with one fewer arg
}

int main() {
    // expands at COMPILE TIME to: cout << "abc" << ", " << 123 << ", " << 3.14
    print("abc", 123, 3.14);
    printing("abc", 123, 3.14);
    cout << '\n';
}
