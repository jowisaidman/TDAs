#include "lista.h"
#include "testing.h"
#include <stddef.h> //este que hacia?
#include <stdio.h>
#include <stdlib.h>

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

void pruebas_lista_vacia() {
	/*Verifica que la lista vacia funcione correctamente.*/
	
	printf("Comienzo de pruebas con lista vacia\n");
	
	/*Inicializo la lista que voy a utilizar*/
	lista_t* lista1 = lista_crear();
	
	/*Veo que se creo correctamente*/
	print_test("lista1 inicializada", lista1 != NULL);
	
	/*La funcion lista_esta_vacia(const lista_t *lista) debe devolver true*/
	print_test("lista_esta_vacia(lista1) devuelve true", lista_esta_vacia(lista1) == true);
	
	/*Las funciones lista_ver_primero(lista1), lista_ver_ultimo(lista1) y
	lista_borrar_primero(lista1) deben devolver NULL*/
	print_test("lista_ver_primero(lista1) devuelve NULL", lista_ver_primero(lista1) == NULL);
	print_test("lista_ver_ultimo(lista1) devuelve NULL", lista_ver_ultimo(lista1) == NULL);
	print_test("lista_borrar_primero(lista1) devuelve NULL", lista_borrar_primero(lista1) == NULL);
	
	/*El largo de la lista1 debe ser 0*/
	print_test("lista_largo(lista1) devuelve 0", lista_largo(lista1) == 0);
	
	/*Destruyo la lista1*/
	lista_destruir(lista1, NULL);
	print_test("La lista1 se destruye cuando esta vacia", true); 
	
}

//***********************************************************************************************************

