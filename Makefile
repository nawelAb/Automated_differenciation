CC=gcc
CFLAGS=-W -Wall -ansi -pendantic
LDFLAGS=
EXEC=main

all: $(EXEC)

main: tests.o libs.o
	$(CC) -o $@ $^ $(LDFLAGS)

tests.o: tests.cpp
	$(CC) -o $@ -c $< $(CFLAGS)

libs.o: libs.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf *.o
