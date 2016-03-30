CC=gcc
EXE=MTFindMin
OBJ=MTFindMin.o
SRC=MTFindMin.c
CFLAGS=-O3 -lpthread -g -Wall

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean: 
	rm $(EXE)
	rm $(OBJ)
