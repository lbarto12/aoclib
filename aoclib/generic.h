#pragma once

#include "vector/vec.h"
#include <iterator>
#include <numeric>
#include <type_traits>

namespace aoc {
template <typename F, typename Iterable> bool all(F f, const Iterable& iter) {
    for (const auto& i : iter)
        if (!f(i)) return false;
    return true;
}

template <typename Iterable> bool all(const Iterable& iter) {
    for (const auto& i : iter)
        if (!i) return false;
    return true;
}

template <typename F, typename Iterable> bool any(F f, const Iterable& iter) {
    for (const auto& i : iter)
        if (f(i)) return true;
    return false;
}

template <typename Iterable> bool any(const Iterable& iter) {
    for (const auto& i : iter)
        if (i) return true;
    return false;
}

template <typename Out = void, typename F, typename Iterable> auto map(const Iterable& iter, F f) {
    using Result = std::decay_t<std::invoke_result_t<F&, decltype(*std::begin(iter))>>;
    using T = std::conditional_t<std::is_void_v<Out>, Result, Out>;

    vec<T> res;
    if constexpr (requires { std::size(iter); }) res.reserve(std::size(iter));
    for (const auto& x : iter) res.push_back(f(x));
    return res;
}

template <typename... Iterables> auto zip(const Iterables&... iters) {
    static_assert(sizeof...(Iterables) > 0, "zip needs at least one iterable");
    using T = std::tuple<std::decay_t<decltype(*std::begin(iters))>...>;

    const std::size_t n = std::min({static_cast<std::size_t>(std::size(iters))...});
    vec<T> res;
    res.reserve(n);

    auto its = std::tuple{std::begin(iters)...};
    for (std::size_t k = 0; k < n; ++k) {
        std::apply(
            [&](auto&... it) {
                res.emplace_back(*it...); // build one tuple from every current element
                (++it, ...);              // advance every iterator
            },
            its);
    }
    return res;
}

template <typename Range> auto enumerate(const Range& iterable, std::size_t start = 0) {
    using T = std::decay_t<decltype(*std::begin(iterable))>;
    vec<std::pair<int, T>> res;

    if constexpr (requires { std::size(iterable); }) res.reserve(std::size(iterable));

    for (const auto& v : iterable) {
        res.emplace_back(start++, v);
    }
    return res;
}

template <typename Range, typename T = std::decay_t<decltype(*std::begin(std::declval<const Range&>()))>>
T sum(const Range& iterable, T start = T{}) {
    return std::accumulate(std::begin(iterable), std::end(iterable), start);
}

template <typename T> constexpr T mod(T a, T b) {
    T r = a % b;
    if (r != 0 && ((r < 0) != (b < 0))) r += b;
    return r;
}

// Python's //, which floors instead of truncating
template <typename T> constexpr T floordiv(T a, T b) {
    T q = a / b;
    if ((a % b != 0) && ((a < 0) != (b < 0))) --q;
    return q;
}

} // namespace aoc
