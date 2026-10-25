#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../ds/strings/str.h"
#include "../errors.h"

namespace aoc {
class File {
  public: // b5
    File() = delete;
    File(const std::string& filepath, std::ios::openmode mode = std::ios::in | std::ios::out);
    File(const char* filepath);

    // read all as string
    str read();

    // read each line as array of str
    vec<str> readlines();

    // move file cursor back to beginning of file for re-reading
    void reset();

    ~File();

  private:
    std::fstream f;
};
} // namespace aoc
