#pragma once

#include <charconv>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include "../generic.h"

namespace aoc {
class str : public std::string {
    static constexpr const char* WS = " \t\n\r\f\v";

  public: // b5
    using std::string::string;

    str() = default;
    str(const std::string& s) : std::string(s) {}
    str(std::string&& s) noexcept : std::string(std::move(s)) {}

  public: // extra pythonic stuff
    // Strip whitespace off both ends of string
    str strip() const;
    std::vector<str> split() const;
    std::vector<str> split(std::string_view sep, int maxsplit) const;
    template <typename Range> str join(const Range& parts) const;

  public: // properties
    bool isdigit() const;
    bool isalpha() const;
    bool isspace() const;

    str upper() const;
    str lower() const;

  public: // casts
    template <typename T> T to_int() const;

    inline operator int() const;
    inline operator long() const;
    inline operator long long() const;
    inline operator std::size_t() const;

  public: // slice as operator
    str operator()(std::optional<std::ptrdiff_t> start, std::optional<std::ptrdiff_t> stop, std::ptrdiff_t step) const;
};
} // namespace aoc

#include "conv.tpp"
#include "join.tpp"
