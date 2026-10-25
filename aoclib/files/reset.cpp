#include "File.h"

namespace aoc {

void File::reset() {
    f.clear();
    f.seekg(0, std::ios::beg);
}

} // namespace aoc
