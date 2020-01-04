CC=gcc
CFLAGS=-g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0
VG=valgrind
VFLAGS=--leak-check=full --track-origins=yes --show-reachable=yes

juego:
	$(CC) $(CFLAGS) *.c -o tp2

valgrind:
	$(VG) $(VFLAGS) ./tp2

.PHONY : clean

clean:
	rm -f tp2
