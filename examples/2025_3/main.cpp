
#include <iostream>

#include "../../aoclib/debug.h"
#include "../../aoclib/ds/Matrix.h"
#include "../../aoclib/ds/Vector2.h"
#include "../../aoclib/files/File.h"
#include "../../aoclib/strings/str.h"
#include "../../aoclib/timing.h"
#include "../../aoclib/vector/vec.h"

using namespace aoc;

std::tuple<str, std::size_t> maxAndLocation(const str& s) {
    str mx = "-1";
    int mi = -1;

    for (const auto& [i, c] : enumerate(s)) {
        if (int(str(c)) > int(mx)) {
            mx = str(c);
            mi = i;
        }
    }

    return {mx, mi};
}

int main() {
    vec<str> lines = File("input.txt").readlines();

    std::size_t j1 = 0, j2 = 0;

    for (const str& line : lines) {
        const auto& [first, f_idx] = maxAndLocation(line({}, -1));
        const auto& [second, _] = maxAndLocation(line(f_idx + 1));
        j1 += std::size_t(first + second);

        str constructed;
        std::size_t boundary = 0;
        for (int i = -11; i <= 0; ++i) {
            const auto& [nxt, idx] = maxAndLocation(i ? line(boundary, i) : line(boundary));
            boundary += idx + 1;
            constructed += nxt;
        }
        j2 += std::size_t(constructed);
    }

    std::cout << "part 1: " << j1 << std::endl;
    std::cout << "part 2: " << j2 << std::endl;
}
