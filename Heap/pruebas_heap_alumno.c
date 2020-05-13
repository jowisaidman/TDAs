#define _XOPEN_SOURCE 500
#include "heap.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b) {
	
	char* str1 = (char*)a;
	char* str2 = (char*)b;
	int num = strcmp(str1,str2);
	return num;
}

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_heap_vacio() {
	printf("Comienzo de pruebas con heap vacio\n");
	heap_t* heap1 = heap_crear(cmp);
	print_test("Heap1 inicializado correctamente", heap1 != NULL);
	print_test("Heap1 esta vacio es true", heap_esta_vacio(heap1) == true);
	print_test("Heap1 cantidad es 0", heap_cantidad(heap1) == 0);	
	print_test("heap_desencolar devuelve NULL", heap_desencolar(heap1) == NULL);
	print_test("heap_ver_max devuelve NULL", heap_ver_max(heap1) == NULL);
	heap_destruir(heap1, NULL);
	print_test("Heap1 se destruye correctamente", true);
}

void pruebas_heap_encolar() {
	printf("Comienzo de pruebas heap encolar\n");
	
	//Datos
	char* dato1 = strdup("1");
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	char* dato4 = strdup("4");
	char* dato5 = strdup("5");
	char* dato6 = strdup("6");
	char* dato7 = strdup("7");		
	
	heap_t* heap2 = heap_crear(cmp);	

	//dato2
	bool se_encolo = heap_encolar(heap2, dato2);
	print_test("Se encolo dato2", se_encolo == true);
	print_test("Heap2 tiene 1 elementos", heap_cantidad(heap2) == 1);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap2) == false);
	print_test("heap ver maximo devuelve 2", cmp(heap_ver_max(heap2),"2") == 0);

	//dato1
	se_encolo = heap_encolar(heap2, dato1);
	print_test("Se encolo dato1", se_encolo == true);
	print_test("Heap2 tiene 2 elementos", heap_cantidad(heap2) == 2);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap2) == false);
	print_test("heap ver maximo devuelve 1", cmp(heap_ver_max(heap2),"2") == 0);
	
	//dato3
	se_encolo = heap_encolar(heap2, dato3);
	print_test("Se encolo dato3", se_encolo == true);
	print_test("Heap2 tiene 3 elementos", heap_cantidad(heap2) == 3);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap2) == false);
	print_test("heap ver maximo devuelve 3", cmp(heap_ver_max(heap2),"3") == 0);
	
	//dato4
	se_encolo = heap_encolar(heap2, dato4);
	print_test("Se encolo dato4", se_encolo == true);
	print_test("Heap2 tiene 4 elementos", heap_cantidad(heap2) == 4);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap2) == false);
	print_test("heap ver maximo devuelve 4", cmp(heap_ver_max(heap2),"4") == 0);
	
	//dato5
	se_encolo = heap_encolar(heap2, dato5);
	print_test("Se encolo dato5", se_encolo == true);
	print_test("Heap2 tiene 5 elementos", heap_cantidad(heap2) == 5);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap2) == false);
	print_test("heap ver maximo devuelve 5", cmp(heap_ver_max(heap2),"5") == 0);	

	//dato6
	se_encolo = heap_encolar(heap2, dato6);
	print_test("Se encolo dato6", se_encolo == true);
	print_test("Heap2 tiene 6 elementos", heap_cantidad(heap2) == 6);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap2) == false);
	print_test("heap ver maximo devuelve 6", cmp(heap_ver_max(heap2),"6") == 0);

	//dato7
	se_encolo = heap_encolar(heap2, dato7);
	print_test("Se encolo dato7", se_encolo == true);
	print_test("Heap2 tiene 7 elementos", heap_cantidad(heap2) == 7);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap2) == false);
	print_test("heap ver maximo devuelve 7", cmp(heap_ver_max(heap2),"7") == 0);

	//dato6
	se_encolo = heap_encolar(heap2, dato6);
	print_test("Se encolo dato6 (segunda vez)", se_encolo == true);
	print_test("Heap2 tiene 8 elementos", heap_cantidad(heap2) == 8);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap2) == false);
	print_test("heap ver maximo devuelve 1", cmp(heap_ver_max(heap2),"7") == 0);


	free(dato1);
	free(dato2);
	free(dato3);
	free(dato4);
	free(dato5);
	free(dato6);
	free(dato7);
	heap_destruir(heap2, NULL);
	print_test("Heap2 se destruye correctamente", true);		
}
	

