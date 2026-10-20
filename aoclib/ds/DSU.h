#pragma once

#include <cstddef>
#include <initializer_list>
#include <unordered_map>
#include <utility>

namespace aoc {

template <typename T> struct DisjointSetUnion {
    DisjointSetUnion() = default;

    DisjointSetUnion(std::initializer_list<T> init) {
        for (const T& x : init) add(x);
    }

    // Adds x as a singleton set; no-op if already present.
    void add(const T& x) {
        if (parent.try_emplace(x, x).second) {
            sizes[x] = 1;
            ++_size;
        }
    }

    T find(const T& x) {
        T root = parent.at(x); // throws if x is unknown
        while (parent.at(root) != root) root = parent.at(root);
        // Path compression: point every node on the path at the root.
        T cur = x;
        while (cur != root) {
            T next = parent[cur];
            parent[cur] = root;
            cur = next;
        }
        return root;
    }

    bool join(const T& i, const T& j) {
        T a = find(i), b = find(j);
        if (a == b) return false;
        if (sizes[a] > sizes[b]) std::swap(a, b); // union by size
        parent[a] = b;
        sizes[b] += sizes[a];
        sizes.erase(a);
        --_size;
        return true;
    }

    std::size_t len(const T& x) { return sizes.at(find(x)); }

    std::size_t size() const { return _size; }

  private:
    std::unordered_map<T, T> parent;
    std::unordered_map<T, std::size_t> sizes; // only roots have entries
    std::size_t _size = 0;
};

} // namespace aoc
