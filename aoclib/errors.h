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

struct FileOpenFailedError : public std::runtime_error {
    explicit FileOpenFailedError(const std::string& what = "File could not be opened") : std::runtime_error(what) {}
};

struct IndexError : public std::out_of_range {
    explicit IndexError(const std::string& what = "Index out of range") : std::out_of_range(what) {}
};

struct ValueError : public std::invalid_argument {
    explicit ValueError(const std::string& what = "Invalid value") : std::invalid_argument(what) {}
};

struct KeyError : public std::out_of_range {
    explicit KeyError(const std::string& what = "Key not found") : std::out_of_range(what) {}
};
} // namespace aoc
