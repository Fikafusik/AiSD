
CODE 	= ./source/
OBJ 	= main.o Queue.o BinaryTree.o
EXE 	= binary_tree
CXX		= g++
CFLAGS 	= -std=c++11 -Wall -Wextra -c

all: $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

main.o: $(CODE)main.cpp $(CODE)Queue.hpp
	$(CXX) $(CFLAGS) $(CODE)main.cpp

BinaryTree.o:  $(CODE)BinaryTree.hpp $(CODE)Queue.hpp
	$(CXX) $(CFLAGS) $(CODE)BinaryTree.cpp

Queue.o: $(CODE)Queue.hpp $(CODE)Queue.cpp 
	$(CXX) $(CFLAGS) $(CODE)Queue.cpp

clean:
	rm $(OBJ) 

cleanest:
	rm $(OBJ) $(EXE) 
	