#pragma once

#include <algorithm>
#include <array>
#include <concepts>
#include <functional>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <optional>
#include <ostream>
#include <ranges>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "../concepts.h"
#include "../debug.h"
#include "../errors.h"
#include "../index.h"
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
    template <std::input_iterator It> vec(It first, It last) : base(first, last) {}

    // split a string into its chars: vec<char>(str("abc")) == {'a', 'b', 'c'}
    explicit vec(const std::string& s)
        requires std::same_as<T, char>
        : base(s.begin(), s.end()) {}

  public: // methods
    // inline reverse
    vec& reverse();

    // copy reverse
    vec reversed() const;

    // inline stable sort, like python: v.sort(), v.sort(key), v.sort({}, true) for descending
    // key maps each element to the value it's compared by: v.sort([](const Vector2u& p) { return p.x; })
    template <typename Key = std::identity>
    vec& sort(Key key = {}, bool reverse = false)
        requires std::sortable<typename base::iterator, std::ranges::less, Key>;

    // copy sort, same arguments as sort
    template <typename Key = std::identity>
    vec sorted(Key key = {}, bool reverse = false) const
        requires std::sortable<typename base::iterator, std::ranges::less, Key>;

    // count the number of elements that match `elem`
    std::size_t count(const T& elem) const
        requires std::equality_comparable<T>;

    // add iterable's elements to this one
    template <typename Iterable>
        requires RangeOf<Iterable, T>
    vec& extend(const Iterable& iter);

    // get the index of an element, throws if not in array
    std::size_t index(const T& elem) const
        requires std::equality_comparable<T>;

    // remove and return the element at `index`, negative indices wrap. v.pop() removes the last element
    T pop(std::ptrdiff_t index = -1);

  public: // unpacking, for structured bindings. throws ValueError if size() doesn't match, like python
    // all N elements, converted to U: auto [a, b] = s.split("-").unpack<2, std::size_t>();
    template <std::size_t N, typename U = T>
        requires std::constructible_from<U, const T&>
    std::array<U, N> unpack() const;

    // one element per type: auto [name, n] = line.split(" ").unpack<str, int>();
    template <typename... Us>
        requires(sizeof...(Us) > 0) && (std::constructible_from<Us, const T&> && ...)
    std::tuple<Us...> unpack() const;

  public: // operators
    // slice operator, like python: v(1, -1) == v[1:-1], v({}, {}, 2) == v[::2]
    vec operator()(std::optional<std::ptrdiff_t> start = std::nullopt,
                   std::optional<std::ptrdiff_t> stop = std::nullopt, std::ptrdiff_t step = 1) const;

    // index operator, like python: negative indices wrap, v[-1] == last element. throws IndexError if out of range
    typename base::reference operator[](std::ptrdiff_t i);
    typename base::const_reference operator[](std::ptrdiff_t i) const;

    // python append
    template <typename Iterable>
        requires RangeOf<Iterable, T>
    vec& operator+=(const Iterable& iter);

    // python concatenation, returns a new vec
    template <typename Iterable>
        requires RangeOf<Iterable, T>
    vec operator+(const Iterable& iter) const;
};

// print like python: [1, 2, 3]
template <Printable T, typename Alloc> std::ostream& operator<<(std::ostream& stream, const vec<T, Alloc>& v);

} // namespace aoc

// templated includes
#include "modify.tpp"
#include "ops.tpp"
#include "search.tpp"
#include "unpack.tpp"
