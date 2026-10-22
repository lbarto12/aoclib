#include "str.h"

namespace aoc {

// Join multiple strings into a single `str` object.
// Uses *this* string as a delimiter
//  str joined = str(", ").join(vec<str>({"1", "2", "3"}));
//  joined == "1, 2, 3"
template <typename Range>
    requires std::ranges::range<const Range> && StrLike<std::ranges::range_value_t<const Range>>
str str::join(const Range& parts) const {
    str res;
    bool first = true;
    for (const auto& p : parts) {
        if (!first) res += *this;
        res += p;
        first = false;
    }
    return res;
}

} // namespace aoc
