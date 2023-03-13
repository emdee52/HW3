CXX = g++
CXXFLAGS	= -std=c++20 -Wall

all: main

clean:
	rm -f main *.o

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp user.cpp product.cpp -o main