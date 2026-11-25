#include <aoclib/lib.h>

using namespace aoc;

int main() {
    dict<str, int> d = {{"hello", 1}, {"world", 2}};

    vec<int> x = {1, 2};
    const auto& [a, b] = x.unpack<2, int>();

    println(a, b);
}
