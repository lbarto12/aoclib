#include "str.h"

namespace aoc {

template <typename Range> str str::join(const Range& parts) const {
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
