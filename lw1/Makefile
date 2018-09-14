
CODE 	= ./Source/
OBJ 	= main.o
EXE 	= lexical_analyzer
CXX		= g++
CFLAGS 	= -Wall -Wextra -c

all: $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

main.o: $(CODE)main.cpp
	$(CXX) $(CFLAGS) $(CODE)main.cpp

clean:
	rm $(OBJ) $(EXE)
	