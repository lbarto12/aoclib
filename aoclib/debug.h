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

template <typename Range> void printl(const Range& iterable) {
    std::cout << '[';
    const char* sep = "";
    for (const auto& x : iterable) {
        std::cout << sep;
        print_one(std::cout, x);
        sep = ", ";
    }
    std::cout << "]\n";
}

} // namespace aoc
