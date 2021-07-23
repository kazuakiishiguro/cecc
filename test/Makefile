CC=gcc
CFLAGS=-g -Wall -Werror

all: verify_ecdh

cecc.o: ../cecc.c ../cecc.h
	$(CC) $(CFLAGS) -c -o cecc.o ../cecc.c

%.o: %.c ../cecc.h
	$(CC) -c $(CFLAGS) $< -o $@

verify_ecdh: verify_ecdh.o testlib.o cecc.o
	$(CC) -o verify_ecdh verify_ecdh.o testlib.o cecc.o

clean:
	rm -f *.o verify_ecdh
