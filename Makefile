CXX = g++
CXXFLAGS = -std=c++11 -Wall -I.

all: differentiator

differentiator: main.cpp Expression.hpp
	$(CXX) $(CXXFLAGS) -o $@ main.cpp

test: test.cpp Expression.hpp
	$(CXX) $(CXXFLAGS) -o test_program test.cpp
	./test_program

clean:
	rm -f differentiator test_program
