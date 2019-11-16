CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0
VG=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
arbol: abb.c abb.h
	$(CC) $(CFLAGS) -c abb.c -o arbol.o

pruebas: mi_assert.h mi_assert.c abb.h arbol.o pruebas_arbol.c
	$(CC) $(CFLAGS) -c mi_assert.c -o mi_assert.o
	$(CC) $(CFLAGS) pruebas_arbol.c  mi_assert.o arbol.o -o pruebas_arbol


minipruebas: abb.h arbol.o minipruebas_abb.c
	$(CC) $(CFLAGS) minipruebas_abb.c  arbol.o -o minipruebas_arbol

valgrind:
	$(VG) $(VFLAGS) ./pruebas_arbol

valgrind_mini:
	$(VG) $(VFLAGS) ./minipruebas_arbol

all: pruebas

.PHONY : clean

clean:
	rm -f minipruebas_arbol
	rm -f pruebas_arbol
	rm *.o                