#pragma once

#include <algorithm>
#include <concepts>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <optional>
#include <ostream>
#include <string>
#include <utility>
#include <vector>

#include "../debug.h"
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
    template <typename It> vec(It first, It last) : base(first, last) {}

    // split a string into its chars: vec<char>(str("abc")) == {'a', 'b', 'c'}
    explicit vec(const std::string& s)
        requires std::same_as<T, char>
        : base(s.begin(), s.end()) {}

  public: // methods
    // inline reverse
    vec& reverse() {
        std::reverse(this->begin(), this->end());
        return *this;
    }

    // copy reverse
    vec reversed() const {
        vec cpy = *this;
        cpy.reverse();
        return cpy;
    }

    // count the number of elements that match `elem`
    std::size_t count(const T& elem) const {
        std::size_t i = 0;
        for (const T& e : *this) {
            if (e == elem) ++i;
        }
        return i;
    }

    // add iterable's elements to this one
    template <typename Iterable>
        requires std::ranges::range<Iterable>
    vec& extend(const Iterable& iter) {
        // v.extend(v): appending would invalidate the iterators we're reading from, so extend from a copy
        if constexpr (std::derived_from<Iterable, base>) {
            if (static_cast<const base*>(&iter) == static_cast<const base*>(this)) return extend(base(iter));
        }
        if constexpr (requires { std::size(iter); }) this->reserve(this->size() + std::size(iter));
        for (const auto& i : iter) this->emplace_back(i);
        return *this;
    }

    // get the index of an element, throws if not in array
    std::size_t index(const T& elem) const {
        for (std::size_t i = 0; i < this->size(); ++i) {
            if ((*this)[i] == elem) return i;
        }
        throw std::invalid_argument("element was not found");
    }

    // remove and return the element at `index`, negative indices wrap. v.pop() removes the last element
    T pop(std::ptrdiff_t index = -1) {
        if (this->empty()) throw IndexError("pop from empty vec");
        const std::size_t i = wrap_index(index, this->size());
        T out = std::move(base::operator[](i));
        this->erase(this->begin() + static_cast<std::ptrdiff_t>(i));
        return out;
    }

  public: // operators
    // slice operator, like python: v(1, -1) == v[1:-1], v({}, {}, 2) == v[::2]
    vec operator()(std::optional<std::ptrdiff_t> start = std::nullopt,
                   std::optional<std::ptrdiff_t> stop = std::nullopt, std::ptrdiff_t step = 1) const {
        return slice(*this, start, stop, step);
    }

    // index operator, like python: negative indices wrap, v[-1] == last element. throws IndexError if out of range
    typename base::reference operator[](std::ptrdiff_t i) { return base::operator[](wrap_index(i, this->size())); }
    typename base::const_reference operator[](std::ptrdiff_t i) const {
        return base::operator[](wrap_index(i, this->size()));
    }

    // python append
    template <typename Iterable>
        requires std::ranges::range<Iterable>
    vec& operator+=(const Iterable& iter) {
        this->extend(iter);
        return *this;
    }

    template <typename Iterable>
        requires std::ranges::range<Iterable>
    vec operator+(const Iterable& iter) {
        vec cpy = *this;
        cpy.extend(iter);
        return cpy;
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
