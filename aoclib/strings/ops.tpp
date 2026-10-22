#include "str.h"

namespace aoc {

template <typename T>
    requires(!std::derived_from<std::remove_cvref_t<T>, str>)
str& str::operator=(T&& x) {
    std::string::operator=(std::forward<T>(x));
    return *this;
}

template <typename T> str& str::operator+=(T&& x) {
    std::string::operator+=(std::forward<T>(x));
    return *this;
}

inline char& str::operator[](std::ptrdiff_t i) { return std::string::operator[](wrap_index(i, size())); }
inline const char& str::operator[](std::ptrdiff_t i) const { return std::string::operator[](wrap_index(i, size())); }

inline str str::substr(size_type pos, size_type n) const { return std::string::substr(pos, n); }

template <typename... Args> str& str::append(Args&&... args) {
    std::string::append(std::forward<Args>(args)...);
    return *this;
}

template <typename... Args> str& str::assign(Args&&... args) {
    std::string::assign(std::forward<Args>(args)...);
    return *this;
}

template <typename... Args> str& str::replace(Args&&... args) {
    std::string::replace(std::forward<Args>(args)...);
    return *this;
}

template <typename... Args> decltype(auto) str::insert(Args&&... args) {
    using R = decltype(std::string::insert(std::forward<Args>(args)...));
    if constexpr (std::is_same_v<R, std::string&>) {
        std::string::insert(std::forward<Args>(args)...);
        return static_cast<str&>(*this);
    } else {
        return std::string::insert(std::forward<Args>(args)...);
    }
}

template <typename... Args> decltype(auto) str::erase(Args&&... args) {
    using R = decltype(std::string::erase(std::forward<Args>(args)...));
    if constexpr (std::is_same_v<R, std::string&>) {
        std::string::erase(std::forward<Args>(args)...);
        return static_cast<str&>(*this);
    } else {
        return std::string::erase(std::forward<Args>(args)...);
    }
}

// str + x
template <StrLike T> str operator+(str lhs, const T& rhs) {
    lhs += rhs;
    return lhs;
}

// x + str
template <StrLike T>
    requires(!std::derived_from<T, str>)
str operator+(const T& lhs, const str& rhs) {
    str out(lhs);
    out += rhs;
    return out;
}

// str * n
template <std::integral N> str operator*(const str& s, N n) {
    str out;
    if (n <= 0) return out;
    out.reserve(s.size() * static_cast<std::size_t>(n));
    for (N i = 0; i < n; ++i) out += s;
    return out;
}

// n * str
template <std::integral N> str operator*(N n, const str& s) { return s * n; }

} // namespace aoc
