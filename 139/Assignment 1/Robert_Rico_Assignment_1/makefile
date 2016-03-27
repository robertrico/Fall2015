CC=gcc
CFLAGS= -g -Wall -Iinclude -Ilib/include
CLFLAGS= -g -Wall -Ilib/include
PRO=build/producer.o
CON=build/consumer.o
LFLAGS= -lshm -Llib -lrt
LIBSRC=lib/src/
LIBBLD=lib/build/

all: shmlib producer consumer

shmlib:
	@echo
	@echo Building Libraries...
	$(CC) $(CLFLAGS) -c $(LIBSRC)libshm.c -o $(LIBBLD)libshm.o
	ar rc lib/libshm.a $(LIBBLD)libshm.o

consumer: $(CON)
	@echo
	@echo Linking Consumer...
	$(CC) $(CON) $(CFLAGS) $(LFLAGS) -o bin/consumer

producer: $(PRO)
	@echo
	@echo Linking Producer...
	$(CC) $(PRO) $(CFLAGS) $(LFLAGS) -o bin/producer

build/consumer.o: src/consumer.c
	@echo
	@echo Compiling Consumer...
	$(CC) $(CFLAGS) $(LFLAGS) -c src/consumer.c -o build/consumer.o

build/producer.o: src/producer.c
	@echo
	@echo Compiling Producer...
	$(CC) $(CFLAGS) $(LFLAGS) -c src/producer.c -o build/producer.o

clean:
	rm bin/*
	rm build/*.o
	rm lib/build/*.o
	rm lib/*.a
