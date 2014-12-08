CC = gcc
CFLAGS = -g

default: test

test:  config.o test.o 
	$(CC) $(CFLAGS) -o test config.o test.o

config.o:  config.c config.h 
	$(CC) $(CFLAGS) -c config.c

test.o:  test.c config.h 
	$(CC) $(CFLAGS) -c test.c

clean: 
	rm -f *.o test