void pruebas_lista_insertar_primero_borrar() {
	
	/*Verfica que se puedan insertar adelante y borrar elementos de 
	cualquier posicion manteniendo los invariantes*/
	printf("Comienzo de pruebas insertar adelante y borrar\n");
	
	/*Inicializo la lista que voy a utilizar*/
	lista_t* lista2 = lista_crear();
	
	/*Inicializo los elementos que voy a insertar*/
	int val1, val2, val3;	
	val1=1;
	val2=2;
	val3=3;
	
	/*Veo que se creo correctamente*/
	print_test("lista2 inicializada", lista2 != NULL);
	
	/*Inserto adelante un elemento*/
	lista_insertar_primero(lista2, &val1);
	
	/*Verifico que la lista no esta vacia*/
	print_test("lista_esta_vacia(lista2) devuelve false luego de insertar adelante 1", lista_esta_vacia(lista2) == false);
	
	/*Verifico que el largo es 1*/
	print_test("lista_largo(lista2) devuelve 1", lista_largo(lista2) == 1);
	
	/*Verifico que ver primero y ver ultimo devuelven 1*/
	int* primer_elemento = lista_ver_primero(lista2);
	int* ultimo_elemento = lista_ver_ultimo(lista2);
	print_test("lista_ver_primero(lista2) devuelve 1", *primer_elemento == 1);
	print_test("lista_ver_ultimo(lista2) devuelve 1", *ultimo_elemento == 1);
	
	/*Inserto adelante un 2do elemento y veo que se mantengan los invariantes y el largo cambie*/
	lista_insertar_primero(lista2, &val2);
	
	/*Verifico que la lista no esta vacia*/
	print_test("lista_esta_vacia(lista2) devuelve false luego de insertar adelante 2", lista_esta_vacia(lista2) == false);
	
	/*Verifico que el largo es 2*/
	print_test("lista_largo(lista2) devuelve 2", lista_largo(lista2) == 2);
	
	/*Verifico que ver primero da 2 y ver ultimo da 1*/
	primer_elemento = lista_ver_primero(lista2);
	ultimo_elemento = lista_ver_ultimo(lista2);
	print_test("lista_ver_primero(lista2) devuelve 2",*primer_elemento == 2);
	print_test("lista_ver_ultimo(lista2) devuelve 1",*ultimo_elemento == 1);
	
	/*Inserto adelante un 3er elemento y veo que se mantengan los invariantes y el largo cambie*/
	lista_insertar_primero(lista2, &val3);
	
	/*Verifico que la lista no esta vacia*/
	print_test("lista_esta_vacia(lista2) devuelve false luego de insertar adelante 3", lista_esta_vacia(lista2) == false);
	
	/*Verifico que el largo es 3*/
	print_test("lista_largo(lista2) devuelve 3", lista_largo(lista2) == 3);
	
	/*Verifico que ver primero da 3 y ver ultimo da 1*/
	primer_elemento = lista_ver_primero(lista2);
	ultimo_elemento = lista_ver_ultimo(lista2);
	print_test("lista_ver_primero(lista2) devuelve 3",*primer_elemento == 3);
	print_test("lista_ver_ultimo(lista2) devuelve 1",*ultimo_elemento == 1);
	
	/*Comienzo a borrar elementos y veo que se mantegan los invariantes y el largo cambie*/
	/*Tambien debe devolver correctamente los elementos*/
	int* dato_obtenido = lista_borrar_primero(lista2);
	print_test("Lista2 devuelve 3 cuando borro",*dato_obtenido == 3);
	print_test("lista_esta_vacia(lista2) devuelve false luego de borrar", lista_esta_vacia(lista2) == false);
	
	/*Verifico que el largo es 2*/
	print_test("lista_largo(lista2) devuelve 2 luego de borrar", lista_largo(lista2) == 2);
	
	/*Veo el primer y ultimo elemento*/
	primer_elemento = lista_ver_primero(lista2);
	ultimo_elemento = lista_ver_ultimo(lista2);
	print_test("lista_ver_primero(lista2) devuelve 2",*primer_elemento == 2);
	print_test("lista_ver_ultimo(lista2) devuelve 1",*ultimo_elemento == 1);
	
	/*Borro otro elemento y chequeo nuevamente*/
	dato_obtenido = lista_borrar_primero(lista2);
	print_test("Lista2 devuelve 2 cuando borro",*dato_obtenido == 2);
	print_test("lista_esta_vacia(lista2) devuelve false luego de borrar", lista_esta_vacia(lista2) == false);
	
	/*Verifico que el largo es 1*/
	print_test("lista_largo(lista2) devuelve 1 luego de borrar", lista_largo(lista2) == 1);

	/*Veo el primer y ultimo elemento*/
	primer_elemento = lista_ver_primero(lista2);
	ultimo_elemento = lista_ver_ultimo(lista2);
	print_test("lista_ver_primero(lista2) devuelve 1",*primer_elemento == 1);
	print_test("lista_ver_ultimo(lista2) devuelve 1",*ultimo_elemento == 1);
	
	/*Dejo la lista vacia, veo que devolvio 1*/
	dato_obtenido = lista_borrar_primero(lista2);
	print_test("Lista2 devuelve 1 cuando borro",*dato_obtenido == 1);
	print_test("lista_esta_vacia(lista2) devuelve true luego de borrar", lista_esta_vacia(lista2) == true);
	
	/*Verifico que el largo es 0*/
	print_test("lista_largo(lista2) devuelve 0 luego de borrar", lista_largo(lista2) == 0);

	/*Veo el primer y ultimo elemento deben dar NULL*/
	primer_elemento = lista_ver_primero(lista2);
	ultimo_elemento = lista_ver_ultimo(lista2);
	print_test("lista_ver_primero(lista2) devuelve NULL",lista_ver_primero(lista2) == NULL);
	print_test("lista_ver_ultimo(lista2) devuelve NULL",lista_ver_ultimo(lista2) == NULL);
	
	/*Destruyo la lista2*/
	lista_destruir(lista2, NULL);
	print_test("La lista2 se destruye cuando esta vacia", true); 

}

//***********************************************************************************************************

