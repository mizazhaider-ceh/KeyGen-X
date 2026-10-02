CXX ?= g++
CXXFLAGS ?= -O2 -Wall -Wextra -std=c++17

all: KeyGen-X

KeyGen-X: KeyGen-X.cpp
	$(CXX) $(CXXFLAGS) KeyGen-X.cpp -o KeyGen-X

clean:
	rm -f KeyGen-X KeyGen-X.exe
