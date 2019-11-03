CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0
VG=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
pila: pila.c pila.h
	$(CC) $(CFLAGS) -c pila.c -o pila.o

pruebas: pila.h pila.o pruebas_pila.c
	$(CC) $(CFLAGS) pruebas_pila.c  pila.o -o pruebas_pila

valgrind:
	$(VG) $(VFLAGS) ./pruebas_pila

all: pruebas

.PHONY : clean

clean:
	rm -f pruebas_pila
	rm *.o                