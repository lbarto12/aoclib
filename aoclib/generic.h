#pragma once

#include <vector>

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

template <typename Out = void, typename F, typename Iterable> auto map(F f, const Iterable& iter) {
    using Result = std::decay_t<std::invoke_result_t<F&, decltype(*std::begin(iter))>>;
    using T = std::conditional_t<std::is_void_v<Out>, Result, Out>;

    std::vector<T> res;
    if constexpr (requires { std::size(iter); }) res.reserve(std::size(iter));
    for (const auto& x : iter) res.push_back(f(x));
    return res;
}

template <typename... Iterables> auto zip(const Iterables&... iters) {
    static_assert(sizeof...(Iterables) > 0, "zip needs at least one iterable");
    using T = std::tuple<std::decay_t<decltype(*std::begin(iters))>...>;

    const std::size_t n = std::min({static_cast<std::size_t>(std::size(iters))...});
    std::vector<T> res;
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

} // namespace aoc
