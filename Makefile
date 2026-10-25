CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2 -MMD -MP
TARGET = main
LIB = libaoc.a

SRCS = $(shell find . -path ./examples -prune -o -name '*.cpp' -print)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(OBJS:.o=.d)
LIB_SRCS = $(shell find ./aoclib -name '*.cpp')
LIB_OBJS = $(LIB_SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

lib: $(LIB)

$(LIB): $(LIB_OBJS)
	ar rcs $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(LIB) $(OBJS) $(DEPS)

-include $(DEPS)

.PHONY: all lib run clean
