CXX=g++
CXXFLAGS=-Wall -std=c++11
LIBS=

default: yaft

yaft: main.cpp
	$(CXX) $(CXXFLAGS) $(LIBS) main.cpp -o yaft

clean:
	rm -f yaft

clean-all:
	rm -f yaft
	rm -f *.png
