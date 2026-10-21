#include "str.h"
#include "../slice.h"

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
    return slice(*this, start, stop, step);
}
} // namespace aoc
