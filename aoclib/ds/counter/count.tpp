#include "Counter.h"

namespace aoc {

template <Hashable K>
template <typename Iterable>
    requires RangeOf<Iterable, K>
Counter<K>::Counter(const Iterable& iter) {
    update(iter);
}

template <Hashable K>
template <typename Iterable>
    requires RangeOf<Iterable, K>
Counter<K>& Counter<K>::update(const Iterable& iter) {
    for (const auto& i : iter) ++(*this)[K(i)];
    return *this;
}

template <Hashable K> Counter<K>& Counter<K>::update(const Counter& other) {
    for (const auto& [k, n] : other) (*this)[k] += n;
    return *this;
}

template <Hashable K>
template <typename Iterable>
    requires RangeOf<Iterable, K>
Counter<K>& Counter<K>::subtract(const Iterable& iter) {
    for (const auto& i : iter) --(*this)[K(i)];
    return *this;
}

template <Hashable K> Counter<K>& Counter<K>::subtract(const Counter& other) {
    for (const auto& [k, n] : other) (*this)[k] -= n;
    return *this;
}

template <Hashable K> Counter<K>& Counter<K>::drop_nonpositive() {
    std::erase_if(*this, [](const auto& kv) -> bool { return kv.second < 1; });
    return *this;
}

} // namespace aoc
