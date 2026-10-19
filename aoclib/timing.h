#pragma once

#include <chrono>
#include <functional>

namespace aoc {

template <typename T = std::chrono::milliseconds, typename Function, typename... Args>
long long Timed(Function&& f, Args&&... args) {
    auto start = std::chrono::steady_clock::now();
    std::invoke(std::forward<Function>(f), std::forward<Args>(args)...);
    auto end = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<T>(end - start).count();
}

} // namespace aoc
