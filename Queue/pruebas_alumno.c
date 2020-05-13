#include "cola.h"
#include "testing.h"
#include <stddef.h> 
#include <stdio.h>
#include <stdlib.h>


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_cola_vacia() {
	/*Verifica que la cola vacia funcione correctamente. Entra como 
	 parametro una cola.*/
	
	printf("Comienzo de pruebas con cola vacia\n");
	
	/*Inicializo la cola que voy a utilizar*/
	cola_t* cola1 = cola_crear();

	/*Veo que se creo correctamente*/
	print_test("Cola1 inicializada", cola1 != NULL);
	

	/*La funcion cola_esta_vacia(const cola_t *cola) debe devolver true*/
	print_test("La cola1 esta vacia", cola_esta_vacia(cola1) == true);

	/*Las funciones cola_ver_primero(const cola_t *cola) y cola_desencolar(cola_t *cola)
	deben devolver NULL*/
	print_test("cola_ver_primero(cola1) devuelve NULL", cola_ver_primero(cola1) == NULL);
	print_test("cola_desencolar(cola1) devuelve NULL", cola_desencolar(cola1) == NULL);

	/*Destruyo la cola vacia*/
	cola_destruir(cola1, NULL);
	print_test("La cola1 se destruye cuando esta vacia", true); 
	
}

//********************************************************************************************************************************

void pruebas_encolar_desencolar() {
	/*Verifica que la cola pueda encolar y desencolar correctamente. Entra como
	 parametro una cola.*/

	printf("Comienzo de pruebas de encolar y desencolar\n");
	
	/*Inicializo cola*/
	cola_t* cola2 = cola_crear();
	
	/*Veo que se creo correctamente*/
	print_test("Cola2 inicializada", cola2 != NULL);

	/*Inicializo dos punteros que apunten a distintos valores*/			
	int val1, val2;	
	val1=1;
	val2=2;
	int* x;
	int* y;
	x = &val1;
	y = &val2;

	/*encolo el 1*/
	cola_encolar(cola2, x);
	
	/*Realizo la prueba que el primero cambio*/
	int* primer_elemento = cola_ver_primero(cola2);
	print_test("Encolo 1 y el primero de cola2 es 1", *primer_elemento == 1);
	
	/*Verifico que la cola2 no esta vacia*/
	print_test("La cola2 no esta vacia luego de encolar", cola_esta_vacia(cola2) == false);	
	
	/*Encolo el 2 y verifico que el primero no cambio*/
	cola_encolar(cola2, y);
	primer_elemento = cola_ver_primero(cola2);
	print_test("Encolo 2 y el primero de cola2 es 1", *primer_elemento == 1);
	
	/*Desencolo y verifico que devuelva 1 y el primero sea 2*/
	int* dato_obtenido = cola_desencolar(cola2);
	print_test("Cola2 devuelve 1 cuando desencolo",*dato_obtenido == 1);
	
	primer_elemento = cola_ver_primero(cola2);
	print_test("El primero de cola2 es 2", *primer_elemento == 2);

	/*Desencolo y dejo la cola en su estado inicial, verifico que 
	devuelva 2*/
	dato_obtenido = cola_desencolar(cola2);		
	print_test("Cola2 devuelve 2 cuando desencolo",*dato_obtenido == 2);

	/*Verificando que la cola esta en el estado inicial luego de encolar 
	 y desencolar*/
	printf("Verificando que la cola esta en el estado inicial luego de encolar y desencolar\n");
	
	/*La cola2 esta vacia*/
	print_test("La cola2 esta vacia", cola_esta_vacia(cola2) == true);

	/*Las funciones cola_ver_primero(const cola_t *cola) y cola_desencolar(cola_t *cola)
	deben devolver NULL*/
	print_test("cola_ver_primero(cola2) devuelve NULL", cola_ver_primero(cola2) == NULL);
	print_test("cola_desencolar(cola2) devuelve NULL", cola_desencolar(cola2) == NULL);

	/*Destruyo la cola vacia*/
	cola_destruir(cola2, NULL);
	print_test("La cola2 se destruye cuando esta vacia", true); 
	
	
	
}


