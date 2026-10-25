CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++20 -O2 -MMD -MP
AOCLIB = /home/liam/Desktop/Important Things/programming/cpp/aoclib
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
