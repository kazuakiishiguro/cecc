CC=gcc

default: main
all: default

cecc.o: ../cecc.c ../cecc.h
	$(CC) -g -c $< -o $@

main.o:	main.c ../cecc.h
	$(CC) -I.. -g -c $< -o $@

main: cecc.o main.o
	$(CC) main.o cecc.o -o $@

clean:
	rm -f cecc.o main.o main

.PHONY: default all clean
