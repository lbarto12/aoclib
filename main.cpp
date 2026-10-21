#include <iostream>

#include "aoclib/debug.h"
#include "aoclib/ds/Matrix.h"
#include "aoclib/ds/Vector2.h"
#include "aoclib/files/File.h"
#include "aoclib/strings/str.h"
#include "aoclib/timing.h"
#include "aoclib/vector/vec.h"

#include <thread>

using namespace aoc;

int main() {
    // vec<str> input = File("input.txt").read().split(",");
    //
    // vec<Vector2u> ranges;
    // for (const str& s : input) {
    //     vec<str> r = s.split("-");
    //     ranges.push_back({std::size_t(r[0]), std::size_t(r[1])});
    // }
    //
    // std::size_t p1 = 0, p2 = 0;
    //
    // for (const auto& [l, r] : ranges) {
    //     for (std::size_t i = l; i <= r; ++i) {
    //         std::size_t n = floordiv(str(i).length(), std::size_t(2));
    //         for (std::size_t seg = n; n >= 0; --seg) {
    //
    //             if (!mod(n, seg) &&) }
    //     }
    // }
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