void pruebas_lista_insertar_ultimo_borrar() {
	/*Verfica que se puedan insertar atras y borrar elementos de 
	cualquier posicion manteniendo los invariantes*/
	printf("Comienzo de pruebas insertar atras y borrar\n");
	
	/*Inicializo la lista que voy a utilizar*/
	lista_t* lista3 = lista_crear();
	
	/*Inicializo los elementos que voy a insertar*/
	int val1, val2, val3;	
	val1=1;
	val2=2;
	val3=3;
	
	/*Veo que se creo correctamente*/
	print_test("lista3 inicializada", lista3 != NULL);
	
	/*Inserto atras un elemento*/
	lista_insertar_ultimo(lista3, &val1);
	
	/*Verifico que la lista no esta vacia*/
	print_test("lista_esta_vacia(lista3) devuelve false luego de insertar atras 1", lista_esta_vacia(lista3) == false);
	
	/*Verifico que el largo es 1*/
	print_test("lista_largo(lista3) devuelve 1", lista_largo(lista3) == 1);
	
	/*Verifico que ver primero y ver ultimo devuelven 1*/
	int* primer_elemento = lista_ver_primero(lista3);
	int* ultimo_elemento = lista_ver_ultimo(lista3);
	print_test("lista_ver_primero(lista2) devuelve 1", *primer_elemento == 1);
	print_test("lista_ver_ultimo(lista2) devuelve 1", *ultimo_elemento == 1);
	
	/*Inserto atras un 2do elemento y veo que se mantengan los invariantes y el largo cambie*/
	lista_insertar_ultimo(lista3, &val2);
	
	/*Verifico que la lista no esta vacia*/
	print_test("lista_esta_vacia(lista3) devuelve false luego de insertar atras 2", lista_esta_vacia(lista3) == false);
	
	/*Verifico que el largo es 2*/
	print_test("lista_largo(lista3) devuelve 2", lista_largo(lista3) == 2);
	
	/*Verifico que ver primero da 1 y ver ultimo da 2*/
	primer_elemento = lista_ver_primero(lista3);
	ultimo_elemento = lista_ver_ultimo(lista3);
	print_test("lista_ver_primero(lista3) devuelve 1",*primer_elemento == 1);
	print_test("lista_ver_ultimo(lista3) devuelve 2",*ultimo_elemento == 2);
	
	/*Inserto atras un 3er elemento y veo que se mantengan los invariantes y el largo cambie*/
	lista_insertar_ultimo(lista3, &val3);
	
	/*Verifico que la lista no esta vacia*/
	print_test("lista_esta_vacia(lista3) devuelve false luego de insertar atras 3", lista_esta_vacia(lista3) == false);
	
	/*Verifico que el largo es 3*/
	print_test("lista_largo(lista3) devuelve 3", lista_largo(lista3) == 3);
	
	/*Verifico que ver primero da 1 y ver ultimo da 3*/
	primer_elemento = lista_ver_primero(lista3);
	ultimo_elemento = lista_ver_ultimo(lista3);
	print_test("lista_ver_primero(lista3) devuelve 1",*primer_elemento == 1);
	print_test("lista_ver_ultimo(lista3) devuelve 3",*ultimo_elemento == 3);
	
	/*Comienzo a borrar elementos y veo que se mantegan los invariantes y el largo cambie*/
	/*Tambien debe devolver correctamente los elementos*/
	int* dato_obtenido = lista_borrar_primero(lista3);
	print_test("Lista3 devuelve 1 cuando borro",*dato_obtenido == 1);
	print_test("lista_esta_vacia(lista3) devuelve false luego de borrar", lista_esta_vacia(lista3) == false);
	
	/*Verifico que el largo es 2*/
	print_test("lista_largo(lista3) devuelve 2 luego de borrar", lista_largo(lista3) == 2);
	
	/*Veo el primer y ultimo elemento*/
	primer_elemento = lista_ver_primero(lista3);
	ultimo_elemento = lista_ver_ultimo(lista3);
	print_test("lista_ver_primero(lista3) devuelve 2",*primer_elemento == 2);
	print_test("lista_ver_ultimo(lista3) devuelve 3",*ultimo_elemento == 3);
	
	/*Borro otro elemento y chequeo nuevamente*/
	dato_obtenido = lista_borrar_primero(lista3);
	print_test("Lista3 devuelve 2 cuando borro",*dato_obtenido == 2);
	print_test("lista_esta_vacia(lista3) devuelve false luego de borrar", lista_esta_vacia(lista3) == false);
	
	/*Verifico que el largo es 1*/
	print_test("lista_largo(lista3) devuelve 1 luego de borrar", lista_largo(lista3) == 1);

	/*Veo el primer y ultimo elemento*/
	primer_elemento = lista_ver_primero(lista3);
	ultimo_elemento = lista_ver_ultimo(lista3);
	print_test("lista_ver_primero(lista3) devuelve 3",*primer_elemento == 3);
	print_test("lista_ver_ultimo(lista3) devuelve 3",*ultimo_elemento == 3);
	
	/*Dejo la lista vacia, veo que devolvio 3*/
	dato_obtenido = lista_borrar_primero(lista3);
	print_test("Lista3 devuelve 3 cuando borro",*dato_obtenido == 3);
	print_test("lista_esta_vacia(lista3) devuelve true luego de borrar", lista_esta_vacia(lista3) == true);
	
	/*Verifico que el largo es 0*/
	print_test("lista_largo(lista3) devuelve 0 luego de borrar", lista_largo(lista3) == 0);

	/*Veo el primer y ultimo elemento deben dar NULL*/
	primer_elemento = lista_ver_primero(lista3);
	ultimo_elemento = lista_ver_ultimo(lista3);
	print_test("lista_ver_primero(lista3) devuelve NULL",lista_ver_primero(lista3) == NULL);
	print_test("lista_ver_ultimo(lista3) devuelve NULL",lista_ver_ultimo(lista3) == NULL);
	
	/*Destruyo la lista3*/
	lista_destruir(lista3, NULL);
	print_test("La lista3 se destruye cuando esta vacia", true); 

	
	
}

