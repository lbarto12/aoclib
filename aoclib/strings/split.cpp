#include "str.h"

namespace aoc {

// strip whitespace off both ends of the string
str str::strip() const {
    const auto start = find_first_not_of(WS);
    if (start == npos) return {};
    const auto end = find_last_not_of(WS);
    return substr(start, end - start + 1);
}

// split the string on whitespace
vec<str> str::split() const {
    vec<str> result;
    std::size_t i = 0;
    while ((i = find_first_not_of(WS, i)) != std::string::npos) {
        std::size_t j = find_first_of(WS, i);
        result.push_back(substr(i, j - i));
        i = j;
    }
    return result;
}

// split the string on a specific delimiter
vec<str> str::split(std::string_view sep, int maxsplit) const {
    if (sep.empty()) throw std::invalid_argument("empty separator");
    vec<str> result;
    std::size_t i = 0;
    for (std::size_t j = 0; maxsplit != 0 && (j = find(sep, i)) != std::string::npos; --maxsplit) {
        result.push_back(substr(i, j - i));
        i = j + sep.size();
    }
    result.push_back(substr(i));
    return result;
}

// Split on new lines, handles \n && \r\n and omits a final, empty line
vec<str> str::splitlines() const {
    vec<str> out;
    for (std::size_t i = 0; i < size();) {
        std::size_t j = find('\n', i);
        if (j == npos) j = size();
        std::size_t e = (j > i && (*this)[j - 1] == '\r') ? j - 1 : j;
        out.push_back(substr(i, e - i));
        i = j + 1;
    }
    return out;
}

} // namespace aoc
