CC=gcc
CFLAGS= -g -Wall
PRO=producer.o
CON=consumer.o

all: producer consumer

producer: $(PRO)
	gcc $(PRO) -o producer

consumer: $(CON)
	gcc $(CON) -o consumer

producer.o: producer.c
	$(CC) $(CFLAGS) -c producer.c

consumer.o: consumer.c
	$(CC) $(CFLAGS) -c consumer.c

clean:
	rm producer
	rm consumer
	rm *.o
