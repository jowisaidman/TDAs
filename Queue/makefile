CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic

all: testing.c testing.h main.c cola.c cola.h pruebas_alumno.c
	$(CC) $(CFLAGS) testing.c cola.c pruebas_alumno.c main.c -o pruebas

gdb: testing.c testing.h main.c cola.c cola.h pruebas_alumno.c
	$(CC) $(CFLAGS) testing.c cola.c pruebas_alumno.c main.c -DTEST --debug -o pruebas

vd: testing.c testing.h main.c cola.c cola.h pruebas_alumno.c
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
