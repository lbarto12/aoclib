#include "str.h"

namespace aoc {

/*
 * Slice operator, like in python.
 * Negative indecies wrap around the length of the string
 *
 * You can slice a string with s(start, stop, step)
 *  str x = "hello";
 *  str y = x(1);
 *  y == "ello";
 *
 *  str x = "hello";
 *  str y = x(1, -1);
 *  y == "ell";
 *
 * if you wish to omit a preceding argument, you may use an anonymous object:
 *  str even = s({}, {}, 2);
 *
 * */
str str::operator()(std::optional<std::ptrdiff_t> start, std::optional<std::ptrdiff_t> stop,
                    std::ptrdiff_t step) const {
    if (step == 0) throw std::invalid_argument("slice step cannot be zero");
    const auto len = static_cast<std::ptrdiff_t>(size());

    auto adjust = [&](std::optional<std::ptrdiff_t> idx, std::ptrdiff_t fallback) {
        if (!idx) return fallback;
        std::ptrdiff_t i = *idx;
        if (i < 0) {
            i += len;
            if (i < 0) i = step < 0 ? -1 : 0;
        } else if (i >= len) {
            i = step < 0 ? len - 1 : len;
        }
        return i;
    };

    const std::ptrdiff_t lo = adjust(start, step < 0 ? len - 1 : 0);
    const std::ptrdiff_t hi = adjust(stop, step < 0 ? -1 : len);

    std::ptrdiff_t count = 0;
    if (step > 0 && lo < hi)
        count = (hi - lo - 1) / step + 1;
    else if (step < 0 && lo > hi)
        count = (hi - lo + 1) / step + 1;

    str out;
    out.reserve(static_cast<std::size_t>(count));
    for (std::ptrdiff_t k = 0; k < count; ++k) out += (*this)[lo + k * step];
    return out;
}
} // namespace aoc
