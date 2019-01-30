CXXFLAGS=-std=c++17 -Wall -Wextra -fstack-protector-strong -pedantic -ffast-math -fopenmp -pipe
CXXFLAGS += -Ofast -march=native
LDLIBS=-lpthread -lstdc++fs
.PHONY: all clean

all:
	$(CXX) $(CXXFLAGS) -o main24 main24.cpp Bitmap24/WinBitmap24.cpp $(LDLIBS)
	strip --strip-all main24

clean:
	rm -f main24
