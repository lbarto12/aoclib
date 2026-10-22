#pragma once

#include "concepts.h"
#include "ds/vector/vec.h"
#include <concepts>
#include <functional>
#include <iterator>
#include <numeric>
#include <ranges>
#include <type_traits>

namespace aoc {
template <typename F, typename Iterable>
    requires std::ranges::range<const Iterable> && std::predicate<F&, std::ranges::range_reference_t<const Iterable>>
bool all(F f, const Iterable& iter) {
    for (const auto& i : iter)
        if (!f(i)) return false;
    return true;
}

template <typename Iterable>
    requires std::ranges::range<const Iterable> &&
             std::constructible_from<bool, std::ranges::range_reference_t<const Iterable>>
bool all(const Iterable& iter) {
    for (const auto& i : iter)
        if (!i) return false;
    return true;
}

template <typename F, typename Iterable>
    requires std::ranges::range<const Iterable> && std::predicate<F&, std::ranges::range_reference_t<const Iterable>>
bool any(F f, const Iterable& iter) {
    for (const auto& i : iter)
        if (f(i)) return true;
    return false;
}

template <typename Iterable>
    requires std::ranges::range<const Iterable> &&
             std::constructible_from<bool, std::ranges::range_reference_t<const Iterable>>
bool any(const Iterable& iter) {
    for (const auto& i : iter)
        if (i) return true;
    return false;
}

template <typename Out = void, typename F, typename Iterable>
    requires std::ranges::range<const Iterable> && std::invocable<F&, std::ranges::range_reference_t<const Iterable>> &&
             (std::is_void_v<Out> ||
              std::convertible_to<std::invoke_result_t<F&, std::ranges::range_reference_t<const Iterable>>, Out>)
auto map(const Iterable& iter, F f) {
    using Result = std::decay_t<std::invoke_result_t<F&, decltype(*std::begin(iter))>>;
    using T = std::conditional_t<std::is_void_v<Out>, Result, Out>;

    vec<T> res;
    if constexpr (std::ranges::sized_range<const Iterable>) res.reserve(std::size(iter));
    for (const auto& x : iter) res.push_back(f(x));
    return res;
}

template <typename... Iterables>
    requires(std::ranges::range<const Iterables> && ...)
auto zip(const Iterables&... iters) {
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

template <typename Range>
    requires std::ranges::range<const Range>
auto enumerate(const Range& iterable, std::ptrdiff_t start = 0) {
    using T = std::decay_t<decltype(*std::begin(iterable))>;
    vec<std::pair<std::ptrdiff_t, T>> res;

    if constexpr (std::ranges::sized_range<const Range>) res.reserve(std::size(iterable));

    for (const auto& v : iterable) {
        res.emplace_back(start++, v);
    }
    return res;
}

// python's sorted(): a new, stably sorted vec of any iterable's elements. sorted(s, key), sorted(s, {}, true)
template <typename Iterable, typename Key = std::identity>
    requires RangeOf<Iterable, std::ranges::range_value_t<const Iterable>> &&
             std::sortable<typename vec<std::ranges::range_value_t<const Iterable>>::iterator, std::ranges::less, Key>
auto sorted(const Iterable& iter, Key key = {}, bool reverse = false) {
    vec<std::ranges::range_value_t<const Iterable>> res;
    res.extend(iter);
    res.sort(key, reverse);
    return res;
}

template <typename Range, typename T = std::decay_t<decltype(*std::begin(std::declval<const Range&>()))>>
    requires std::ranges::range<const Range> &&
             requires(T acc, std::ranges::range_reference_t<const Range> x) { acc = acc + x; }
T sum(const Range& iterable, T start = T{}) {
    return std::accumulate(std::begin(iterable), std::end(iterable), start);
}

template <std::integral T> constexpr T mod(T a, T b) {
    T r = a % b;
    if (r != 0 && ((r < 0) != (b < 0))) r += b;
    return r;
}

// Python's //, which floors instead of truncating
template <std::integral T> constexpr T floordiv(T a, T b) {
    T q = a / b;
    if ((a % b != 0) && ((a < 0) != (b < 0))) --q;
    return q;
}

} // namespace aoc
