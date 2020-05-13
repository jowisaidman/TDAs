#include "heap.h"
#include "testing.h"
#include <stdio.h>

void pruebas_heap_alumno(void);


int main (){
	printf("+++ PRUEBAS DEL ALUMNO +++\n");
	pruebas_heap_alumno();

	return failure_count() > 0;
}