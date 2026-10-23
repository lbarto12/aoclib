#pragma once

#include <regex>

#include "../ds/strings/str.h"
#include "../ds/vector/vec.h"

namespace aoc {
struct regex {
    regex(const str& pattern) : pattern(pattern) {}

    bool fullmatch(const str& text) const { return std::regex_match(text, pattern); }

    vec<str> findall(const str& text) const {
        auto begin = std::sregex_iterator(text.begin(), text.end(), pattern);
        auto end = std::sregex_iterator();

        vec<str> res;

        for (std::regex_iterator i = begin; i != end; ++i) {
            std::smatch match = *i;
            res.push_back(match.str());
        }

        return res;
    }

    str replace(const str& text, const str& replacement) const {
        return std::regex_replace(text, pattern, replacement);
    }

  private:
    std::regex pattern;
};
} // namespace aoc
