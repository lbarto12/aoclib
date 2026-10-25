#include "dict.h"

namespace aoc {

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
vec<K> dict<K, V, Hash, KeyEqual, Alloc>::keys() const {
    vec<K> out;
    out.reserve(this->size());
    for (const auto& [k, v] : *this) out.push_back(k);
    return out;
}

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
vec<V> dict<K, V, Hash, KeyEqual, Alloc>::values() const {
    vec<V> out;
    out.reserve(this->size());
    for (const auto& [k, v] : *this) out.push_back(v);
    return out;
}

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
vec<std::pair<K, V>> dict<K, V, Hash, KeyEqual, Alloc>::items() const {
    return vec<std::pair<K, V>>(this->begin(), this->end());
}

} // namespace aoc