//********************************************************************************************************************************

void destruir_dato(void* dato) {
	free(dato);
}

//********************************************************************************************************************************

void pruebas_destruir_cola_con_elementos() {
	printf("Verificando que se destruye una cola que tenga datos en el heap\n");

	/*Creo una nueva cola*/
	cola_t* cola4 = cola_crear();

	/*Veo que se creo correctamente*/
	print_test("Cola4 inicializada", cola4 != NULL);
	
	/*Inicializo dos punteros con datos en el heap*/
	int* x = malloc(sizeof(int));
	int* y = malloc(sizeof(int));
	*x=1;
	*y=2;
	
	/*Encolo los datos*/
	cola_encolar(cola4, x);
	int* primer_elemento = cola_ver_primero(cola4);
	print_test("El primero de cola4 es 1", *primer_elemento == 1);
	cola_encolar(cola4, y);
	primer_elemento = cola_ver_primero(cola4);
	print_test("El primero de cola4 es 1", *primer_elemento == 1);
	
	/*Verifico que la cola no esta vacia*/
	print_test("La cola4 no esta vacia", cola_esta_vacia(cola4) == false);
	
	
	/*Los destruyo*/	
	
	cola_destruir(cola4,destruir_dato);
	print_test("La cola4 se destruye cuando contiene datos y libera los mismos", true); 
	
}
//********************************************************************************************************************************
void pruebas_con_null() {
	/*Realizo la prueba de que se pueda encolar NULL y la cola funcione correctamente*/
	
	printf("Verificando que se pueda encolar NULL\n");
	
	/*Inicializo una nueva cola*/
	cola_t* cola3 = cola_crear();
	
	/*Veo que se creo correctamente*/
	print_test("Cola3 inicializada", cola3 != NULL);
	
	/*Encolo NULL*/
	cola_encolar(cola3, NULL);
	print_test("Se puede encolar NULL", cola_ver_primero(cola3) == NULL);
	
	/*Verifico que la cola no esta vacia luego de apilar NULL*/
	print_test("La cola3 no esta vacia luego de encolar NULL", cola_esta_vacia(cola3) == false);
	
	/*Verifico que el primer elemento es NULL*/
	print_test("El primer elemento de cola3 es NULL", cola_ver_primero(cola3) == NULL);
	
	/*Desencolo NULL y veo que lo devuelva bien*/
	print_test("Cuando desencolo devuelve NULL", cola_desencolar(cola3) == NULL);		
	
	/*Veo que funcione como una cola vacia*/
	print_test("La cola3 esta vacia", cola_esta_vacia(cola3) == true);

	/*Las funciones cola_ver_primero(const cola_t *cola) y cola_desencolar(cola_t *cola)
	deben devolver NULL*/
	print_test("cola_ver_primero(cola3) devuelve NULL", cola_ver_primero(cola3) == NULL);
	print_test("cola_desencolar(cola3) devuelve NULL", cola_desencolar(cola3) == NULL);
	
	/*Destruyo cola4 destruyo*/	
	print_test("La cola3 se destruye cuando esta vacia", true); 
	cola_destruir(cola3,destruir_dato);
}

//********************************************************************************************************************************
void pruebas_cola_alumno() {
	/*Se encarga de correr todas las pruebas necesarias para verificar
	 que la cola funcione correctamente. Llama al resto de las pruebas*/

	printf("Inicio de pruebas con cola\n");
	
	/*Realizo las pruebas con cola vacia*/
	pruebas_cola_vacia();
	
	/*Realizo pruebas a encolar viendo si se mantiene el invariante */
	pruebas_encolar_desencolar();

	/*Realizo pruebas de encolar y desencolar null*/
	pruebas_con_null();
	
	/*Creo nuevamente una cola y le encolo datos que esten en el heap */
	pruebas_destruir_cola_con_elementos();

}

//*******************************************************************************************************************************










