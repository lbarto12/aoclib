#include <iostream>

#include "aoclib/debug.h"
#include "aoclib/ds/Matrix.h"
#include "aoclib/ds/Vector2.h"
#include "aoclib/files/File.h"
#include "aoclib/strings/str.h"
#include "aoclib/timing.h"

#include <thread>

using namespace aoc;

int main() {
    File file = "input.txt";
    std::vector<std::tuple<char, int>> instructions;
    for (const auto& line : file.readlines()) {
        str ln = line.strip();
        instructions.push_back({ln[0], int(ln(1))});
    }

    for (auto [i, inst] : enumerate(instructions)) {
        std::cout << i << " " << std::get<char>(inst) << std::endl;
    }

    std::cout << sum(std::vector<int>{1, 2, 3}) << std::endl;
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
