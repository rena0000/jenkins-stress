all: mstdriver

mstdriver: msttest.cpp Graph.h Graph.cpp DisjointSet.h DisjointSet.cpp
	g++ -std=c++11 -o mstdriver Graph.cpp DisjointSet.cpp msttest.cpp

clean:
	rm *.o mstdriver
