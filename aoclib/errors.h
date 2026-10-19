#pragma once

#include <stdexcept>
#include <string>

namespace aoc {

struct InvalidMatrixError : public std::runtime_error {
    explicit InvalidMatrixError(const std::string& what = "Invalid Matrix") : std::runtime_error(what) {}
};
struct EmptyMatrixError : public std::runtime_error {
    explicit EmptyMatrixError(const std::string& what = "Empty Matrix") : std::runtime_error(what) {}
};
} // namespace aoc
