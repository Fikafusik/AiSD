
CODE 	= ./source/
OBJ 	= main.o stack.o
EXE 	= postfix_to_infix
CXX		= g++
CFLAGS 	= -std=c++11 -Wall -Wextra -c

all: $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

main.o: $(CODE)main.cpp
	$(CXX) $(CFLAGS) $(CODE)main.cpp

stack.o: $(CODE)stack.hpp $(CODE)stack.cpp 
	$(CXX) $(CFLAGS) $(CODE)stack.cpp

clean:
	rm $(OBJ) 

cleanest:
	rm $(OBJ) $(EXE) 
	