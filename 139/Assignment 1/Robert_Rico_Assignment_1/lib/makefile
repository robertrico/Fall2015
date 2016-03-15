CC=gcc
CFLAGS= -g -Wall -Iinclude
PRO=libshm.o



all: compile library

compile: src/libshm.c
	$(CC) $(CFLAGS) -c src/libshm.c -o build/libshm.o

library:
	ar rc libshm.a build/libshm.o

clean:
	rm build/*.o
	rm libshm.a
