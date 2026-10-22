#pragma once

#include <cstddef>
#include <string>

#include "errors.h"

namespace aoc {

/*
 * python-style element index: negative indecies wrap around from the end.
 * Throws IndexError if i is outside [-len, len)
 *
 *  wrap_index(-1, 5) == 4
 *  wrap_index(2, 5)  == 2
 *  wrap_index(5, 5)  -> IndexError
 * */
inline std::size_t wrap_index(std::ptrdiff_t i, std::size_t len) {
    const auto n = static_cast<std::ptrdiff_t>(len);
    const std::ptrdiff_t w = i < 0 ? i + n : i;
    if (w < 0 || w >= n)
        throw IndexError("index " + std::to_string(i) + " out of range for length " + std::to_string(len));
    return static_cast<std::size_t>(w);
}

/*
 * python-style slice bound: negative indecies wrap around from the end,
 * then out of range indecies are clamped to the nearest valid bound for the step's direction.
 * Never throws.
 *
 *  clamp_index(-1, 5)     == 4
 *  clamp_index(10, 5)     == 5
 *  clamp_index(10, 5, -1) == 4
 *  clamp_index(-10, 5, -1) == -1
 * */
inline std::ptrdiff_t clamp_index(std::ptrdiff_t i, std::size_t len, std::ptrdiff_t step = 1) {
    const auto n = static_cast<std::ptrdiff_t>(len);
    if (i < 0) {
        i += n;
        if (i < 0) i = step < 0 ? -1 : 0;
    } else if (i >= n) {
        i = step < 0 ? n - 1 : n;
    }
    return i;
}

} // namespace aoc
