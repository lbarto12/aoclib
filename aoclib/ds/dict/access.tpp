#include "dict.h"

namespace aoc {

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
V dict<K, V, Hash, KeyEqual, Alloc>::get(const K& key, const V& fallback) const {
    auto it = this->find(key);
    return it == this->end() ? fallback : it->second;
}

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
V& dict<K, V, Hash, KeyEqual, Alloc>::setdefault(const K& key, const V& fallback) {
    return this->try_emplace(key, fallback).first->second;
}

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
V dict<K, V, Hash, KeyEqual, Alloc>::pop(const K& key) {
    auto it = this->find(key);
    if (it == this->end()) throw KeyError("pop of missing key");
    V out = std::move(it->second);
    this->erase(it);
    return out;
}

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
V dict<K, V, Hash, KeyEqual, Alloc>::pop(const K& key, const V& fallback) {
    auto it = this->find(key);
    if (it == this->end()) return fallback;
    V out = std::move(it->second);
    this->erase(it);
    return out;
}

} // namespace aoc
