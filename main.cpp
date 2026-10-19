#include <iostream>

#include "aoclib/Matrix.h"
#include "aoclib/Vector2.h"

using namespace aoc;

int main() {
    Matrix2D<int> mtx = {{1, 2, 3}, {4, 5, 6}};

    std::cout << mtx << std::endl;

    auto t = mtx.transpose();

    for (const auto x : t) {
        std::cout << x[0] << std::endl;
    }

    std::cout << t << std::endl;

    Vector2i v = {0, 0};

    for (const auto x : v.adjacent()) {
        std::cout << x << std::endl;
    }
}
