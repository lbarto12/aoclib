#include "Counter.h"

namespace aoc {

template <Hashable K> Counter<K>& Counter<K>::operator+=(const Counter& other) {
    return update(other).drop_nonpositive();
}

template <Hashable K> Counter<K>& Counter<K>::operator-=(const Counter& other) {
    return subtract(other).drop_nonpositive();
}

template <Hashable K> Counter<K>& Counter<K>::operator|=(const Counter& other) {
    for (const auto& [k, n] : other) {
        count_type& mine = (*this)[k];
        mine = std::max(mine, n);
    }
    return drop_nonpositive();
}

template <Hashable K> Counter<K>& Counter<K>::operator&=(const Counter& other) {
    for (auto& [k, n] : *this) n = std::min(n, other.get(k));
    return drop_nonpositive();
}

template <Hashable K> Counter<K> Counter<K>::operator+(const Counter& other) const {
    Counter cpy = *this;
    return cpy += other;
}

template <Hashable K> Counter<K> Counter<K>::operator-(const Counter& other) const {
    Counter cpy = *this;
    return cpy -= other;
}

template <Hashable K> Counter<K> Counter<K>::operator|(const Counter& other) const {
    Counter cpy = *this;
    return cpy |= other;
}

template <Hashable K> Counter<K> Counter<K>::operator&(const Counter& other) const {
    Counter cpy = *this;
    return cpy &= other;
}

} // namespace aoc
