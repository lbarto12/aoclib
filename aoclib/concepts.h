#pragma once

#include <concepts>
#include <cstddef>
#include <functional>
#include <ostream>
#include <ranges>
#include <tuple>
#include <type_traits>

namespace aoc {

// any built-in number type, including char and bool
template <typename T>
concept Arithmetic = std::is_arithmetic_v<T>;

// an integer type that isn't bool
template <typename T>
concept Integer = std::integral<T> && !std::same_as<T, bool>;

// can be written with os << x
template <typename T>
concept Streamable = requires(std::ostream& os, const T& x) { os << x; };

// tuple, pair, array: anything std::tuple_size and std::apply work on
template <typename T>
concept TupleLike = requires { std::tuple_size<T>::value; };

// anything print_one knows how to print
template <typename T>
concept Printable = Streamable<T> || TupleLike<T>;

// usable as an unordered_map / unordered_set key
template <typename T>
concept Hashable = std::equality_comparable<T> && requires(const T& x) {
    { std::hash<T>{}(x) } -> std::convertible_to<std::size_t>;
};

// a range that can be iterated while const, whose elements can construct a T
template <typename R, typename T>
concept RangeOf = std::ranges::range<const R> && std::constructible_from<T, std::ranges::range_reference_t<const R>>;

} // namespace aoc
