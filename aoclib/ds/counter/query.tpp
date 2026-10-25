#include "Counter.h"

namespace aoc {

template <Hashable K> auto Counter<K>::total() const -> count_type {
    count_type sum = 0;
    for (const auto& [k, n] : *this) sum += n;
    return sum;
}

template <Hashable K> auto Counter<K>::most_common(std::ptrdiff_t n) const -> vec<std::pair<K, count_type>> {
    vec<std::pair<K, count_type>> out = this->items();
    out.sort([](const std::pair<K, count_type>& kv) -> count_type { return kv.second; }, true);
    if (n >= 0 && static_cast<std::size_t>(n) < out.size()) out.resize(static_cast<std::size_t>(n));
    return out;
}

template <Hashable K> vec<K> Counter<K>::elements() const {
    vec<K> out;
    for (const auto& [k, n] : *this) {
        for (count_type i = 0; i < n; ++i) out.push_back(k);
    }
    return out;
}

} // namespace aoc
