#define _XOPEN_SOURCE 500
#include "abb.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//*******************************************************************************************************************************
int cmp(const char* vector1, const char* vector2) {
	int pos_actual=0;
	int n1 = (int)strlen(vector1);
	int n2 = (int)strlen(vector2);
	while (pos_actual<n1 && pos_actual<n2) {
		if (vector2[pos_actual]<vector1[pos_actual]){
		    return -1;
                }
		if (vector1[pos_actual]<vector2[pos_actual]) {
		    return 1;
                }
		if (pos_actual==n2-1 && n1!=n2) {
		    return -1;
                }
		pos_actual++;
        }
	if (n2==n1) {
		return 0;
        }
	return 1;	
}

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_abb_vacio() {
	printf("Comienzo de pruebas con abb vacio\n");
	abb_t* arbol1 = abb_crear(cmp, NULL);
	print_test("Arbol1 inicializado correctamente", arbol1 != NULL);
	print_test("Arbol1 esta vacio", abb_cantidad(arbol1) == 0);
	print_test("abb_obtener devuelve NULL", abb_obtener(arbol1,"1") == NULL);
	print_test("abb_pertenece devuelve false", abb_pertenece(arbol1,"1") == false);
	abb_destruir(arbol1);
	print_test("Arbol1 se destruye correctamente", true);
}


//*******************************************************************************************************************************

void pruebas_abb_insertar() {
	char* dato6 = strdup("2");
	char* dato2 = strdup("1");
	char* dato1 = strdup("3");
	
	abb_t* arbol2 = abb_crear(strcmp,NULL);
	
	
	bool se_inserto = abb_guardar(arbol2, dato6, dato6);
	print_test("Se intero dato6", se_inserto == true);
	print_test("Arbol2 tiene 1 elemento", abb_cantidad(arbol2) == 1);
	print_test("abb_obtener a devuelve perro", strcmp(abb_obtener(arbol2,dato6),dato6) == 0);
	print_test("abb_pertenece a devuelve true", abb_pertenece(arbol2,dato6) == true);	
	
	se_inserto = abb_guardar(arbol2, dato2, dato2);
	print_test("Se intero dato2", se_inserto == true);
	print_test("Arbol2 tiene 2 elemento", abb_cantidad(arbol2) == 2);
	print_test("abb_obtener a devuelve gato", strcmp(abb_obtener(arbol2,dato2),dato2) == 0);
	print_test("abb_pertenece a devuelve true", abb_pertenece(arbol2,dato2) == true);		
	
	se_inserto = abb_guardar(arbol2, dato1, dato1);
	print_test("Se intero dato1", se_inserto == true);
	print_test("Arbol2 tiene 3 elemento", abb_cantidad(arbol2) == 3);
	print_test("abb_obtener a devuelve perro", strcmp(abb_obtener(arbol2,dato1),dato1) == 0);
	print_test("abb_pertenece a devuelve true", abb_pertenece(arbol2,dato1) == true);		
	
	abb_destruir(arbol2);
	
	
	free(dato6);
	free(dato2);
	free(dato1);	
}