//***********************************************************************************************************

void pruebas_lista_con_null() {
	/*Realizo la prueba de que se pueda insertar NULL y la lista funcione correctamente*/
	
	printf("Verificando que se pueda insertar NULL\n");
	
	/*Inicializo una nueva lista*/
	lista_t* lista4 = lista_crear();
	
	/*Veo que se creo correctamente*/
	print_test("lista4 inicializada", lista4 != NULL);
	
	/*Inserto NULL*/
	lista_insertar_primero(lista4, NULL);
	print_test("El primer elemento de lista4 es NULL", lista_ver_primero(lista4) == NULL);
	print_test("El ultimo elemento de lista4 es NULL", lista_ver_primero(lista4) == NULL);
	
	/*Verifico que la lista no esta vacia luego de insertar NULL*/
	print_test("La lista4 no esta vacia luego de insertar NULL", lista_esta_vacia(lista4) == false);
	

	/*Borro NULL y veo que lo devuelva bien*/
	print_test("Cuando borro devuelve NULL", lista_borrar_primero(lista4) == NULL);		
	
	/*Veo que funcione como una lista vacia*/
	print_test("La lista4 esta vacia", lista_esta_vacia(lista4) == true);

	/*Las funciones lista_ver_primero(lista4) lista_ver_ultimo(lista4) y 
	lista_borrar_primer(lista4) deben devolver NULL*/
	print_test("lista_ver_primero(lista4) devuelve NULL", lista_ver_primero(lista4) == NULL);
	print_test("lista_ver_ultimo(lista4) devuelve NULL", lista_ver_ultimo(lista4) == NULL);
	print_test("lista_borrar_primero(lista4) devuelve NULL", lista_borrar_primero(lista4) == NULL);
	
	/*Destruyo lista4 destruyo*/	
	print_test("La lista4 se destruye cuando esta vacia", true); 
	lista_destruir(lista4,NULL);
}

//***********************************************************************************************************

void destruir_dato(void* dato) {
	free(dato);
}

//***********************************************************************************************************