void pruebas_heap_desencolar() {
	printf("Comienzo de pruebas heap desencolar\n");
	char* dato1 = strdup("1");
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	char* dato4 = strdup("4");
	char* dato5 = strdup("5");
	char* dato6 = strdup("6");
	char* dato7 = strdup("7");

	heap_t* heap3 = heap_crear(cmp);	
	heap_encolar(heap3, dato1);
	heap_encolar(heap3, dato2);
	heap_encolar(heap3, dato3);
	heap_encolar(heap3, dato4);
	heap_encolar(heap3, dato5);
	heap_encolar(heap3, dato6);
	heap_encolar(heap3, dato7);
	
	print_test("Heap3 se encolaron 7 elementos (cantidad = 7)", heap_cantidad(heap3) == 7);
	
	
	char* dato_obtenido = heap_desencolar(heap3);
	print_test("Se desencolo y se obtuvo 7", cmp(dato_obtenido,"7") == 0);
	print_test("Heap3 tiene 6 elementos", heap_cantidad(heap3) == 6);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap3) == false);
	print_test("heap ver maximo devuelve 6", cmp(heap_ver_max(heap3),"6") == 0);	
	
	dato_obtenido = heap_desencolar(heap3);
	print_test("Se desencolo y se obtuvo 6", cmp(dato_obtenido,"6") == 0);
	print_test("Heap3 tiene 5 elementos", heap_cantidad(heap3) == 5);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap3) == false);
	print_test("heap ver maximo devuelve 5", cmp(heap_ver_max(heap3),"5") == 0);
	
	dato_obtenido = heap_desencolar(heap3);
	print_test("Se desencolo y se obtuvo 5", cmp(dato_obtenido,"5") == 0);
	print_test("Heap3 tiene 4 elementos", heap_cantidad(heap3) == 4);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap3) == false);
	print_test("heap ver maximo devuelve 4", cmp(heap_ver_max(heap3),"4") == 0);

	dato_obtenido = heap_desencolar(heap3);
	print_test("Se desencolo y se obtuvo 4", cmp(dato_obtenido,"4") == 0);
	print_test("Heap3 tiene 3 elementos", heap_cantidad(heap3) == 3);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap3) == false);
	print_test("heap ver maximo devuelve 3", cmp(heap_ver_max(heap3),"3") == 0);

	dato_obtenido = heap_desencolar(heap3);
	print_test("Se desencolo y se obtuvo 3", cmp(dato_obtenido,"3") == 0);
	print_test("Heap3 tiene 2 elementos", heap_cantidad(heap3) == 2);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap3) == false);
	print_test("heap ver maximo devuelve 2", cmp(heap_ver_max(heap3),"2") == 0);

	dato_obtenido = heap_desencolar(heap3);
	print_test("Se desencolo y se obtuvo 2", cmp(dato_obtenido,"2") == 0);
	print_test("Heap3 tiene 1 elementos", heap_cantidad(heap3) == 1);
	print_test("heap esta vacio devuelve false", heap_esta_vacio(heap3) == false);
	print_test("heap ver maximo devuelve 1", cmp(heap_ver_max(heap3),"1") == 0);

	dato_obtenido = heap_desencolar(heap3);
	print_test("Se desencolo y se obtuvo 1", cmp(dato_obtenido,"1") == 0);
	print_test("Heap3 tiene 0 elementos", heap_cantidad(heap3) == 0);
	print_test("heap esta vacio devuelve true", heap_esta_vacio(heap3) == true);
	print_test("heap ver maximo devuelve NULL", heap_ver_max(heap3) == NULL);
	print_test("heap desencolar devuelve NULL", heap_desencolar(heap3) == NULL);
	
	
	heap_destruir(heap3, NULL);
	print_test("Heap3 se destruye correctamente", true);	
	
	free(dato1);
	free(dato2);
	free(dato3);
	free(dato4);
	free(dato5);
	free(dato6);
	free(dato7);	
}	

