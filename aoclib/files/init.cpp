#include "File.h"

namespace aoc {

File::File(const std::string& filepath, std::ios::openmode mode) {
    f = std::fstream(filepath, mode);
    if (!f.is_open()) {
        throw FileOpenFailedError();
    }
}

File::File(const char* filepath) {
    f = std::fstream(filepath);
    if (!f.is_open()) {
        throw FileOpenFailedError();
    }
}

} // namespace aoc
