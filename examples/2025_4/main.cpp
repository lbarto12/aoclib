
#include <iostream>

#include "../../aoclib/debug.h"
#include "../../aoclib/ds/Matrix.h"
#include "../../aoclib/ds/Vector2.h"
#include "../../aoclib/files/File.h"
#include "../../aoclib/strings/str.h"
#include "../../aoclib/timing.h"
#include "../../aoclib/vector/vec.h"

#include <unordered_set>

using namespace aoc;

std::tuple<std::size_t, std::unordered_set<Vector2i>> forklift(const vec<vec<char>>& floor) {
    int w = floor[0].size(), h = floor.size();
    std::unordered_set<Vector2i> valid;
    std::size_t result = 0;
    for (const auto& [y, line] : enumerate(floor)) {
        for (const auto& [x, c] : enumerate(line)) {
            std::size_t adj = sum(map(Vector2i(x, y).adjacent8(), [w, h, &floor](const Vector2i& pos) -> int {
                const auto& [cx, cy] = pos;
                return int(0 <= cx && cx < w && 0 <= cy && cy < h && floor[cy][cx] == '@');
            }));
            if (c == '@' && adj < 4) {
                ++result;
                valid.insert({x, y});
            }
        }
    }
    return {result, valid};
}

int main() {
    vec<vec<char>> room =
        map(File("input.txt").readlines(), [](const str& line) -> vec<char> { return vec<char>(line.strip()); });

    const auto& [p1, _] = forklift(room);

    std::size_t p2 = 0;
    while (true) {
        const auto& [count, remove] = forklift(room);
        if (remove.empty()) break;

        p2 += count;

        for (const auto& [x, y] : remove) {
            room[y][x] = '.';
        }
    }

    std::cout << "part 1: " << p1 << std::endl;
    std::cout << "part 2: " << p2 << std::endl;
}