void pruebas_abb_borrar() {
	printf("Comienzo de pruebas abb borrar\n");
	char* dato6 = strdup("6");
	char* dato2 = strdup("2");
	char* dato1 = strdup("1");
	char* dato3 = strdup("3");
	char* dato8 = strdup("8");
	char* dato7 = strdup("7");
	char* dato9 = strdup("9");

	
	printf("Borrar arbol de a hojas\n");
	abb_t* arbol3 = abb_crear(cmp, NULL);		
	//dato6	
	bool se_inserto = abb_guardar(arbol3, "6", dato6);
	print_test("Se intero dato6", se_inserto == true);
	//dato2
	se_inserto = abb_guardar(arbol3, "2", dato2);
	print_test("Se intero dato2", se_inserto == true);
	//dato3
	se_inserto = abb_guardar(arbol3, "3", dato3);
	print_test("Se intero dato3", se_inserto == true);
	//dato8
	se_inserto = abb_guardar(arbol3, "8", dato8);
	print_test("Se intero dato8", se_inserto == true);
	//dato7
	se_inserto = abb_guardar(arbol3, "7", dato7);
	print_test("Se intero dato7", se_inserto == true);
	print_test("La cantidad del arbol3 es 5", abb_cantidad(arbol3) == 5);

	//Borro dato3
	void* dato = abb_borrar(arbol3, "3");
	print_test("Se borro dato3 y se obtuvo 3", strcmp(dato,"3") == 0);
	print_test("abb_pertenece(arbol3,3) es false",abb_pertenece(arbol3,"3") == false);
	print_test("abb_obtener(arbol3, 3) es NULL",abb_obtener(arbol3, "3") == NULL);
	print_test("La cantidad de arbol3 es 4", abb_cantidad(arbol3) == 4);
	
	//Borro dato7
	dato = abb_borrar(arbol3, "7");
	print_test("Se borro dato7 y se obtuvo 7", strcmp(dato,"7") == 0);
	print_test("abb_pertenece(arbol3,7) es false",abb_pertenece(arbol3,"7") == false);
	print_test("abb_obtener(arbol3, 7) es NULL",abb_obtener(arbol3, "7") == NULL);
	print_test("La cantidad de arbol3 es 3", abb_cantidad(arbol3) == 3);
	
	//Borro dato8
	dato = abb_borrar(arbol3, "8");
	print_test("Se borro dato8 y se obtuvo 8", strcmp(dato,"8") == 0);
	print_test("abb_pertenece(arbol3,8) es false",abb_pertenece(arbol3,"8") == false);
	print_test("abb_obtener(arbol3, 8) es NULL",abb_obtener(arbol3, "8") == NULL);
	print_test("La cantidad de arbol3 es 2", abb_cantidad(arbol3) == 2);
	
	//Borro dato2
	dato = abb_borrar(arbol3, "2");
	print_test("Se borro dato2 y se obtuvo 2", strcmp(dato,"2") == 0);
	print_test("abb_pertenece(arbol3,2) es false",abb_pertenece(arbol3,"2") == false);
	print_test("abb_obtener(arbol3, 2) es NULL",abb_obtener(arbol3, "2") == NULL);
	print_test("La cantidad de arbol3 es 1", abb_cantidad(arbol3) == 1);
	
	//Borro dato6
	dato = abb_borrar(arbol3, "6");
	print_test("Se borro dato6 y se obtuvo 6", strcmp(dato,"6") == 0);
	print_test("abb_pertenece(arbol3,6) es false",abb_pertenece(arbol3,"6") == false);
	print_test("abb_obtener(arbol3, 6) es NULL",abb_obtener(arbol3, "6") == NULL);
	print_test("La cantidad de arbol3 es 0", abb_cantidad(arbol3) == 0);		
	print_test("Arbol3 no es NULL", arbol3 != NULL);
	abb_destruir(arbol3);
	print_test("Arbol3 se destruye correctamente", true);	
	
	printf("Borrar con 1 hijo en distintas posiciones\n");
	abb_t* arbol4 = abb_crear(cmp, NULL);	
	//dato6	
	se_inserto = abb_guardar(arbol4, "6", dato6);
	print_test("Se intero dato6", se_inserto == true);
	//dato2
	se_inserto = abb_guardar(arbol4, "2", dato2);
	print_test("Se intero dato2", se_inserto == true);
	//dato3
	se_inserto = abb_guardar(arbol4, "3", dato3);
	print_test("Se intero dato3", se_inserto == true);
	//dato8
	se_inserto = abb_guardar(arbol4, "8", dato8);
	print_test("Se intero dato8", se_inserto == true);
	//dato7
	se_inserto = abb_guardar(arbol4, "7", dato7);
	print_test("Se intero dato7", se_inserto == true);
	print_test("La cantidad del arbol4 es 5", abb_cantidad(arbol4) == 5);		
	
	//Borro dato2
	dato = abb_borrar(arbol4, "2");
	print_test("Se borro dato2 y se obtuvo 2", strcmp(dato,"2") == 0);
	print_test("abb_pertenece(arbol4,2) es false",abb_pertenece(arbol4,"2") == false);
	print_test("abb_obtener(arbol4, 2) es NULL",abb_obtener(arbol4, "2") == NULL);
	print_test("La cantidad de arbol4 es 4", abb_cantidad(arbol4) == 4);	
	print_test("Se obtuvo dato3", strcmp(abb_obtener(arbol4, "3"),"3") == 0);
	print_test("abb_pertenece(arbol4,3) es true",abb_pertenece(arbol4,"3") == true);	
	
	//Borro dato8
	dato = abb_borrar(arbol4, "8");
	print_test("Se borro dato8 y se obtuvo 8", strcmp(dato,"8") == 0);
	print_test("abb_pertenece(arbol4,8) es false",abb_pertenece(arbol4,"8") == false);
	print_test("La cantidad de arbol4 es 3", abb_cantidad(arbol4) == 3);	
	print_test("Se obtuvo dato7", strcmp(abb_obtener(arbol4, "7"),"7") == 0);	
	abb_destruir(arbol4);
	print_test("Arbol4 se destruye correctamente", true);	
	
	abb_t* arbol5 = abb_crear(cmp, NULL);
	//dato6	
	se_inserto = abb_guardar(arbol5, "6", dato6);
	print_test("Se intero dato6", se_inserto == true);
	//dato2
	se_inserto = abb_guardar(arbol5, "2", dato2);
	print_test("Se intero dato2", se_inserto == true);
	//dato9
	se_inserto = abb_guardar(arbol5, "9", dato9);
	print_test("Se intero dato9", se_inserto == true);
	//dato8
	se_inserto = abb_guardar(arbol5, "8", dato8);
	print_test("Se intero dato8", se_inserto == true);
	//dato1
	se_inserto = abb_guardar(arbol5, "1", dato1);
	print_test("Se intero dato1", se_inserto == true);
	print_test("La cantidad del arbol5 es 5", abb_cantidad(arbol5) == 5);
	
	//Borro dato2
	dato = abb_borrar(arbol5, "2");
	print_test("Se borro dato2 y se obtuvo 2", strcmp(dato,"2") == 0);
	print_test("abb_pertenece(arbol5,2) es false",abb_pertenece(arbol5,"2") == false);
	print_test("abb_obtener(arbol5, 2) es NULL",abb_obtener(arbol5, "2") == NULL);
	print_test("La cantidad de arbol5 es 4", abb_cantidad(arbol5) == 4);	
	print_test("Se obtuvo dato1", strcmp(abb_obtener(arbol5, "1"),"1") == 0);
	print_test("abb_pertenece(arbol5,1) es true",abb_pertenece(arbol5,"1") == true);	
	
	//Borro dato9
	dato = abb_borrar(arbol5, "9");
	print_test("Se borro dato9 y se obtuvo 9", strcmp(dato,"9") == 0);
	print_test("abb_pertenece(arbol5,9) es false",abb_pertenece(arbol5,"9") == false);
	print_test("abb_obtener(arbol5, 9) es NULL",abb_obtener(arbol5, "9") == NULL);
	print_test("La cantidad de arbol5 es 3", abb_cantidad(arbol5) == 3);		
	abb_destruir(arbol5);
	print_test("Arbol5 se destruye correctamente", true);		
	
	printf("Borrar con 2 hijos en distintas posiciones\n");
	abb_t* arbol6 = abb_crear(cmp, NULL);	
	//dato6	
	se_inserto = abb_guardar(arbol6, "6", dato6);
	print_test("Se intero dato6", se_inserto == true);
	//dato2
	se_inserto = abb_guardar(arbol6, "2", dato2);
	print_test("Se intero dato2", se_inserto == true);
	//dato3
	se_inserto = abb_guardar(arbol6, "3", dato3);
	print_test("Se intero dato3", se_inserto == true);
	//dato8
	se_inserto = abb_guardar(arbol6, "8", dato8);
	print_test("Se intero dato8", se_inserto == true);
	//dato7
	se_inserto = abb_guardar(arbol6, "7", dato7);
	print_test("Se intero dato7", se_inserto == true);
	//dato1
	se_inserto = abb_guardar(arbol6, "1", dato1);
	print_test("Se intero dato1", se_inserto == true);
	//dato9
	se_inserto = abb_guardar(arbol6, "9", dato9);
	print_test("Se intero dato9", se_inserto == true);
	print_test("La cantidad del arbol6 es 7", abb_cantidad(arbol6) == 7);
    
	//Borro dato2
	dato = abb_borrar(arbol6, "2");
	print_test("Se borro dato2 y se obtuvo 2", strcmp(dato,"2") == 0);
	print_test("abb_pertenece(arbol6,aa) es false",abb_pertenece(arbol6,"2") == false);
	print_test("abb_obtener(arbol6, aa) es NULL",abb_obtener(arbol6, "2") == NULL);
	print_test("La cantidad de arbol6 es 6", abb_cantidad(arbol6) == 6);
	
	//Borro dato6
	dato = abb_borrar(arbol6, "6");
	print_test("Se borro dato6 y se obtuvo 6", strcmp(dato,"6") == 0);
	print_test("abb_pertenece(arbol6,6) es false",abb_pertenece(arbol6,"6") == false);
	print_test("abb_obtener(arbol6, aa) es NULL",abb_obtener(arbol6, "6") == NULL);
	print_test("La cantidad de arbol6 es 6", abb_cantidad(arbol6) == 5);	
	
	abb_destruir(arbol6);
	print_test("Arbol6 se destruye correctamente", true);

	free(dato6);
	free(dato2);
	free(dato1);
	free(dato3);
	free(dato8);
	free(dato7);
	free(dato9);
}	

