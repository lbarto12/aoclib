#pragma once

#include <iostream>
#include <tuple>

namespace aoc {

template <typename T> void print_one(std::ostream& os, const T& x) {
    if constexpr (requires { std::tuple_size<T>::value; }) { // tuple, pair, array
        os << '(';
        std::apply(
            [&](const auto&... xs) {
                const char* sep = "";
                ((os << sep, print_one(os, xs), sep = ", "), ...);
            },
            x);
        os << ')';
    } else {
        os << x;
    }
}

template <typename Range> void printit(const Range& iterable) {
    std::cout << '[';
    const char* sep = "";
    for (const auto& x : iterable) {
        std::cout << sep;
        print_one(std::cout, x);
        sep = ", ";
    }
    std::cout << "]\n";
}

// Python's print(): prints each arg space separated, followed by a newline
template <typename... Args> void println(const Args&... args) {
    [[maybe_unused]] const char* sep = "";
    ((std::cout << sep, print_one(std::cout, args), sep = " "), ...);
    std::cout << '\n';
}

} // namespace aoc
