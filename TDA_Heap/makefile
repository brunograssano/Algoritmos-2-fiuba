CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0
VG=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

heap: heap.c heap.h
	$(CC) $(CFLAGS) -c heap.c -o heap.o

pruebas: heap mi_assert.h mi_assert.c ejemplo1.c ejemplo2.c
	$(CC) $(CFLAGS) -c mi_assert.c -o mi_assert.o
	$(CC) $(CFLAGS) ejemplo1.c  mi_assert.o heap.o -o ejemplo1
	$(CC) $(CFLAGS) ejemplo2.c  mi_assert.o heap.o -o ejemplo2

valgrind:
	$(VG) $(VFLAGS) ./ejemplo1
	$(VG) $(VFLAGS) ./ejemplo2

all: pruebas

.PHONY : clean

clean:
	rm -f ejemplo1 ejemplo2
	rm *.o