bool imprimir(const char* clave, void* dato, void* extra){
	printf("%s \n", clave);
	return true;
}

void pruebas_iter_interno(){
	abb_t* arbol7 = abb_crear(strcmp, NULL);
	char* dato6 = strdup("6");
	char* dato2 = strdup("2");
	char* dato1 = strdup("1");
	char* dato3 = strdup("3");
	char* dato8 = strdup("8");
	char* dato7 = strdup("7");
	char* dato9 = strdup("9");

	abb_guardar(arbol7, "6", dato6);
	abb_guardar(arbol7, "2", dato2);
	abb_guardar(arbol7, "1", dato1);
	abb_guardar(arbol7, "3", dato3);
	abb_guardar(arbol7, "8", dato8);
	abb_guardar(arbol7, "7", dato7);
	abb_guardar(arbol7, "9", dato9);

	abb_in_order(arbol7, imprimir,NULL);	
	

	free(dato6);
	free(dato2);
	free(dato1);
	free(dato3);
	free(dato8);
	free(dato7);
	free(dato9);

	abb_destruir(arbol7);	
}

void pruebas_iter_externo(){
	abb_t* arbol7 = abb_crear(strcmp, NULL);
	char* dato6 = strdup("2");
	char* dato2 = strdup("1");
	char* dato1 = strdup("3");


	abb_guardar(arbol7, dato6, dato6);
	abb_guardar(arbol7, dato2, dato2);
	abb_guardar(arbol7, dato1, dato1);


	abb_iter_t* iter = abb_iter_in_crear(arbol7);

	while(!abb_iter_in_al_final(iter)){
		const char* clave = abb_iter_in_ver_actual(iter);
		printf("%s\n", clave);
		abb_iter_in_avanzar(iter);
	}

	abb_iter_in_destruir(iter);

	free(dato6);
	free(dato2);
	free(dato1);

	abb_destruir(arbol7);	
}
//*******************************************************************************************************************************

void pruebas_abb_alumno() {
	pruebas_abb_vacio();
	printf("******************************\n");
	pruebas_abb_insertar();
	printf("******************************\n");
	pruebas_abb_borrar();	
    printf("******************************\n");
    pruebas_iter_interno();
    printf("******************************\n");
    pruebas_iter_externo();
}

//*******************************************************************************************************************************