void pruebas_destruir_lista_con_elementos() {
	printf("Verificando que se destruye una lista que tenga datos en el heap\n");

	/*Creo una nueva lista*/
	lista_t* lista5 = lista_crear();

	/*Veo que se creo correctamente*/
	print_test("lista5 inicializada", lista5 != NULL);
	
	/*Inicializo dos punteros con datos en el heap*/
	int* x = malloc(sizeof(int));
	int* y = malloc(sizeof(int));
	*x=1;
	*y=2;
	
	/*Inserto los datos*/
	lista_insertar_primero(lista5, x);
	int* primer_elemento = lista_ver_primero(lista5);
	int* ultimo_elemento = lista_ver_ultimo(lista5);
	print_test("El primero de lista5 es 1", *primer_elemento == 1);
	print_test("El ultimo de lista5 es 1", *ultimo_elemento == 1);
	lista_insertar_primero(lista5, y);
	primer_elemento = lista_ver_primero(lista5);
	ultimo_elemento = lista_ver_ultimo(lista5);
	print_test("El primero de lista5 es 2", *primer_elemento == 2);
	print_test("El ultimo de lista5 es 1", *ultimo_elemento == 1);
	
	/*Verifico que la lista no esta vacia*/
	print_test("La lista5 no esta vacia", lista_esta_vacia(lista5) == false);
	
	
	/*Los destruyo pasando una funcion como parametro*/	
	
	lista_destruir(lista5,destruir_dato);
	print_test("La lista5 se destruye cuando contiene datos y libera los mismos", true); 	
}

//***********************************************************************************************************

void pruebas_iterador_vacio() {
	/*Veo que una lista con un iterador vacio funcione correctamente*/
	printf("Comienzo de pruebas de lista vacia con un iterador funcione correctamente\n");
	
	/*Creo lista6*/
	lista_t* lista6 = lista_crear();
	
	/*Veo que se creo correctamente*/
	print_test("lista6 inicializada", lista6 != NULL);
	
	/*Inicializo un iterador para la lista6*/
	lista_iter_t* iterador1 = lista_iter_crear(lista6);
	
	/*Veo que se inicializo correctamente*/
	print_test("iterador1 de lista6 inicializado", iterador1 != NULL);
	
	/*Avanzar debe dar false*/
	print_test("lista_iter_avanzar() debe devolver false", lista_iter_avanzar(iterador1) == false);
	
	/*Ver actual debe dar NULL*/
	print_test("lista_iter_ver_actual(iterador1) debe devolver NULL", lista_iter_ver_actual(iterador1) == NULL);
	
	/*Esta alfinal debe dar true*/
	print_test("lista_iter_al_final(iterador1) debe dar true",lista_iter_al_final(iterador1) == true);
	
	/*Borrar debe devolver NULL*/
	print_test("lista_iter_borrar(iterador1) debe devolver NULL",lista_iter_borrar(iterador1) == NULL);
	
	/*Destruyo el iterador y la lista*/
	lista_iter_destruir(iterador1);
	lista_destruir(lista6,NULL);
	print_test("La lista6 se destruye", true);
	print_test("La iterador1 se destruye", true);	
}

//***********************************************************************************************************

