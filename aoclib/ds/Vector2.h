#pragma once
// IWYU pragma: private, include <aoclib/lib.h>

#include <array>
#include <cstddef>
#include <functional>
#include <ostream>
#include <vector>

#include "../concepts.h"

namespace aoc {

// Simple definition of a 2 point set.
// This is good for positions, directions, vectors, etc.
// Includes operator overloads for basic arithmetic operations (+, -, *, /, %)
template <Arithmetic T> struct vec2 {
    T x{}, y{};

    constexpr vec2() = default;
    constexpr vec2(T x, T y) : x(x), y(y) {}

  public: // methods
    std::vector<vec2> adjacent4() const {
        static constexpr std::array<std::array<int, 2>, 4> d = {{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};
        std::vector<vec2> res;
        res.reserve(4);
        for (auto [dx, dy] : d) res.emplace_back(static_cast<T>(x + dx), static_cast<T>(y + dy));
        return res;
    }

    std::vector<vec2> adjacent8() const {
        std::vector<vec2<T>> res;
        res.reserve(8);

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (!i && !j) continue;
                res.emplace_back(static_cast<T>(x + j), static_cast<T>(y + i));
            }
        }

        return res;
    }

  public: // operators
    constexpr vec2& operator+=(const vec2& o) {
        x += o.x;
        y += o.y;
        return *this;
    }
    constexpr vec2& operator-=(const vec2& o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
    constexpr vec2& operator*=(const vec2& o) {
        x *= o.x;
        y *= o.y;
        return *this;
    }
    constexpr vec2& operator/=(const vec2& o) {
        x /= o.x;
        y /= o.y;
        return *this;
    }
    constexpr vec2& operator%=(const vec2& o) {
        x %= o.x;
        y %= o.y;
        return *this;
    }

    constexpr vec2& operator+=(T c) {
        x += c;
        y += c;
        return *this;
    }
    constexpr vec2& operator-=(T c) {
        x -= c;
        y -= c;
        return *this;
    }
    constexpr vec2& operator*=(T c) {
        x *= c;
        y *= c;
        return *this;
    }
    constexpr vec2& operator/=(T c) {
        x /= c;
        y /= c;
        return *this;
    }
    constexpr vec2& operator%=(T c) {
        x %= c;
        y %= c;
        return *this;
    }

  public: // binary operators, defined in terms of compounds
    friend constexpr vec2 operator+(vec2 a, const vec2& b) { return a += b; }
    friend constexpr vec2 operator-(vec2 a, const vec2& b) { return a -= b; }
    friend constexpr vec2 operator*(vec2 a, const vec2& b) { return a *= b; }
    friend constexpr vec2 operator/(vec2 a, const vec2& b) { return a /= b; }
    friend constexpr vec2 operator%(vec2 a, const vec2& b) { return a %= b; }

    friend constexpr vec2 operator+(vec2 a, T c) { return a += c; }
    friend constexpr vec2 operator-(vec2 a, T c) { return a -= c; }
    friend constexpr vec2 operator*(vec2 a, T c) { return a *= c; }
    friend constexpr vec2 operator*(T c, vec2 a) { return a *= c; }
    friend constexpr vec2 operator/(vec2 a, T c) { return a /= c; }
    friend constexpr vec2 operator%(vec2 a, T c) { return a %= c; }

  public: // unary
    constexpr vec2 operator-() const { return {static_cast<T>(-x), static_cast<T>(-y)}; }

  public: // comparison
    friend constexpr bool operator==(const vec2& a, const vec2& b) { return a.x == b.x && a.y == b.y; }
    friend constexpr bool operator!=(const vec2& a, const vec2& b) { return !(a == b); }
    friend constexpr bool operator<(const vec2& a, const vec2& b) { return a.y != b.y ? a.y < b.y : a.x < b.x; }

  public: // fmt
    friend std::ostream& operator<<(std::ostream& s, const vec2& v) { return s << '(' << v.x << ", " << v.y << ')'; }
};

using vec2i = vec2<int>;
using vec2u = vec2<std::size_t>;
using vec2f = vec2<float>;
using vec2d = vec2<double>;
using vec2c = vec2<char>;

} // namespace aoc

// define hash for vectors
template <aoc::Arithmetic T> struct std::hash<aoc::vec2<T>> {
    std::size_t operator()(const aoc::vec2<T>& v) const noexcept {
        std::size_t h1 = std::hash<T>{}(v.x);
        std::size_t h2 = std::hash<T>{}(v.y);
        // bit mix, fractional parts of phi :)
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};
