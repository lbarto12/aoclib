#pragma once

#include <concepts>
#include <iostream>

#include "../concepts.h"
#include "../errors.h"
#include "../generic.h"
#include "Vector2.h"
#include "vector/vec.h"

namespace aoc {

// Represents a matrix
// Offers some basic matrix methods
template <typename T> struct Matrix2D {
    using Row = vec<T>;
    using Grid = vec<Row>;

    Matrix2D() = default;
    Matrix2D(std::initializer_list<Row> init) : mtx(init) {}
    Matrix2D(Grid init) : mtx(std::move(init)) {}

    // Correctness assertions for matricies
    struct Assert {
        static bool NotEmpty(const vec<vec<T>>& mtx) { return mtx.size() && mtx[0].size(); }

        static bool CanTranspose(const vec<vec<T>>& mtx) {
            const size_t mustbe = mtx[0].size();
            for (const auto& row : mtx) {
                if (row.size() != mustbe) return false;
            }
            return true;
        }
    };

    // transposes a matrix. rows may be ragged, see aoc::transpose
    // throws if the matrix is empty
    Matrix2D<T> transpose() const
        requires std::copyable<T>
    {
        if (!Assert::NotEmpty(mtx)) throw EmptyMatrixError();
        return Matrix2D<T>(aoc::transpose(mtx));
    }

    // Allows use of std::cout << matrix << std::endl;
    friend std::ostream& operator<<(std::ostream& s, const Matrix2D<T>& matrix)
        requires Streamable<T>
    {

        for (const auto& row : matrix.mtx) {
            s << "| ";
            for (const auto& cell : row) s << cell << " ";
            s << "|\n";
        }

        return s;
    }

  public: // iterators
    vec<vec<T>>::iterator begin() { return mtx.begin(); }

    vec<vec<T>>::iterator end() { return mtx.end(); }

    vec<vec<T>>::const_iterator begin() const { return mtx.begin(); }

    vec<vec<T>>::const_iterator end() const { return mtx.end(); }

  public: // accessors
    vec<T>& operator[](size_t index) { return mtx[index]; }

    const vec<T>& operator[](size_t index) const { return mtx[index]; }

    T& at(const Vector2i& pos) { return mtx[pos.y][pos.x]; }
    const T& at(const Vector2i& pos) const { return mtx[pos.y][pos.x]; }

  private:
    vec<vec<T>> mtx;
};

} // namespace aoc
