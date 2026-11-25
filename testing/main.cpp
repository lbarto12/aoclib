#include <aoclib/lib.h>

#include <unordered_set>

using namespace aoc;

int main() {
    dict<str, int> d = {{"hello", 1}, {"world", 2}};

    std::unordered_set<vec2<int>> set;

    auto x = set.insert({10, 10});

    println(set.contains({10, 2}));
}
