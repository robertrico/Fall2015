CC=gcc
CFLAGS=-g -Wall -Iinclude
EXEC=webserv
BIN=bin/
SRC=src/
WBO=build/webserv.o

all: webserv

webserv: $(WBO)
	$(CC) $(CFLAGS) $(WBO) -o $(BIN)$(EXEC)

build/webserv.o: src/webserv.c
	$(CC) $(CFLAGS) -c src/webserv.c -o $(WBO)

clean:
	rm bin/*
	rm build/*
