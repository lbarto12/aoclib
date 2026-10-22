#include "vec.h"

namespace aoc {

// python's "too many / not enough values to unpack"
inline void check_unpack_size(std::size_t have, std::size_t want) {
    if (have != want)
        throw ValueError("cannot unpack " + std::to_string(have) + " values into " + std::to_string(want));
}

template <typename T, typename Alloc>
template <std::size_t N, typename U>
    requires std::constructible_from<U, const T&>
std::array<U, N> vec<T, Alloc>::unpack() const {
    check_unpack_size(this->size(), N);
    const base& self = *this; // plain std::vector indexing; size is already checked
    return [&self]<std::size_t... I>(std::index_sequence<I...>) {
        return std::array<U, N>{U(self[I])...};
    }(std::make_index_sequence<N>{});
}

template <typename T, typename Alloc>
template <typename... Us>
    requires(sizeof...(Us) > 0) && (std::constructible_from<Us, const T&> && ...)
std::tuple<Us...> vec<T, Alloc>::unpack() const {
    check_unpack_size(this->size(), sizeof...(Us));
    const base& self = *this; // plain std::vector indexing; size is already checked
    return [&self]<std::size_t... I>(std::index_sequence<I...>) {
        return std::tuple<Us...>{Us(self[I])...};
    }(std::index_sequence_for<Us...>{});
}

} // namespace aoc
