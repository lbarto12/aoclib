#pragma once

#include <chrono>
#include <concepts>
#include <functional>

namespace aoc {

// any std::chrono::duration, e.g. std::chrono::milliseconds
template <typename T>
concept Duration = requires {
    typename T::rep;
    typename T::period;
} && std::same_as<T, std::chrono::duration<typename T::rep, typename T::period>>;

template <Duration T = std::chrono::milliseconds, typename Function, typename... Args>
    requires std::invocable<Function, Args...>
long long Timed(Function&& f, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    std::invoke(std::forward<Function>(f), std::forward<Args>(args)...);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<T>(end - start).count();
}

} // namespace aoc
