#pragma once

#include "Vector2.h"
#include "errors.h"
#include <iostream>
#include <vector>

namespace aoc {

// Represents a matrix
// Offers some basic matrix methods
template <typename T> struct Matrix2D {
    using Row = std::vector<T>;
    using Grid = std::vector<Row>;

    Matrix2D() = default;
    Matrix2D(std::initializer_list<Row> init) : mtx(init) {}
    Matrix2D(Grid init) : mtx(std::move(init)) {}

    // Correctness assertions for matricies
    struct Assert {
        static bool NotEmpty(const std::vector<std::vector<T>>& mtx) { return mtx.size() && mtx[0].size(); }

        static bool CanTranspose(const std::vector<std::vector<T>>& mtx) {
            const size_t mustbe = mtx[0].size();
            for (const auto& row : mtx) {
                if (row.size() != mustbe) return false;
            }
            return true;
        }
    };

    // transposes a matrix.
    // in this particular function, for vectors.
    // asserts the correctness of the vector
    Matrix2D<T> transpose() const {
        if (!Assert::NotEmpty()) throw new EmptyMatrixError();
        if (!Assert::CanTranspose()) throw new InvalidMatrixError("matrix is not transposable");

        // create a transposed, empty matrix from the input
        auto res = std::vector<std::vector<T>>(mtx[0].size(), std::vector<T>(mtx.size(), T{}));

        for (size_t i = 0; i < mtx.size(); ++i) {
            for (size_t j = 0; j < mtx[0].size(); ++j) {
                res[j][i] = mtx[i][j];
            }
        }
        return Matrix2D<T>(res);
    }

    // Allows use of std::cout << matrix << std::endl;
    friend std::ostream& operator<<(std::ostream& s, const Matrix2D<T>& matrix) {

        for (const auto& row : matrix.mtx) {
            s << "| ";
            for (const auto& cell : row) s << cell << " ";
            s << "|\n";
        }

        return s;
    }

  public: // iterators
    std::vector<std::vector<T>>::iterator begin() { return mtx.begin(); }

    std::vector<std::vector<T>>::iterator end() { return mtx.end(); }

    std::vector<std::vector<T>>::const_iterator begin() const { return mtx.begin(); }

    std::vector<std::vector<T>>::const_iterator end() const { return mtx.end(); }

  public: // accessors
    std::vector<T>& operator[](size_t index) { return mtx[index]; }

    const std::vector<T>& operator[](size_t index) const { return mtx[index]; }

    T& at(const Vector2i& pos) { return mtx[pos.y][pos.x]; }
    const T& at(const Vector2i& pos) const { return mtx[pos.y][pos.x]; }

  private:
    std::vector<std::vector<T>> mtx;
};

} // namespace aoc
