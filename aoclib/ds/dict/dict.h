#pragma once

#include <concepts>
#include <functional>
#include <initializer_list>
#include <memory>
#include <ostream>
#include <unordered_map>
#include <utility>

#include "../../concepts.h"
#include "../../debug.h"
#include "../../errors.h"
#include "../vector/vec.h"

namespace aoc {

template <typename K, typename V, typename Hash = std::hash<K>, typename KeyEqual = std::equal_to<K>,
          typename Alloc = std::allocator<std::pair<const K, V>>>
class dict : public std::unordered_map<K, V, Hash, KeyEqual, Alloc> {
    using base = std::unordered_map<K, V, Hash, KeyEqual, Alloc>;

  public: // b5
    using base::base;
    using base::operator=;

    dict() = default;
    dict(const base& m) : base(m) {}
    dict(base&& m) noexcept : base(std::move(m)) {}

    dict(std::initializer_list<typename base::value_type> init) : base(init) {}

  public: // access
    // value for `key`, or `fallback` if missing. never inserts: d.get("a", 0)
    V get(const K& key, const V& fallback = V{}) const;

    // value for `key`, inserting `fallback` first if missing: d.setdefault(k, {}).push_back(x)
    V& setdefault(const K& key, const V& fallback = V{});

    // remove `key` and return its value. throws KeyError if missing
    V pop(const K& key);

    // remove `key` and return its value, or `fallback` if missing
    V pop(const K& key, const V& fallback);

  public: // views, copied out so they can be sorted and unpacked
    vec<K> keys() const;
    vec<V> values() const;

    // for (auto [k, v] : d.items())
    vec<std::pair<K, V>> items() const;

  public: // merging, later values win like python
    // add every pair from `other`, overwriting existing keys
    dict& update(const base& other);

    // python 3.9 merge, returns a new dict: a | b
    dict operator|(const base& other) const;

    // python 3.9 in-place merge: a |= b
    dict& operator|=(const base& other);
};

// print like python: {a: 1, b: 2}
template <Printable K, Printable V, typename Hash, typename KeyEqual, typename Alloc>
std::ostream& operator<<(std::ostream& stream, const dict<K, V, Hash, KeyEqual, Alloc>& d);

} // namespace aoc

// templated includes
#include "access.tpp"
#include "merge.tpp"
#include "views.tpp"
