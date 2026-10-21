CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -MMD -MP
TARGET = main

SRCS = $(shell find . -path ./examples -prune -o -name '*.cpp' -print)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(OBJS) $(DEPS)

-include $(DEPS)

.PHONY: all run clean
