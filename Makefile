CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2

SRCS = main.cpp expression.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = differentiator

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

test: $(TARGET)
	./$(TARGET) --eval "x * y" x=10 y=12
	./$(TARGET) --diff "x * sin(x)" --by x

.PHONY: all clean test