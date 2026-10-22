#include "str.h"

namespace aoc {

// Convert this string's legible, numeric value to integer type <T>; if possible.
// Throws invalid_argument if conversion is not possible
template <Integer T> T str::to_int() const {
    str t = strip();
    T v{};
    auto [p, ec] = std::from_chars(t.data(), t.data() + t.size(), v);
    if (ec != std::errc{} || p != t.data() + t.size()) throw std::invalid_argument("invalid integer: '" + t + "'");
    return v;
};

inline str::operator int() const { return to_int<int>(); }
inline str::operator long() const { return to_int<long>(); }
inline str::operator long long() const { return to_int<long long>(); }
inline str::operator std::size_t() const { return to_int<std::size_t>(); }

} // namespace aoc
