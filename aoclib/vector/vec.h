#pragma once

#include <initializer_list>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

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
};

} // namespace aoc
