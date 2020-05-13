CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic

all: testing.c testing.h main.c pila.c pila.h pruebas_alumno.c
	$(CC) $(CFLAGS) testing.c pila.c pruebas_alumno.c main.c -o pruebas

gdb: testing.c testing.h main.c pila.c pila.h pruebas_alumno.c
	$(CC) $(CFLAGS) testing.c pila.c pruebas_alumno.c main.c -DTEST --debug -o pruebas

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