void pruebas_iterador_insertar_borrar() {
	printf("Comienzo de pruebas de insertar y borrar en la lista con un iterador externo\n");

	/*Creo lista7*/
	lista_t* lista7 = lista_crear();
	
	/*Veo que se creo correctamente*/
	print_test("lista7 inicializada", lista7 != NULL);
	
	/*Inicializo un iterador2 para la lista6*/
	lista_iter_t* iterador2 = lista_iter_crear(lista7);
	
	/*Veo que se inicializo correctamente*/
	print_test("iterador2 de lista7 inicializado", iterador2 != NULL);
	
	/*Defino los datos que voy a utilizar*/
	int val1, val2, val3, val4, val5;	
	val1=1;
	val2=2;
	val3=3;
	val4=4;
	val5=5;
	
	/*Inserto un val1 y verifico que se inserto al comienzo y que las primitivas
	 de la lista e iterador devuelven resultados coherentes*/
	bool insercion_correcta= lista_iter_insertar(iterador2, &val1);
	print_test("insercion correcta", insercion_correcta == true);
	int* dato_actual = lista_iter_ver_actual(iterador2);
	int* primer_elemento = lista_ver_primero(lista7);
	int* ultimo_elemento = lista_ver_ultimo(lista7);
	print_test("lista_iter_ver_actual(iterador2) debe dar 1",*dato_actual == 1);
	print_test("lista_iter_al_final(iterador2) debe dar false", lista_iter_al_final(iterador2) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 1",lista_largo(lista7) == 1);
	print_test("lista_ver_primero(lista7) debe ser 1", *primer_elemento == 1);
	print_test("lista_ver_ultimo(lista7) debe ser 1", *ultimo_elemento == 1);
	
	/*Inserto val2 al comienzo y verifico que los invariantes se mantengan y los
	resultados sean coherentes*/
	lista_iter_insertar(iterador2, &val2);
	dato_actual = lista_iter_ver_actual(iterador2);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);	
	print_test("lista_iter_ver_actual(iterador2) debe dar 2",*dato_actual == 2);
	print_test("lista_iter_al_final(iterador2) debe dar false", lista_iter_al_final(iterador2) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 2",lista_largo(lista7) == 2);
	print_test("lista_ver_primero(lista7) debe ser 2", *primer_elemento == 2);
	print_test("lista_ver_ultimo(lista7) debe ser 1", *ultimo_elemento == 1);

	/*Inserto val3 al comienzo y verifico que los invariantes se mantengan y los
	resultados sean coherentes*/
	lista_iter_insertar(iterador2, &val3);
	dato_actual = lista_iter_ver_actual(iterador2);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);	
	print_test("lista_iter_ver_actual(iterador2) debe dar 3",*dato_actual == 3);
	print_test("lista_iter_al_final(iterador2) debe dar false", lista_iter_al_final(iterador2) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 3",lista_largo(lista7) == 3);
	print_test("lista_ver_primero(lista7) debe ser 3", *primer_elemento == 3);
	print_test("lista_ver_ultimo(lista7) debe ser 1", *ultimo_elemento == 1);
	
	/*Avanzo una posicion e inserto val4, verifico que los invariantes 
	se mantengan y que los resultados sean coherentes*/
	lista_iter_avanzar(iterador2);
	lista_iter_insertar(iterador2, &val4);
	dato_actual = lista_iter_ver_actual(iterador2);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);		
	print_test("lista_iter_ver_actual(iterador2) debe dar 4", *dato_actual == 4);
	print_test("lista_iter_al_final(iterador2) debe dar false", lista_iter_al_final(iterador2) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 4",lista_largo(lista7) == 4);
	print_test("lista_ver_primero(lista7) debe ser 3", *primer_elemento == 3);
	print_test("lista_ver_ultimo(lista7) debe ser 1", *ultimo_elemento == 1);
	
	/*Avanzo hasta el final de todo e inserto val 5, verifico que los invariantes 
	se mantengan y que los resultados sean coherentes*/
	lista_iter_avanzar(iterador2);
	dato_actual = lista_iter_ver_actual(iterador2);
	print_test("lista_iter_ver_actual(iterador2) debe dar 2", *dato_actual == 2);
	lista_iter_avanzar(iterador2);
	dato_actual = lista_iter_ver_actual(iterador2);
	print_test("lista_iter_ver_actual(iterador2) debe dar 1", *dato_actual == 1);
	lista_iter_avanzar(iterador2);
	print_test("lista_iter_ver_actual(iterador2) debe dar NULL", lista_iter_ver_actual(iterador2) == NULL);
	print_test("lista_iter_al_final(iterador2) debe dar true", lista_iter_al_final(iterador2) == true);
	
	/*Inserto val5*/
	lista_iter_insertar(iterador2, &val5);
	dato_actual = lista_iter_ver_actual(iterador2);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);	
	print_test("lista_iter_ver_actual(iterador2) debe dar 5", *dato_actual == 5);
	print_test("lista_iter_al_final(iterador2) debe dar false", lista_iter_al_final(iterador2) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 5",lista_largo(lista7) == 5);
	print_test("lista_ver_primero(lista7) debe ser 3", *primer_elemento == 3);
	print_test("lista_ver_ultimo(lista7) debe ser 5", *ultimo_elemento == 5);
	
	/*Borro el val5 con este iterador, verifico que los resultados sean coherentes.
	Luego lo destruyo y creo uno nuevo iterador3 para lista7*/
	int* dato_devuelto = lista_iter_borrar(iterador2);
	print_test("lista_iter_borrar(iterador2) devolvio 5", *dato_devuelto == 5);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);	
	print_test("lista_iter_ver_actual(iterador2) debe dar NULL", lista_iter_ver_actual(iterador2) == NULL);
	print_test("lista_iter_al_final(iterador2) debe dar true", lista_iter_al_final(iterador2) == true);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 4",lista_largo(lista7) == 4);
	print_test("lista_ver_primero(lista7) debe ser 3", *primer_elemento == 3);
	print_test("lista_ver_ultimo(lista7) debe ser 1", *ultimo_elemento == 1);
	lista_iter_destruir(iterador2);
	print_test("iterador2 destruido", true);
	
	lista_iter_t* iterador3 = lista_iter_crear(lista7);
	
	/*Veo que se inicializo correctamente*/
	print_test("iterador3 de lista7 inicializado", iterador3 != NULL);
	
	/*Veo que este en el lugar correcto y que los invariantes estan bien*/
	dato_actual = lista_iter_ver_actual(iterador3);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);	
	print_test("lista_iter_ver_actual(iterador3) debe dar 3", *dato_actual == 3);
	print_test("lista_iter_al_final(iterador3) debe dar false", lista_iter_al_final(iterador3) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 4",lista_largo(lista7) == 4);
	print_test("lista_ver_primero(lista7) debe ser 3", *primer_elemento == 3);
	print_test("lista_ver_ultimo(lista7) debe ser 1", *ultimo_elemento == 1);
	
	/*Remuevo el primer elemento y veo que se mantengan los invariantes*/
	dato_devuelto = lista_iter_borrar(iterador3);
	print_test("lista_iter_borrar(iterador3) devolvio 3", *dato_devuelto == 3);
	dato_actual = lista_iter_ver_actual(iterador3);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);	
	print_test("lista_iter_ver_actual(iterador3) debe dar 4", *dato_actual == 4);
	print_test("lista_iter_al_final(iterador3) debe dar false", lista_iter_al_final(iterador3) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 3",lista_largo(lista7) == 3);
	print_test("lista_ver_primero(lista7) debe ser 4", *primer_elemento == 4);
	print_test("lista_ver_ultimo(lista7) debe ser 1", *ultimo_elemento == 1);
	
	/*Avanzo una posicion y remuevo en el medio*/
	lista_iter_avanzar(iterador3);
	dato_actual = lista_iter_ver_actual(iterador3);
	print_test("lista_iter_ver_actual(iterador3) debe dar 2", *dato_actual == 2);
	dato_devuelto = lista_iter_borrar(iterador3);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);	
	dato_actual = lista_iter_ver_actual(iterador3);
	print_test("lista_iter_borrar(iterador3) devolvio 2", *dato_devuelto == 2);
	print_test("lista_iter_ver_actual(iterador3) debe dar 1", *dato_actual == 1);
	print_test("lista_iter_al_final(iterador3) debe dar false", lista_iter_al_final(iterador3) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 2",lista_largo(lista7) == 2);
	print_test("lista_ver_primero(lista7) debe ser 4", *primer_elemento == 4);
	print_test("lista_ver_ultimo(lista7) debe ser 1", *ultimo_elemento == 1);
	
	/*Borro el ultimo elemento y veo que se mantengan los invariantes y este al final
	de la lista el iterador3*/
	dato_devuelto = lista_iter_borrar(iterador3);
	print_test("lista_iter_borrar(iterador3) devolvio 1", *dato_devuelto == 1);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);
	print_test("lista_iter_ver_actual(iterador3) debe dar NULL", lista_iter_ver_actual(iterador3) == NULL);
	print_test("lista_iter_al_final(iterador3) debe dar true", lista_iter_al_final(iterador3) == true);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 1",lista_largo(lista7) == 1);
	print_test("lista_ver_primero(lista7) debe ser 4", *primer_elemento == 4);
	print_test("lista_ver_ultimo(lista7) debe ser 4", *ultimo_elemento == 4);
	
	/*Destruyo el iterador3 y creo un ultimo iterador para la lista*/
	lista_iter_destruir(iterador3);
	print_test("iterador3 destruido", true);
	
	lista_iter_t* iterador4 = lista_iter_crear(lista7);
	
	/*Veo que se inicializo correctamente*/
	print_test("iterador3 de lista7 inicializado", iterador4 != NULL);
	primer_elemento = lista_ver_primero(lista7);
	ultimo_elemento = lista_ver_ultimo(lista7);	
	dato_actual = lista_iter_ver_actual(iterador4);
	print_test("lista_iter_ver_actual(iterador4) debe dar 4", *dato_actual == 4);
	print_test("lista_iter_al_final(iterador4) debe dar false", lista_iter_al_final(iterador4) == false);
	print_test("lista_esta_vacia(lista7) debe ser false", lista_esta_vacia(lista7) == false);
	print_test("lista_largo(lista7) debe ser 1",lista_largo(lista7) == 1);
	print_test("lista_ver_primero(lista7) debe ser 4", *primer_elemento == 4);
	print_test("lista_ver_ultimo(lista7) debe ser 4", *ultimo_elemento == 4);
	
	/*Borro el dato actual y veo que el iterador se comporte como en una lista vacia*/
	dato_devuelto = lista_iter_borrar(iterador4);
	print_test("lista_iter_borrar(iterador4) devolvio 1", *dato_devuelto == 4);
	print_test("lista_iter_ver_actual(iterador4) debe dar NULL", lista_iter_ver_actual(iterador4) == NULL);
	print_test("lista_iter_al_final(iterador4) debe dar true", lista_iter_al_final(iterador4) == true);
	print_test("lista_esta_vacia(lista7) debe ser true", lista_esta_vacia(lista7) == true);
	print_test("lista_largo(lista7) debe ser 0",lista_largo(lista7) == 0);
	print_test("lista_ver_primero(lista7) debe ser NULL", lista_ver_primero(lista7) == NULL);
	print_test("lista_ver_ultimo(lista7) debe ser NULL", lista_ver_ultimo(lista7) == NULL);
	
	/*Destruyo la lista7 y el iterador4*/
	lista_iter_destruir(iterador4);
	lista_destruir(lista7,NULL);
	print_test("iterador4 destruido", true);
	print_test("lista7 destruida",true);
	
}

