CC=gcc
CFLAGS= -g -Wall -Iinclude -Ilib/include
PRO=build/producer.o
CON=build/consumer.o
LFLAGS= -lshm -Llib -lrt


all: producer consumer

consumer: $(CON)
	$(CC) $(CON) $(CFLAGS) $(LFLAGS) -o bin/consumer

producer: $(PRO)
	$(CC) $(PRO) $(CFLAGS) $(LFLAGS) -o bin/producer

build/consumer.o: src/consumer.c
	$(CC) $(CFLAGS) $(LFLAGS) -c src/consumer.c -o build/consumer.o

build/producer.o: src/producer.c
	$(CC) $(CFLAGS) $(LFLAGS) -c src/producer.c -o build/producer.o

clean:
	rm bin/producer
	rm bin/consumer
	rm build/*.o
