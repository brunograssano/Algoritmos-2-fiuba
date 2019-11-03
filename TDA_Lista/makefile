CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0
VG=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
lista: lista.c lista.h
	$(CC) $(CFLAGS) -c lista.c -o lista.o

pruebas: mi_assert.h mi_assert.c lista.h lista.o pruebas_lista.c
	$(CC) $(CFLAGS) -c mi_assert.c -o mi_assert.o
	$(CC) $(CFLAGS) pruebas_lista.c  mi_assert.o lista.o -o pruebas_lista


mini_pruebas: lista.h lista.o minipruebas_lista.c
	$(CC) $(CFLAGS) minipruebas_lista.c  lista.o -o minipruebas_lista

valgrind:
	$(VG) $(VFLAGS) ./pruebas_lista

valgrind_minipruebas:
	$(VG) $(VFLAGS) ./minipruebas_lista

all: pruebas

.PHONY : clean

clean:
	rm -f minipruebas_lista
	rm -f pruebas_lista
	rm *.o                