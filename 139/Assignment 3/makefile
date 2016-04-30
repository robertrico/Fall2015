CC=g++
EXE=sched
OBJ=sched.o
SRC=sched.cc
#CFLAGS=-O3 -g -Wall
CFLAGS= -g3 -Wall

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

clean: 
	rm $(EXE)
	rm *.o 
