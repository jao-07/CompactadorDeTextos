CC = g++
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/Huffman.o $(OBJ)/Lista.o $(OBJ)/No.o
HDRS = $(INC)/Huffman.hpp $(INC)/Lista.hpp $(INC)/No.hpp

EXE = $(BIN)/main

all:  $(EXE)

$(BIN)/main: $(OBJS) $(SRC)/main.cpp
	$(CC) -o $(EXE) $(SRC)/main.cpp $(OBJS) -Wall -lm

$(OBJ)/Huffman.o: $(HDRS) $(SRC)/Huffman.cpp
	$(CC) -o $(OBJ)/Huffman.o $(SRC)/Huffman.cpp -c -Wall -lm

$(OBJ)/Lista.o: $(HDRS) $(SRC)/Lista.cpp
	$(CC) -o $(OBJ)/Lista.o $(SRC)/Lista.cpp -c -Wall -lm

$(OBJ)/No.o: $(HDRS) $(SRC)/No.cpp
	$(CC) -o $(OBJ)/No.o $(SRC)/No.cpp -c -Wall -lm

clean:
	rm -f $(EXE) $(OBJS)