#include <bits/stdc++.h>
using namespace std;

// Template metaprogramming
// Exploiting this compile-time machinery to compute things at compile time

// Factorials

template<int N>
struct Factorial {
    static constexpr int value = N * Factorial<N-1>::value;
};

template<>
struct Factorial<0> {
    static constexpr int value = 1;
};

// Fibonacci Sequence

template<int N>
struct Fibonacci {
    static constexpr int value = Fibonacci<N-1>::value + Fibonacci<N-2>::value;
};

template<>
struct Fibonacci<0> {
    static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
    static constexpr int value = 1;
};

int main() {
    cout << Factorial<5>::value << '\n';
    cout << Fibonacci<10>::value << '\n';
}
