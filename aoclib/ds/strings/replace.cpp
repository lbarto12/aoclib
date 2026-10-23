#include "str.h"

namespace aoc {

// python's replace. An empty `from` matches between every char and at both ends, like python:
//  str("abc").replace("", "-") == "-a-b-c-"
str str::replace(std::string_view from, std::string_view to, int count) const {
    int done = 0;
    auto more = [&] { return count < 0 || done < count; };

    str out;
    if (from.empty()) {
        for (std::size_t i = 0; i <= size(); ++i) {
            if (more()) {
                out += to;
                ++done;
            }
            if (i < size()) out += data()[i];
        }
        return out;
    }

    std::size_t i = 0;
    for (std::size_t j; more() && (j = find(from, i)) != npos; ++done) {
        out.append(data() + i, j - i);
        out += to;
        i = j + from.size();
    }
    out.append(data() + i, size() - i);
    return out;
}

} // namespace aoc
