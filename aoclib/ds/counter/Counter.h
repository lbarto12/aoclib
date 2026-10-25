#pragma once

#include <algorithm>
#include <cstddef>
#include <unordered_map>
#include <utility>

#include "../../concepts.h"
#include "../dict/dict.h"
#include "../vector/vec.h"

namespace aoc {

// python's collections.Counter: a dict of element -> count. counts can go negative through subtract
template <Hashable K> class Counter : public dict<K, long long> {
    using base = dict<K, long long>;

  public: // b5
    using count_type = long long;

    using base::base;
    using base::operator=;

    Counter() = default;

    // count every element: Counter<char>(str("aab")) == {a: 2, b: 1}
    template <typename Iterable>
        requires RangeOf<Iterable, K>
    explicit Counter(const Iterable& iter);

  public: // counting
    // add one for every element: c.update(line.split())
    template <typename Iterable>
        requires RangeOf<Iterable, K>
    Counter& update(const Iterable& iter);

    // add every count from `other`
    Counter& update(const Counter& other);

    // subtract one for every element, keeping zero and negative counts like python
    template <typename Iterable>
        requires RangeOf<Iterable, K>
    Counter& subtract(const Iterable& iter);

    // subtract every count from `other`, keeping zero and negative counts like python
    Counter& subtract(const Counter& other);

  public: // queries
    // sum of all counts
    count_type total() const;

    // pairs sorted by count, highest first, ties in iteration order. n < 0 returns all of them
    vec<std::pair<K, count_type>> most_common(std::ptrdiff_t n = -1) const;

    // each element repeated by its count, skipping counts below one
    vec<K> elements() const;

  public: // multiset operators, like python they drop counts below one
    Counter& operator+=(const Counter& other);
    Counter& operator-=(const Counter& other);

    // max of each count
    Counter& operator|=(const Counter& other);

    // min of each count
    Counter& operator&=(const Counter& other);

    Counter operator+(const Counter& other) const;
    Counter operator-(const Counter& other) const;
    Counter operator|(const Counter& other) const;
    Counter operator&(const Counter& other) const;

  private:
    // remove every count below one
    Counter& drop_nonpositive();
};

} // namespace aoc

// templated includes
#include "count.tpp"
#include "ops.tpp"
#include "query.tpp"
