#include "dict.h"

namespace aoc {

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
dict<K, V, Hash, KeyEqual, Alloc>& dict<K, V, Hash, KeyEqual, Alloc>::update(const base& other) {
    for (const auto& [k, v] : other) this->insert_or_assign(k, v);
    return *this;
}

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
dict<K, V, Hash, KeyEqual, Alloc> dict<K, V, Hash, KeyEqual, Alloc>::operator|(const base& other) const {
    dict cpy = *this;
    cpy.update(other);
    return cpy;
}

template <typename K, typename V, typename Hash, typename KeyEqual, typename Alloc>
dict<K, V, Hash, KeyEqual, Alloc>& dict<K, V, Hash, KeyEqual, Alloc>::operator|=(const base& other) {
    return update(other);
}

template <Printable K, Printable V, typename Hash, typename KeyEqual, typename Alloc>
std::ostream& operator<<(std::ostream& stream, const dict<K, V, Hash, KeyEqual, Alloc>& d) {
    stream << '{';
    const char* sep = "";
    for (const auto& [k, v] : d) {
        stream << std::exchange(sep, ", ");
        print_one(stream, k);
        stream << ": ";
        print_one(stream, v);
    }
    return stream << '}';
}

} // namespace aoc
