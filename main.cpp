#include <iostream>

#include "aoclib/debug.h"
#include "aoclib/ds/Matrix.h"
#include "aoclib/ds/Vector2.h"
#include "aoclib/ds/strings/str.h"
#include "aoclib/ds/vector/vec.h"
#include "aoclib/files/File.h"
#include "aoclib/timing.h"

#include <unordered_set>

using namespace aoc;

int main() {
    vec<str> lines = File("input.txt").readlines();
    std::size_t split = lines.index("");
    vec<Vector2u> ranges = map(lines({}, split), [](const str& s) -> Vector2u {
        const auto& [a, b] = s.split("-").unpack<2, std::size_t>();
        return {a, b};
    });
    ranges.sort(&Vector2u::x);
    vec<std::size_t> ingredients = map(lines(split + 1), [](const str& s) -> std::size_t { return std::size_t(s); });

    std::size_t p1 = 0;

    for (const auto& i : ingredients) {
        p1 += any(map(ranges, [i](const Vector2u& v) -> bool {
            const auto& [l, r] = v;
            return l <= i && i <= r;
        }));
    }

    std::size_t p2 = 0;
    auto& [left, right] = ranges[0];

    for (const auto& [l, r] : ranges(1)) {
        if (l <= right)
            right = std::max(r, right);
        else {
            p2 += right - left + 1;
            left = l, right = r;
        }
    }

    p2 += right - left + 1;

    std::cout << "part 1: " << p1 << std::endl;
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
