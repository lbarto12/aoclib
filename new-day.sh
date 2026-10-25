#!/usr/bin/env bash
set -euo pipefail

if [ $# -ne 1 ]; then
    echo "usage: $0 <day>" >&2
    exit 1
fi

AOCLIB="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
DIR="day_$1"

if [ -e "$DIR" ]; then
    echo "error: $DIR already exists" >&2
    exit 1
fi

mkdir "$DIR"
touch "$DIR/input.txt"

cat > "$DIR/main.cpp" <<'EOF'
#include <aoclib/lib.h>

using namespace aoc;

// Solution
int main() {
    vec<str> lines = File("input.txt").readlines();
    println(lines);
}
EOF

cat > "$DIR/Makefile" <<'EOF'
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2 -MMD -MP
AOCLIB = @AOCLIB@
TARGET = main

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

aoclib:
	$(MAKE) -C "$(AOCLIB)" lib

$(TARGET): aoclib $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) -L"$(AOCLIB)" -laoc

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -I"$(AOCLIB)" -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)

.PHONY: all aoclib run clean
EOF

cat > "$DIR/.clangd" <<'EOF'
Completion:
  HeaderInsertion: Never
Diagnostics:
  MissingIncludes: None
  UnusedIncludes: None
  Suppress: [pp_including_mainfile_in_preamble]
CompileFlags:
  Add: [-std=c++23, "-I@AOCLIB@"]
---
If:
  PathMatch: .*\.tpp
CompileFlags:
  Add: [-xc++-header]
EOF

sed -i "s|@AOCLIB@|$AOCLIB|" "$DIR/Makefile" "$DIR/.clangd"

echo "created $DIR"
