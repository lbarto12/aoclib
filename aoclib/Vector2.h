#pragma once

#include <assert.h>
#include <iostream>
#include <vector>

namespace aoc {

// Simple definition of a 2 point set.
// This is good for positions, directions, vectors, etc.
// Includes operator overloads for basic arithmetic operations (+, -, *, /, %)
template <typename T> struct Vector2 {
    Vector2(T x, T y) : x(x), y(y) {}
    Vector2() : x(x), y(y) {}
    T x, y;

  public: // methods
    // get a vector that contains
    std::vector<Vector2<T>> adjacent() const {
        std::vector<Vector2<T>> res;

        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (Vector2<T>(j, i) == *this) continue;
                res.push_back(Vector2<T>(j, i));
            }
        }

        return res;
    }

  public: // operators
    Vector2<T> operator+(const Vector2<T>& other) const { return {x + other.x, y + other.y}; }
    Vector2<T> operator+(T cnst) const { return {x + cnst, y + cnst}; }
    Vector2<T>& operator+=(const Vector2<T>& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2<T>& operator+=(T cnst) {
        x += cnst;
        y += cnst;
        return *this;
    }

    Vector2<T> operator-(const Vector2<T>& other) const { return {x - other.x, y - other.y}; }
    Vector2<T> operator-(T cnst) const { return {x - cnst, y - cnst}; }
    Vector2<T>& operator-=(const Vector2<T>& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2<T>& operator-=(T cnst) {
        x -= cnst;
        y -= cnst;
        return *this;
    }

    Vector2<T> operator/(const Vector2<T>& other) const { return {x / other.x, y / other.y}; }
    Vector2<T> operator/(T cnst) const { return {x / cnst, y / cnst}; }
    Vector2<T>& operator/=(const Vector2<T>& other) {
        x /= other.x;
        y /= other.y;
        return *this;
    }
    Vector2<T>& operator/=(T cnst) {
        x /= cnst;
        y /= cnst;
        return *this;
    }

    Vector2<T> operator*(const Vector2<T>& other) const { return {x * other.x, y * other.y}; }
    Vector2<T> operator*(T cnst) const { return {x * cnst, y * cnst}; }
    Vector2<T>& operator*=(const Vector2<T>& other) {
        x *= other.x;
        y *= other.y;
        return *this;
    }
    Vector2<T>& operator*=(T cnst) {
        x *= cnst;
        y *= cnst;
        return *this;
    }

    Vector2<T> operator%(const Vector2<T>& other) const { return {x % other.x, y % other.y}; }
    Vector2<T> operator%(T cnst) const { return {x % cnst, y % cnst}; }
    Vector2<T>& operator%=(const Vector2<T>& other) {
        x %= other.x;
        y %= other.y;
        return *this;
    }
    Vector2<T>& operator%=(T cnst) {
        x %= cnst;
        y %= cnst;
        return *this;
    }

  public:
    bool operator==(const Vector2<T>& other) const { return x == other.x && y == other.y; }
    bool operator!=(const Vector2<T>& other) const { return !(*this == other); }

  public:
    friend std::ostream& operator<<(std::ostream& s, const Vector2<T>& v) {
        return s << "(" << v.x << ", " << v.y << ")";
    }
};

typedef Vector2<int> Vector2i;
typedef Vector2<size_t> Vector2u;
typedef Vector2<float> Vector2f;
typedef Vector2<double> Vector2d;
typedef Vector2<char> Vector2c;

} // namespace aoc
