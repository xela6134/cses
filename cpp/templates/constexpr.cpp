#include <bits/stdc++.h>

// Shitty way (runtime)

template<typename T>
void shitProcess(T val) {
    if (std::is_integral<T>::value) {
        std::cout << "integer path: " << val << "\n";
    } else if (std::is_floating_point<T>::value) {
        std::cout << "float path: " << val << "\n";
    } else {
        std::cout << "other path: " << val << "\n";
    }
}

template<typename T>
void goodProcess(T val) {
    // without constexpr, all the paths are compiled

    ////////////////////////////////////////////////////////////////////
    // constexpr makes compiler discard the untaken branches entirely //
    ////////////////////////////////////////////////////////////////////

    // so (val << 1) will also be compiled with the string path
    // resulting in an error
    if constexpr (std::is_integral<T>::value) {
        std::cout << "integer path: " << (val << 1) << "\n";
    } else {
        std::cout << "other path: " << val << "\n";
    }
}

int main() {
    std::cout << '\n';
    shitProcess(42);
    shitProcess(3.14);
    shitProcess("lol");

    std::cout << '\n';
    goodProcess(42);
    goodProcess(3.14);
    goodProcess("lol");
}
