#include <iostream>

#include "../../aoclib/debug.h"
#include "../../aoclib/ds/Matrix.h"
#include "../../aoclib/ds/Vector2.h"
#include "../../aoclib/files/File.h"
#include "../../aoclib/strings/str.h"
#include "../../aoclib/timing.h"
#include "../../aoclib/vector/vec.h"

#include <unordered_set>

#include <thread>

using namespace aoc;

int main() {
    vec<str> input = File("input.txt").read().split(",");

    vec<Vector2u> ranges;
    for (const str& s : input) {
        vec<str> r = s.split("-");
        ranges.push_back({std::size_t(r[0]), std::size_t(r[1])});
    }

    std::size_t p1 = 0, p2 = 0;

    for (const auto& [l, r] : ranges) {
        for (std::size_t i = l; i <= r; ++i) {
            str s = str(i);
            std::size_t n = s.length();
            for (std::size_t seg = n / 2; seg > 0; --seg) {
                if (mod(n, seg)) continue;

                std::unordered_set<str> check;
                for (std::size_t x = 0; x < n; x += seg) {
                    check.insert(s(x, x + seg));
                }

                if (check.size() == 1) {
                    p1 += i * (seg == n / 2 && !mod(n, std::size_t(2)));
                    p2 += i;
                    break;
                }
            }
        }
    }

    std::cout << "part 1: " << p1 << std::endl;
    std::cout << "part 2: " << p2 << std::endl;
}
