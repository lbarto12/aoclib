#include "vec.h"

namespace aoc {

template <typename T, typename Alloc> vec<T, Alloc>& vec<T, Alloc>::reverse() {
    std::reverse(this->begin(), this->end());
    return *this;
}

template <typename T, typename Alloc> vec<T, Alloc> vec<T, Alloc>::reversed() const {
    vec cpy = *this;
    cpy.reverse();
    return cpy;
}

template <typename T, typename Alloc>
template <typename Iterable>
    requires RangeOf<Iterable, T>
vec<T, Alloc>& vec<T, Alloc>::extend(const Iterable& iter) {
    // v.extend(v): appending would invalidate the iterators we're reading from, so extend from a copy
    if constexpr (std::derived_from<Iterable, base>) {
        if (static_cast<const base*>(&iter) == static_cast<const base*>(this)) return extend(base(iter));
    }
    if constexpr (std::ranges::sized_range<const Iterable>) this->reserve(this->size() + std::size(iter));
    for (const auto& i : iter) this->emplace_back(i);
    return *this;
}

template <typename T, typename Alloc> T vec<T, Alloc>::pop(std::ptrdiff_t index) {
    if (this->empty()) throw IndexError("pop from empty vec");
    const std::size_t i = wrap_index(index, this->size());
    T out = std::move(base::operator[](i));
    this->erase(this->begin() + static_cast<std::ptrdiff_t>(i));
    return out;
}

} // namespace aoc
