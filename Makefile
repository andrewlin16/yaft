CXX=g++
CXXFLAGS=-Wall -std=c++11 `libpng-config --cflags` -O3 -pthread
LDFLAGS=-lgmpxx -lgmp `libpng-config --ldflags`

default: yaft

yaft: main.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) main.cpp -o yaft

clean:
	rm -f yaft

clean-all:
	rm -f yaft
	rm -f *.png
