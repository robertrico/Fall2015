CC=gcc
EXE=sched
OBJ=sched.o
SRC=sched.c
#CFLAGS=-O3 -lpthread -g -Wall
CFLAGS= -lpthread -g3 -Wall

all: $(EXE)

$(EXE): $(OBJ) p_q.o
	$(CC) $(CFLAGS) $(OBJ) p_q.o -o $(EXE)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -c $(SRC) -o $(OBJ)

p_q.o: p_q.c
	$(CC) $(CFLAGS) -c p_q.c -o p_q.o

clean: 
	rm $(EXE)
	rm *.o 
