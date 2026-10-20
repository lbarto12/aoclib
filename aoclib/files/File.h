#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../errors.h"
#include "../strings/str.h"

namespace aoc {
struct File {
    File() = delete;
    File(const std::string& filepath, std::ios::openmode mode = std::ios::in | std::ios::out) {
        f = std::fstream(filepath, mode);
        if (!f.is_open()) {
            throw FileOpenFailedError();
        }
    }

    File(const char* filepath) {
        f = std::fstream(filepath);
        if (!f.is_open()) {
            throw FileOpenFailedError();
        }
    }

    str read() {
        std::stringstream buffer;
        buffer << f.rdbuf();
        this->reset();
        return buffer.str();
    }

    std::vector<str> readlines() {
        std::vector<str> result;
        std::string line;
        while (std::getline(f, line)) {
            result.push_back(line);
        }
        this->reset();
        return result;
    }

    void reset() {
        f.clear();
        f.seekg(0, std::ios::beg);
    }

  private:
    std::fstream f;
};
} // namespace aoc