//*******************************************************************************************************************************

void pruebas_heap_redimension() {
	printf("Comienzo de pruebas heap redimensionar\n");
	char* dato1 = strdup("1");
	char* dato2 = strdup("2");
	char* dato3 = strdup("3");
	char* dato4 = strdup("4");
	char* dato5 = strdup("5");
	char* dato6 = strdup("6");
	char* dato7 = strdup("7");
	char* dato8 = strdup("8");
	char* dato9 = strdup("9");
	char* dato10 = strdup("10");
	char* dato11 = strdup("11");
	char* dato12 = strdup("12");
	char* dato13 = strdup("13");
	char* dato14 = strdup("14");
	char* dato15 = strdup("15");
	
	heap_t* heap4 = heap_crear(cmp);
	
	heap_encolar(heap4, dato1);
	heap_encolar(heap4, dato2);
	heap_encolar(heap4, dato3);
	heap_encolar(heap4, dato4);
	heap_encolar(heap4, dato5);
	heap_encolar(heap4, dato6);
	heap_encolar(heap4, dato7);	
	heap_encolar(heap4, dato8);
	heap_encolar(heap4, dato9);
	heap_encolar(heap4, dato10);
	heap_encolar(heap4, dato11);
	heap_encolar(heap4, dato12);
	heap_encolar(heap4, dato13);
	heap_encolar(heap4, dato14);	
	heap_encolar(heap4, dato15);
	
	print_test("La cantidad de elementos es 15", heap_cantidad(heap4) == 15);	
	
	
	heap_destruir(heap4, NULL);
	print_test("Heap4 se destruye correctamente", true);	
	
	free(dato1);
	free(dato2);
	free(dato3);
	free(dato4);
	free(dato5);
	free(dato6);
	free(dato7);
	free(dato8);
	free(dato9);
	free(dato10);
	free(dato11);
	free(dato12);
	free(dato13);
	free(dato14);		
	free(dato15);	
	

}

//*******************************************************************************************************************************
 
void pruebas_heap_arr() {
	
	void* arreglo[5];
	arreglo[0]= "5";
	arreglo[1] = "3";
	arreglo[2] = "4";
	arreglo[3] = "1";
	arreglo[4] = "2";
	
	heap_t* heap5 = heap_crear_arr(arreglo,5,cmp);
	
	print_test("Heap5 inicializado correctamente", heap5 != NULL);
	print_test("Heap5 esta vacio es false", heap_esta_vacio(heap5) == false);
	print_test("Heap1 cantidad es 5", heap_cantidad(heap5) == 5);	
	print_test("heap_ver_min devuelve 5", cmp(heap_ver_max(heap5),"5") == 0);	
	
	heap_destruir(heap5, NULL);
	print_test("Heap5 se destruye correctamente", true);	
}

//***************************************************************************************************
void imprimir_arr(void** arr,int cant) {
	for (int i = 0; i<cant; i++) {
		printf("%s",(char*)arr[i]);
	}
	printf("\n");	
	
}

//*****************************************************************************************************
void pruebas_heap_sort() {
	
	void* arreglo[5];
	arreglo[0]= "5";
	arreglo[1] = "3";
	arreglo[2] = "4";
	arreglo[3] = "1";
	arreglo[4] = "2";
	
	imprimir_arr(arreglo,5);
	heap_sort(arreglo,5,cmp);
	imprimir_arr(arreglo,5);
	
	
}

//*******************************************************************************************************************************

void pruebas_heap_alumno() {
	pruebas_heap_vacio();
	printf("******************************\n");
	pruebas_heap_encolar();
	printf("******************************\n");
	pruebas_heap_desencolar();
	printf("******************************\n");
	pruebas_heap_redimension();
	printf("******************************\n");
	pruebas_heap_arr();
	printf("******************************\n");
	pruebas_heap_sort();
	printf("******************************\n");
}

//*******************************************************************************************************************************










