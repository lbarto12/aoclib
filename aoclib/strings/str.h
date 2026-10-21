#pragma once

#include <charconv>
#include <optional>
#include <stdexcept>
#include <string>
#include <string_view>

#include "../generic.h"
#include "../vector/vec.h"

namespace aoc {

// std::string wrapper to more easily facilitate some common string methods
class str : public std::string {
    // whitespace chars
    static constexpr const char* WS = " \t\n\r\f\v";

  public: // b5
    using std::string::string;

    str() = default;
    str(const std::string& s) : std::string(s) {}
    str(std::string&& s) noexcept : std::string(std::move(s)) {}

    // cool extras
    template <typename N>
        requires std::is_arithmetic_v<N> && (!std::same_as<N, char>) && (!std::same_as<N, bool>)
    explicit str(N n) {
        char buf[64];
        auto [end, ec] = std::to_chars(buf, buf + sizeof buf, n);
        assign(buf, end);
    }

    explicit str(char c) : std::string(1, c) {}                 // str('a') -> "a"
    explicit str(bool b) : std::string(b ? "true" : "false") {} // like Python

  public: // extra pythonic stuff
    // Strip whitespace off both ends of string
    str strip() const;

    // Split string on whitespace
    vec<str> split() const;

    // Split string on delimiter
    vec<str> split(std::string_view sep, int maxsplit = -1) const;

    // Split on newlines, os agnostic
    vec<str> splitlines() const;

    // join multiple strings into a single string, using *this* string as a delimiter
    template <typename Range> str join(const Range& parts) const;

  public: // properties
    // is the string a valid integer
    bool isdigit() const;

    // is the string only alphabetical characters
    bool isalpha() const;

    // is the string solely whitespace
    bool isspace() const;

    // uppercase copy of this string
    str upper() const;

    // lowercase copy of this string
    str lower() const;

  public: // casts
    // covert this string into character-integer representation
    // templated to control resulting int-type
    template <typename T> T to_int() const;

    // various int casts, expand to str.to_int<cast_type>();
    inline operator int() const;
    inline operator long() const;
    inline operator long long() const;
    inline operator std::size_t() const;

  public: // operators
    // slice operator
    str operator()(std::optional<std::ptrdiff_t> start = std::nullopt,
                   std::optional<std::ptrdiff_t> stop = std::nullopt, std::ptrdiff_t step = 1) const;
};

} // namespace aoc

// hash compat
template <> struct std::hash<aoc::str> : std::hash<std::string> {};

// templated includes
#include "conv.tpp"
#include "join.tpp"
