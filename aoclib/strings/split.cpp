#include "str.h"

namespace aoc {

str str::strip() const {
    const auto start = find_first_not_of(WS);
    if (start == npos) return {};
    const auto end = find_last_not_of(WS);
    return substr(start, end - start + 1);
}

std::vector<str> str::split() const {
    std::vector<str> result;
    std::size_t i = 0;
    while ((i = find_first_not_of(WS, i)) != std::string::npos) {
        std::size_t j = find_first_of(WS, i);
        result.push_back(substr(i, j - i));
        i = j;
    }
    return result;
}

std::vector<str> str::split(std::string_view sep, int maxsplit) const {
    if (sep.empty()) throw std::invalid_argument("empty separator");
    std::vector<str> result;
    std::size_t i = 0;
    for (std::size_t j = 0; maxsplit != 0 && (j = find(sep, i)) != std::string::npos; --maxsplit) {
        result.push_back(substr(i, j - i));
        i = j + sep.size();
    }
    result.push_back(substr(i));
    return result;
}

} // namespace aoc
