#pragma once

#include <charconv>
#include <concepts>
#include <optional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>

#include "../../concepts.h"
#include "../../generic.h"
#include "../../index.h"
#include "../vector/vec.h"

namespace aoc {

// anything that can be concatenated onto a str
template <typename T>
concept StrLike = std::convertible_to<const T&, std::string_view> || std::same_as<T, char>;

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
        requires Arithmetic<N> && (!std::same_as<N, char>) && (!std::same_as<N, bool>)
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
    template <typename Range>
        requires std::ranges::range<const Range> && StrLike<std::ranges::range_value_t<const Range>>
    str join(const Range& parts) const;

    // python's replace: a copy with occurrences of `from` replaced by `to`, the first `count` only if count >= 0
    //  str("a-b-c").replace("-", "+")    == "a+b+c"
    //  str("a-b-c").replace("-", "", 1)  == "ab-c"
    // the positional std::string forms, s.replace(pos, len, "x"), still edit in place
    str replace(std::string_view from, std::string_view to, int count = -1) const;

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
    template <Integer T = long long> T to_int() const;

    // various int casts, expand to str.to_int<cast_type>();
    inline operator int() const;
    inline operator long() const;
    inline operator long long() const;
    inline operator std::size_t() const;

  public: // operators
    // slice operator
    str operator()(std::optional<std::ptrdiff_t> start = std::nullopt,
                   std::optional<std::ptrdiff_t> stop = std::nullopt, std::ptrdiff_t step = 1) const;

    // index operator, like python: negative indices wrap, s[-1] == last char. throws IndexError if out of range
    char& operator[](std::ptrdiff_t i);
    const char& operator[](std::ptrdiff_t i) const;

    // assign anything std::string can, returning str&
    template <typename T>
        requires(!std::derived_from<std::remove_cvref_t<T>, str>) &&
                requires(std::string& s, T&& x) { s = std::forward<T>(x); }
    str& operator=(T&& x);

    // append anything std::string can, returning str&
    template <typename T>
        requires requires(std::string& s, T&& x) { s += std::forward<T>(x); }
    str& operator+=(T&& x);

  public: // std::string methods, re-typed to return str instead of std::string
    str substr(size_type pos = 0, size_type n = npos) const;

    template <typename... Args>
        requires requires(std::string& s, Args&&... args) { s.append(std::forward<Args>(args)...); }
    str& append(Args&&... args);
    template <typename... Args>
        requires requires(std::string& s, Args&&... args) { s.assign(std::forward<Args>(args)...); }
    str& assign(Args&&... args);
    template <typename... Args>
        requires requires(std::string& s, Args&&... args) { s.replace(std::forward<Args>(args)...); }
    str& replace(Args&&... args);

    // iterator overloads still return iterators
    template <typename... Args>
        requires requires(std::string& s, Args&&... args) { s.insert(std::forward<Args>(args)...); }
    decltype(auto) insert(Args&&... args);
    template <typename... Args>
        requires requires(std::string& s, Args&&... args) { s.erase(std::forward<Args>(args)...); }
    decltype(auto) erase(Args&&... args);
};

// concatenation: str + x, x + str
template <StrLike T> str operator+(str lhs, const T& rhs);
template <StrLike T>
    requires(!std::derived_from<T, str>)
str operator+(const T& lhs, const str& rhs);

// repetition, like python: str("ab") * 3 == "ababab"
template <Integer N> str operator*(const str& s, N n);
template <Integer N> str operator*(N n, const str& s);

} // namespace aoc

// hash compat
template <> struct std::hash<aoc::str> : std::hash<std::string> {};

// templated includes
#include "conv.tpp"
#include "join.tpp"
#include "ops.tpp"
