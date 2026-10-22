#include "vec.h"

namespace aoc {

template <typename T, typename Alloc>
std::size_t vec<T, Alloc>::count(const T& elem) const
    requires std::equality_comparable<T>
{
    std::size_t i = 0;
    for (const T& e : *this) {
        if (e == elem) ++i;
    }
    return i;
}

template <typename T, typename Alloc>
std::size_t vec<T, Alloc>::index(const T& elem) const
    requires std::equality_comparable<T>
{
    for (std::size_t i = 0; i < this->size(); ++i) {
        if ((*this)[i] == elem) return i;
    }
    throw std::invalid_argument("element was not found");
}

} // namespace aoc
