all:
	g++ -c main.cpp stack.cpp hash.cpp
	g++ main.o stack.o hash.o
