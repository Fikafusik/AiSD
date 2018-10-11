
CODE 	= ./source/
OBJ 	= main.o Additional.o AVLNode.o AVLTree.o 
EXE 	= avl_tree
CXX		= clang++
CFLAGS 	= -std=c++11 -Wall -Wextra -c 

all: $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

main.o: $(CODE)main.cpp $(CODE)AVLTree.hpp
	$(CXX) $(CFLAGS) $(CODE)main.cpp

Additional.o: $(CODE)Additional.cpp
	$(CXX) $(CFLAGS) $(CODE)Additional.cpp

AVLTree.o:  $(CODE)AVLTree.cpp $(CODE)AVLNode.hpp
	$(CXX) $(CFLAGS) $(CODE)AVLTree.cpp

AVLNode.o: $(CODE)AVLNode.cpp $(CODE)Additional.hpp
	$(CXX) $(CFLAGS) $(CODE)AVLNode.cpp

clean:
	rm $(OBJ) 

cleanest:
	rm $(OBJ) $(EXE) 
	