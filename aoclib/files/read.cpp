#include "File.h"

namespace aoc {

str File::read() {
    std::stringstream buffer;
    buffer << f.rdbuf();
    this->reset();
    return buffer.str();
}

vec<str> File::readlines() {
    vec<str> result;
    std::string line;
    while (std::getline(f, line)) {
        result.push_back(line);
    }
    this->reset();
    return result;
}

} // namespace aoc
