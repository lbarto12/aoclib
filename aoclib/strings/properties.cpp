#include "str.h"

namespace aoc {

bool str::isdigit() const {
    return !empty() && all([](unsigned char c) { return std::isdigit(c); }, *this);
}

bool str::isalpha() const {
    return !empty() && all([](unsigned char c) { return std::isalpha(c); }, *this);
}

bool str::isspace() const {
    return !empty() && all([](unsigned char c) { return std::isspace(c); }, *this);
}

str str::upper() const {
    str out = *this;
    for (auto& c : out) c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    return out;
}

str str::lower() const {
    str out = *this;
    for (auto& c : out) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
    return out;
}

} // namespace aoc
