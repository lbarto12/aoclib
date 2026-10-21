#include <iostream>

#include "aoclib/debug.h"
#include "aoclib/ds/Matrix.h"
#include "aoclib/ds/Vector2.h"
#include "aoclib/files/File.h"
#include "aoclib/strings/str.h"
#include "aoclib/timing.h"
#include "aoclib/vector/vec.h"

#include <unordered_set>

#include <thread>

using namespace aoc;

int main() {
    vec<std::tuple<char, int>> instructions =
        map(File("input.txt").readlines(), [](const str& line) -> std::tuple<char, int> {
            str ln = line.strip();
            return {ln[0], int(ln(1))};
        });

    int pos = 50;
    int p1 = 0;

    for (auto& [dir, off] : instructions) {
        pos = mod(pos + (dir == 'R' ? off : -off), 100);
        p1 += pos == 0;
    }

    std::cout << "part 1: " << p1 << std::endl;

    // part 2
    pos = 50;
    int p2 = 0;

    for (auto& [dir, off] : instructions) {
        for (int i = 0; i < off; ++i) {
            pos = mod(pos + (dir == 'R' ? 1 : -1), 100);
            p2 += pos == 0;
        }
    }

    std::cout << "part 2: " << p2 << std::endl;
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
