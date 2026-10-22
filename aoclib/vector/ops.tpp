#include "vec.h"

namespace aoc {

template <typename T, typename Alloc>
vec<T, Alloc> vec<T, Alloc>::operator()(std::optional<std::ptrdiff_t> start, std::optional<std::ptrdiff_t> stop,
                                        std::ptrdiff_t step) const {
    return slice(*this, start, stop, step);
}

template <typename T, typename Alloc>
auto vec<T, Alloc>::operator[](std::ptrdiff_t i) -> typename base::reference {
    return base::operator[](wrap_index(i, this->size()));
}

template <typename T, typename Alloc>
auto vec<T, Alloc>::operator[](std::ptrdiff_t i) const -> typename base::const_reference {
    return base::operator[](wrap_index(i, this->size()));
}

template <typename T, typename Alloc>
template <typename Iterable>
    requires std::ranges::range<Iterable>
vec<T, Alloc>& vec<T, Alloc>::operator+=(const Iterable& iter) {
    return extend(iter);
}

template <typename T, typename Alloc>
template <typename Iterable>
    requires std::ranges::range<Iterable>
vec<T, Alloc> vec<T, Alloc>::operator+(const Iterable& iter) const {
    vec cpy = *this;
    cpy.extend(iter);
    return cpy;
}

template <typename T, typename Alloc> std::ostream& operator<<(std::ostream& stream, const vec<T, Alloc>& v) {
    stream << '[';
    const char* sep = "";
    for (const auto& i : v) {
        stream << std::exchange(sep, ", ");
        print_one(stream, i);
    }
    return stream << ']';
}

} // namespace aoc
