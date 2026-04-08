#include <bits/stdc++.h>
// using namespace std;

// Template metaprogramming

// is_same implementation

template<typename T, typename U>
struct is_same { static constexpr bool value = false; };

template<typename T>
struct is_same<T, T> { static constexpr bool value = true; };

int main() {
    std::cout << std::boolalpha;
    std::cout << "int, int: " << is_same<int, int>::value << "\n";       // true
    std::cout << "int, double: " << is_same<int, double>::value << "\n"; // false
}
