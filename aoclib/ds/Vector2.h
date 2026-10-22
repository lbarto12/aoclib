#pragma once

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
template <Arithmetic T> struct Vector2 {
    T x{}, y{};

    constexpr Vector2() = default;
    constexpr Vector2(T x, T y) : x(x), y(y) {}

  public: // methods
    std::vector<Vector2> adjacent4() const {
        static constexpr std::array<std::array<int, 2>, 4> d = {{{0, -1}, {1, 0}, {0, 1}, {-1, 0}}};
        std::vector<Vector2> res;
        res.reserve(4);
        for (auto [dx, dy] : d) res.emplace_back(static_cast<T>(x + dx), static_cast<T>(y + dy));
        return res;
    }

    std::vector<Vector2> adjacent8() const {
        std::vector<Vector2<T>> res;
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
    constexpr Vector2& operator+=(const Vector2& o) {
        x += o.x;
        y += o.y;
        return *this;
    }
    constexpr Vector2& operator-=(const Vector2& o) {
        x -= o.x;
        y -= o.y;
        return *this;
    }
    constexpr Vector2& operator*=(const Vector2& o) {
        x *= o.x;
        y *= o.y;
        return *this;
    }
    constexpr Vector2& operator/=(const Vector2& o) {
        x /= o.x;
        y /= o.y;
        return *this;
    }
    constexpr Vector2& operator%=(const Vector2& o) {
        x %= o.x;
        y %= o.y;
        return *this;
    }

    constexpr Vector2& operator+=(T c) {
        x += c;
        y += c;
        return *this;
    }
    constexpr Vector2& operator-=(T c) {
        x -= c;
        y -= c;
        return *this;
    }
    constexpr Vector2& operator*=(T c) {
        x *= c;
        y *= c;
        return *this;
    }
    constexpr Vector2& operator/=(T c) {
        x /= c;
        y /= c;
        return *this;
    }
    constexpr Vector2& operator%=(T c) {
        x %= c;
        y %= c;
        return *this;
    }

  public: // binary operators, defined in terms of compounds
    friend constexpr Vector2 operator+(Vector2 a, const Vector2& b) { return a += b; }
    friend constexpr Vector2 operator-(Vector2 a, const Vector2& b) { return a -= b; }
    friend constexpr Vector2 operator*(Vector2 a, const Vector2& b) { return a *= b; }
    friend constexpr Vector2 operator/(Vector2 a, const Vector2& b) { return a /= b; }
    friend constexpr Vector2 operator%(Vector2 a, const Vector2& b) { return a %= b; }

    friend constexpr Vector2 operator+(Vector2 a, T c) { return a += c; }
    friend constexpr Vector2 operator-(Vector2 a, T c) { return a -= c; }
    friend constexpr Vector2 operator*(Vector2 a, T c) { return a *= c; }
    friend constexpr Vector2 operator*(T c, Vector2 a) { return a *= c; }
    friend constexpr Vector2 operator/(Vector2 a, T c) { return a /= c; }
    friend constexpr Vector2 operator%(Vector2 a, T c) { return a %= c; }

  public: // unary
    constexpr Vector2 operator-() const { return {static_cast<T>(-x), static_cast<T>(-y)}; }

  public: // comparison
    friend constexpr bool operator==(const Vector2& a, const Vector2& b) { return a.x == b.x && a.y == b.y; }
    friend constexpr bool operator!=(const Vector2& a, const Vector2& b) { return !(a == b); }
    friend constexpr bool operator<(const Vector2& a, const Vector2& b) { return a.y != b.y ? a.y < b.y : a.x < b.x; }

  public: // fmt
    friend std::ostream& operator<<(std::ostream& s, const Vector2& v) { return s << '(' << v.x << ", " << v.y << ')'; }
};

using Vector2i = Vector2<int>;
using Vector2u = Vector2<std::size_t>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;
using Vector2c = Vector2<char>;

} // namespace aoc

// define hash for vectors
template <aoc::Arithmetic T> struct std::hash<aoc::Vector2<T>> {
    std::size_t operator()(const aoc::Vector2<T>& v) const noexcept {
        std::size_t h1 = std::hash<T>{}(v.x);
        std::size_t h2 = std::hash<T>{}(v.y);
        // bit mix, fractional parts of phi :)
        return h1 ^ (h2 + 0x9e3779b97f4a7c15ULL + (h1 << 6) + (h1 >> 2));
    }
};
