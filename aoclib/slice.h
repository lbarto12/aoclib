#pragma once

#include <cstddef>
#include <optional>
#include <stdexcept>

#include "index.h"

namespace aoc {

/*
 * python-style slice of any indexable container, returning a new container of the same type.
 * Negative indecies wrap around the length of the container, out of range indecies are clamped.
 *
 *  slice(c, 1)         -> c[1:]
 *  slice(c, 1, -1)     -> c[1:-1]
 *  slice(c, {}, {}, 2) -> c[::2]
 * */
template <typename C>
C slice(const C& src, std::optional<std::ptrdiff_t> start, std::optional<std::ptrdiff_t> stop, std::ptrdiff_t step) {
    if (step == 0) throw std::invalid_argument("slice step cannot be zero");
    const auto len = static_cast<std::ptrdiff_t>(src.size());

    const std::ptrdiff_t lo = start ? clamp_index(*start, src.size(), step) : (step < 0 ? len - 1 : 0);
    const std::ptrdiff_t hi = stop ? clamp_index(*stop, src.size(), step) : (step < 0 ? -1 : len);

    std::ptrdiff_t count = 0;
    if (step > 0 && lo < hi)
        count = (hi - lo - 1) / step + 1;
    else if (step < 0 && lo > hi)
        count = (hi - lo + 1) / step + 1;

    C out;
    out.reserve(static_cast<std::size_t>(count));
    for (std::ptrdiff_t k = 0; k < count; ++k) out.push_back(src[static_cast<std::size_t>(lo + k * step)]);
    return out;
}

} // namespace aoc
