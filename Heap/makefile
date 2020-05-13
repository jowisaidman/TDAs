CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror

all: testing.c testing.h main.c heap.c heap.h pruebas_heap_alumno.c
	$(CC) $(CFLAGS) testing.c heap.c pruebas_heap_alumno.c main.c -o pruebas

gdb: testing.c testing.h main.c heap.c heap.h pruebas_heap_alumno.c
	$(CC) $(CFLAGS) testing.c heap.c pruebas_heap_alumno.c main.c -DTEST --debug -o pruebas

vg: testing.c testing.h main.c heap.c heap.h pruebas_heap_alumno.c
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas

run: all
	./pruebas

clean:
	rm -f *.0 pruebas

ejemplo_echo:
	echo "Texto super interesante"

ejemplo_ls:
	ls

ejemplo_date:
	date
