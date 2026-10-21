#pragma once

#include <initializer_list>
#include <iterator>
#include <memory>
#include <optional>
#include <ostream>
#include <utility>
#include <vector>

#include "../debug.h"
#include "../slice.h"

namespace aoc {

template <typename T, typename Alloc = std::allocator<T>> class vec : public std::vector<T, Alloc> {
    using base = std::vector<T, Alloc>;

  public: // b5
    using base::base;
    using base::operator=;

    vec() = default;
    vec(const base& v) : base(v) {}
    vec(base&& v) noexcept : base(std::move(v)) {}

    vec(std::initializer_list<T> init) : base(init) {}
    template <typename It> vec(It first, It last) : base(first, last) {}

  public: // operators
    // slice operator, like python: v(1, -1) == v[1:-1], v({}, {}, 2) == v[::2]
    vec operator()(std::optional<std::ptrdiff_t> start = std::nullopt,
                   std::optional<std::ptrdiff_t> stop = std::nullopt, std::ptrdiff_t step = 1) const {
        return slice(*this, start, stop, step);
    }

    // print like python: [1, 2, 3]
    friend std::ostream& operator<<(std::ostream& stream, const vec& v) {
        stream << '[';
        const char* sep = "";
        for (const auto& i : v) {
            stream << std::exchange(sep, ", ");
            print_one(stream, i);
        }
        return stream << ']';
    }
};

} // namespace aoc
