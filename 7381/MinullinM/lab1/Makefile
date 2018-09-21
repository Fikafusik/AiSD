
CODE 	= ./source/
OBJ 	= main.o rocker.o
EXE 	= binary_rocker
CXX		= g++
CFLAGS 	= -Wall -Wextra -c

all: $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

main.o: $(CODE)main.cpp
	$(CXX) $(CFLAGS) $(CODE)main.cpp

rocker.o: $(CODE)rocker.hpp $(CODE)rocker.cpp 
	$(CXX) $(CFLAGS) $(CODE)rocker.cpp

clean:
	rm $(OBJ) 
	