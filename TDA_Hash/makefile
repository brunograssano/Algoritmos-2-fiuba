CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0
VG=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

hash: hash.c hash.h hash_iterador.h
	$(CC) $(CFLAGS) -c lista.c -o lista.o
	$(CC) $(CFLAGS) -c abb.c -o abb.o
	$(CC) $(CFLAGS) -c hash.c -o hash.o

pruebas: hash mi_assert.h mi_assert.c pruebas_hash.c
	$(CC) $(CFLAGS) -c mi_assert.c -o mi_assert.o
	$(CC) $(CFLAGS) pruebas_hash.c  mi_assert.o hash.o abb.o lista.o -o pruebashash


minipruebas: hash minipruebas_hash.c
	$(CC) $(CFLAGS) minipruebas_hash.c  hash.o abb.o lista.o -o minipruebas_hash

valgrind:
	$(VG) $(VFLAGS) ./pruebashash

valgrind_mini:
	$(VG) $(VFLAGS) ./minipruebas_hash

all: pruebas

.PHONY : clean

clean:
	rm -f minipruebas_hash
	rm -f pruebashash
	rm *.o
