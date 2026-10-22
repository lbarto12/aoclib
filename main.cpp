#include <iostream>

#include "aoclib/debug.h"
#include "aoclib/ds/Matrix.h"
#include "aoclib/ds/Vector2.h"
#include "aoclib/files/File.h"
#include "aoclib/strings/str.h"
#include "aoclib/timing.h"
#include "aoclib/vector/vec.h"

#include <unordered_set>

using namespace aoc;

int main() {
    vec<int> x = {1, 2, 3};

    vec<int> y = (x + vec<int>{4, 5, 6}).reversed();

    std::cout << y << std::endl;
    std::cout << x << std::endl;
}

// void longfunc(int x) { std::this_thread::sleep_for(std::chrono::seconds(x)); }

// int main() {
//     Matrix2D<int> mtx = {{1, 2, 3}, {4, 5, 6}};
//
//     std::cout << mtx << std::endl;
//
//     auto t = mtx.transpose();
//
//     for (const auto& x : t) {
//         std::cout << x[0] << std::endl;
//     }
//
//     std::cout << t << std::endl;
//
//     Vector2i v = {0, 0};
//
//     for (const auto x : v.adjacent8()) {
//         std::cout << x << std::endl;
//     }
//
//     std::cout << Timed(longfunc, 10) << std::endl;
// }
