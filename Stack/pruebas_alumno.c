#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdio.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_pila_vacia(pila_t *pila) {
	/*Verifica que la pila vacia funcione correctamente. Entra como 
	 parametro una pila.*/
	
	printf("Comienzo de pruebas con pila vacia\n");

	/*La funcion pila_esta_vacia(pila) debe devolver true*/
	print_test("La pila esta vacia", pila_esta_vacia(pila) == true);

	/*Las funciones pila_ver_tope(pila_t *pila) y pila_desapilar(pila_t *pila)
	deben devolver NULL*/
	print_test("pila_ver_tope() devuelve NULL", pila_ver_tope(pila) == NULL);
	print_test("pila_desapitar() devuelve NULL", pila_desapilar(pila) == NULL);
}

//********************************************************************************************************************************

void pruebas_apilar_desapilar(pila_t *pila) {
	/*Verifica que la pila pueda apilar y desapilar correctamente. Entra como
	 parametro una pila.*/

	printf("Comienzo de pruebas de apilar y desapilar\n");

	/*Inicializo dos punteros que apunten a distintos valores*/			
	int val1, val2;	
	val1=1;
	val2=2;
	int* x;
	int* y;
	x = &val1;
	y = &val2;

	/*Apilo el 1*/
	pila_apilar(pila, x);
	
	/*Realizo la prueba que el tope cambio*/
	int* tope=pila_ver_tope(pila);
	print_test("El tope es 1", *tope == 1);

	/*Apilo el 2 y verifico que el tope cambio*/
	pila_apilar(pila, y);
	tope = pila_ver_tope(pila);
	print_test("El tope es 2", *tope == 2);

	/*Desapilo y verifico que el tope vuelva a ser 1*/
	pila_desapilar(pila);
	tope = pila_ver_tope(pila);
	print_test("El tope es 1", *tope == 1);

	/*Desapilo y dejo la pila en su estado inicial*/
	pila_desapilar(pila);		
}

//********************************************************************************************************************************

void pruebas_redimensionar(pila_t *pila) {
	/*Verifica que la pila se redimensione correctamete. Entra como
	 parametro una pila*/

	printf("Comienzo de pruebas de redimension\n");

	/*Apilo con un puntero dirigido a el mismo valor hasta llenar
	la pila, el tope vale 1*/
	int val1, val2;	
	val1=1;
	val2=2;
	int* x;
	int* y;
	x = &val1;
	y = &val2;

	for (int i=0; i<10; i++) {
		pila_apilar(pila, x);
	}
	int* tope = pila_ver_tope(pila);
	print_test("La pila esta llena y el tope vale 1", *tope == 1);
	
	/*La pila esta llena ahora pruebo apilar un int* que 
	apunte hacia un valor distinto y corroborar que esta se 
	apilo, lo que significa que se agrando*/
	pila_apilar(pila, y);
	tope = pila_ver_tope(pila);
	print_test("Se redimensiono y el tope vale 2", *tope == 2);

	/*Ahora desapilo hasta tener un 25% de la capacidad que
	seran 5 elementos, pero desapilo todos porque deberia tener
	el mismo resultado y puedo verificar luego que la pila quedo
	como en el estado inicial*/
	for (int i=0; i<11; i++) {
		pila_desapilar(pila);
	}
}

//*******************************************************************************************************************************

void pruebas_pila_alumno() {
	/*Se encarga de correr todas las pruebas necesarias para verificar
	 que la pila funcione correctamente. Llama al resto de las pruebas*/

	printf("Inicio de pruebas con pila\n");

	/*Declaro la pila que voy a utilizar*/
	pila_t* pila = pila_crear();

	/*Veo que se creo correctamente*/
	print_test("Pila inicializada", pila != NULL);

	/*Realizo las pruebas de una pila vacia*/
	pruebas_pila_vacia(pila);
	
	/*Realizo pruebas a apilar y desapilar viendo si se mantiene el 
	 invariante y cuando la pila este vacia se debe comportar como una 
	 pila vacia*/
	pruebas_apilar_desapilar(pila);

	/*Verificando que la pila esta en el estado inicial luego de apilar 
	 y desapilar*/
	printf("Verificando que la pila esta en el estado inicial luego de apilar y desapilar\n");
	pruebas_pila_vacia(pila);

	/*Realizo las pruebas de redimension*/
	pruebas_redimensionar(pila);

	/*Verifico que la pila este como en el estado inicial*/
	printf("Verificando que la pila esta en el estado inicial luego de redimensionar\n");
	pruebas_pila_vacia(pila);

	/*Realizo la prueba de que se apueda apilar NULL*/
	pila_apilar(pila, NULL);
	print_test("Se puede apilar NULL", pila_esta_vacia(pila) == false);

	/*Destruyo la pila*/
	pila_destruir(pila);
	print_test("La pila se destruye", true); 
}

//*******************************************************************************************************************************










