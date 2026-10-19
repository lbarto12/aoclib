#pragma once

#include <iostream>
#include <unordered_map>
#include <vector>

namespace aoc {

template <typename T> struct DisjointSetUnion {
    DisjointSetUnion(std::initializer_list<T> init) {}

    T find(T i) {
        if (parent[i] == i) return i;
        return find(parent[i]);
    }

    void join(T i, T j) {
        T a = find(i), b = find(j);
        if (a != b) {
            parent[a] = b;
            sizes[b] += sizes[a];
            sizes[a] = 0;
            --_size;
        }
    }

    size_t len(T i) const { return sizes[find(i)]; }

    size_t size() const { return _size; }

  private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, int> sizes;
    size_t _size;
};

} // namespace aoc
