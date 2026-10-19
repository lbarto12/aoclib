#include <iostream>

#include "aoclib/Matrix.h"
#include "aoclib/Vector2.h"
#include "aoclib/timing.h"

#include <thread>

using namespace aoc;

void longfunc(int x) { std::this_thread::sleep_for(std::chrono::seconds(x)); }

int main() {
    Matrix2D<int> mtx = {{1, 2, 3}, {4, 5, 6}};

    std::cout << mtx << std::endl;

    auto t = mtx.transpose();

    for (const auto& x : t) {
        std::cout << x[0] << std::endl;
    }

    std::cout << t << std::endl;

    Vector2i v = {0, 0};

    for (const auto x : v.adjacent()) {
        std::cout << x << std::endl;
    }

    std::cout << Timed(longfunc, 10) << std::endl;
}
