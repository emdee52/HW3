CXX = g++
CXXFLAGS	= -std=c++20 -Wall

all: main

clean:
	rm -f main *.o

main: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp driver.cpp product.cpp user.cpp -o main