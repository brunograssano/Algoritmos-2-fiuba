CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0
VG=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes
cola: cola.c cola.h
	$(CC) $(CFLAGS) -c cola.c -o cola.o

pruebas: cola.h cola.o pruebas_cola.c
	$(CC) $(CFLAGS) pruebas_cola.c  cola.o -o pruebas_cola


mini_pruebas: cola.h cola.o minipruebas_cola.c
	$(CC) $(CFLAGS) minipruebas_cola.c  cola.o -o minipruebas_cola

valgrind:
	$(VG) $(VFLAGS) ./pruebas_cola

valgrind_minipruebas:
	$(VG) $(VFLAGS) ./minipruebas_cola

all: pruebas

.PHONY : clean

clean:
	rm -f pruebas_cola
	rm *.o                