bool guardar_maximo(void* dato, void* extra) {
	int num1 = *(int*)dato;
	int num2 = *(int*)extra;
	if (num1>num2) {
		*(int*)extra = num1;
	}
	return true; 
}



void prueba_iterador_interno_duplicar() {
	//Creo una nueva lista
	lista_t* lista8 = lista_crear();
	
	//Veo que se creo correctamente
	print_test("lista8 inicializada", lista8 != NULL);
	
	//Agrego datos a la lista
	int val1, val2, val3, val4, val5;	
	val1=-1;
	val2=2;
	val3=8;
	val4=4;
	val5=80;
	lista_insertar_primero(lista8, &val1);
	lista_insertar_primero(lista8, &val2);
	lista_insertar_primero(lista8, &val3);	
	lista_insertar_primero(lista8, &val4);	
	lista_insertar_primero(lista8, &val5);	
	
	//Aplico el iterador interno
	print_test("Entro al it interno, busco el maximo", true);
	int* maximo = malloc(sizeof(int*));
	free(maximo);
	maximo = lista_ver_primero(lista8);
	lista_iterar(lista8, guardar_maximo, maximo);
	print_test("El maximo obtenido es 8", *maximo==80);
	lista_borrar_primero(lista8);
	lista_borrar_primero(lista8);
	lista_borrar_primero(lista8);
	lista_borrar_primero(lista8);
	lista_borrar_primero(lista8);
	lista_destruir(lista8,NULL);

	
}


void pruebas_lista_alumno(void) {
	pruebas_lista_vacia();
	pruebas_lista_insertar_primero_borrar();
	pruebas_lista_insertar_ultimo_borrar();
	pruebas_lista_con_null();
	pruebas_destruir_lista_con_elementos();
	
	printf("**************************************************************************\n");
	printf("Comienzo de pruebas con iterador externo\n");
	
	pruebas_iterador_vacio();
	pruebas_iterador_insertar_borrar();
	
	printf("**************************************************************************\n");
	printf("Comienzo de pruebas con iterador interno\n");
	prueba_iterador_interno_duplicar();
	
	printf("Fin de pruebas\n");
}
	






















































































































