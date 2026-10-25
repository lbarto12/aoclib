#include <aoclib/lib.h>

using namespace aoc;

int main() {
    vec<str> lines = File("input.txt").readlines();
    vec<str> x = {"1", "2", "3"};
    vec<int> asints = map(x, [&](const str& s) -> int { return int(s); });

    println(asints);
}
