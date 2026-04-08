#include <bits/stdc++.h>

// SFINAE: Substitution Failure Is Not An Error
// SFINAE resolves the branch before the binary even exists 
// The generated code contains only the path that applies

// Only enabled for integers
template<typename T>
typename std::enable_if<std::is_integral<T>::value, void>::type
process(T val) {
    std::cout << "integer path: " << (val << 1) << "\n";
}

// Only enabled for floating point
template<typename T>
typename std::enable_if<std::is_floating_point<T>::value, void>::type
process(T val) {
    std::cout << "float path: " << val << "\n";
}

// Everything else
template<typename T>
typename std::enable_if<!std::is_integral<T>::value && !std::is_floating_point<T>::value, void>::type
process(T val) {
    std::cout << "other path: " << val << "\n";
}

// Modern, C++17 version
template<typename T>
void modernProcess(T val) {
    if constexpr (std::is_integral_v<T>) {
        std::cout << "integer path: " << val << "\n";
    } else if constexpr (std::is_floating_point_v<T>) {
        std::cout << "float path: " << val << "\n";
    } else {
        std::cout << "other path: " << val << "\n";
    }
}

// Both SFINAE and if constexpr produce exactly this:
// void process(int val)         { std::cout << "integer path: " << (val << 1) << "\n"; }
// void process(double val)      { std::cout << "non-integer path: " << val << "\n"; }
// void process(const char* val) { std::cout << "non-integer path: " << val << "\n"; }

// Benefits of SFINAE / if constexpr compared to regular if
// Correctness (the main reason)
// -> untaken branches are discarded before type-checking, 
//    so you can write type-specific code like bit shifts without worrying about other types
// No branch (minor)
// -> no conditional jump in the generated assembly, 
//    which matters in aggregate in hot paths but is negligible for isolated calls

int main() {
    process(42);
    process(3.14);
    process("lol");

    modernProcess(42);
    modernProcess(3.14);
    modernProcess("lol");
}
