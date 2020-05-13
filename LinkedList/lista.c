#include "lista.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

/*Se define los struct para la lista, nodos, itedaror externo*/

struct nodo {
	void* dato;
	struct nodo* prox;
};

typedef struct nodo nodo_t;

struct lista {
	nodo_t* primero;	
	size_t largo;
	nodo_t* ultimo; 	
};

struct lista_iter {
	nodo_t* nodo_act;
	nodo_t* nodo_ant;
	lista_t* lista; 
};


/* *****************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/
 
lista_t *lista_crear(void) {
	lista_t* lista = malloc(sizeof(lista_t));
	if (lista == NULL) {
		return NULL;
	}
	lista->primero=NULL;
	lista->ultimo=NULL;  
	lista->largo=0;
	return lista;
}

//*******************************************************************************************

size_t lista_largo(const lista_t *lista) {
	return lista->largo;
}

//*******************************************************************************************

bool lista_esta_vacia(const lista_t *lista) {  	
	return lista_largo(lista) == 0;
}

//*******************************************************************************************

bool lista_insertar_primero(lista_t *lista, void *dato) {
	/*Pido memoria para un nodo y verifico que de ok*/
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo==NULL) {
		return false;
	}
	
	nodo->dato= dato;
	
	/*En caso que la lista este vacia y se agrega el primer elemento*/
	if (lista_esta_vacia(lista)) {
		lista->primero = nodo;
		lista->ultimo = nodo;
		lista->ultimo->prox=NULL;
		lista->largo++;
		return true;
	}
	
	/*En caso que la lista ya contenga elementos*/
	nodo_t* nodo_aux = lista->primero;
	lista->primero = nodo;
	nodo->prox = nodo_aux;
	lista->largo++;
	return true;
}
	
//*******************************************************************************************

bool lista_insertar_ultimo(lista_t *lista, void *dato) {	
	/*Pido memoria para un nodo y verifico que de ok*/
	nodo_t* nodo = malloc(sizeof(nodo_t));
	if (nodo==NULL) {
		return false;
	}
	
	nodo->dato= dato;
	
	/*En caso que la lista este vacia y se agrega el primer elemento*/
	if (lista_esta_vacia(lista)) {
		lista->primero = nodo;
		lista->ultimo = nodo;
		lista->ultimo->prox=NULL;
		lista->largo++;
		return true;
	}
	
	/*En caso que la lista ya contenga elementos*/
	nodo_t* nodo_aux = lista->ultimo;
	lista->ultimo = nodo;
	nodo_aux->prox = nodo;
	lista->ultimo->prox= NULL;
	lista->largo++;
	return true;
}

//*******************************************************************************************

void *lista_borrar_primero(lista_t *lista) {
	/*Veo si la lista esta vacia*/
	if (lista_esta_vacia(lista)) {
		return NULL; 
	}
	
	/*Guardo el dato que voy a devolver*/
	void* dato = lista->primero->dato;
	
	/*En caso que halla un solo elemento*/
	if (lista_largo(lista) == 1) { 
		free(lista->primero);
		lista->primero = NULL;
		lista->ultimo = NULL;
		lista->largo=0;
		return dato;
	}
	
	/*En caso que halla dos o mas elementos*/
	nodo_t* nodo_aux = lista->primero; 
	lista->primero = lista->primero->prox;
	lista->largo--;
	free(nodo_aux);
	return dato; 
}

//*******************************************************************************************

void *lista_ver_primero(const lista_t *lista) {
	/*Veo si la lista esta vacia*/
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	
	/*Si la lista contiene al menos un elemento*/
	return lista->primero->dato;
}	

//*******************************************************************************************

void *lista_ver_ultimo(const lista_t* lista) {
	/*Veo si la lista esta vacia*/
	if (lista_esta_vacia(lista)) {
		return NULL;
	}
	
	/*Si la lista contiene al menos un elemento*/
	return lista->ultimo->dato;
}

//*******************************************************************************************

void lista_destruir(lista_t *lista, void destruir_dato(void *)) {
	/*Recorro todos los nodos para destruirlos*/
	while (lista->primero) {
		nodo_t* nodo_aux = lista->primero;
		void* dato = nodo_aux->dato;
		lista->primero = lista->primero->prox;
		
		/*Verifico que el usuario quiere destruir los datos*/
		if (destruir_dato != NULL) {
			destruir_dato(dato);
		}
		free(nodo_aux);
	} 
	free(lista);
}	
	
/* *****************************************************************
 *               PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

lista_iter_t *lista_iter_crear(lista_t *lista) {
	
	/*Pido memoria al heap y verifico se me la dio bien*/
	lista_iter_t* iter = malloc(sizeof(lista_iter_t)); 
	if (iter == NULL) {
		return NULL;
	}
	
	/*Asigno*/
	iter->lista = lista;
	iter->nodo_act = lista->primero;
	iter->nodo_ant = NULL;
	return iter;	
}

//*******************************************************************************************

bool lista_iter_avanzar(lista_iter_t *iter) {
	/*Verficio si el nodo_act esta en NULL es que se llego al final del TDA*/   
	if (iter->nodo_act == NULL) {
		return false;
	}
	
	/*Avanzo una posicion con nodo_ant y nodo_act del iterador*/
	iter->nodo_ant = iter->nodo_act;
	iter->nodo_act = iter->nodo_act->prox;
	return true;		
}

//*******************************************************************************************

void *lista_iter_ver_actual(const lista_iter_t *iter) {
	/*Verifico si esta en NULL*/
	if (iter->nodo_act == NULL) {
		return NULL;
	}
	
	/*Devuelvo el dato*/
	return iter->nodo_act->dato;
}

//*******************************************************************************************

bool lista_iter_al_final(const lista_iter_t *iter) {
	return iter->nodo_act == NULL;
}

//*******************************************************************************************

void lista_iter_destruir(lista_iter_t *iter) {
	free(iter); 
}

//*******************************************************************************************

bool lista_iter_insertar(lista_iter_t *iter, void *dato) {
	/*En caso que este en la primer posicion del TDA o este vacio*/
	if (iter->nodo_act == iter->lista->primero && iter->nodo_ant == NULL) {
		bool insercion_correcta = lista_insertar_primero(iter->lista, dato);
		if (insercion_correcta == false) {
			return false;
		}
		iter->nodo_act = iter->lista->primero;
		iter->nodo_ant = NULL;
		return true;
	}
	
	/*En caso que este al final*/ 
	if (iter->nodo_act == NULL && iter->nodo_ant != NULL) {
		bool insercion_correcta = lista_insertar_ultimo(iter->lista, dato);
		if (insercion_correcta == false) {
			return false;
		}
		iter->nodo_act = iter->lista->ultimo;
		iter->nodo_ant->prox = iter->nodo_act;
		return true;
	}
	
	
	/*En cualquier otro caso*/
	/*Pido lugar para un nuevo nodo y verifico que de ok*/
	nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
	if (nodo_nuevo == NULL) {
		return false;
	}
	
	/*Asigno el dato*/
	nodo_nuevo->dato = dato;
		
	nodo_nuevo->prox = iter->nodo_act;
	iter->nodo_act = nodo_nuevo;
	iter->nodo_ant->prox = iter->nodo_act;
	iter->lista->largo++;
	return true;
}

//*******************************************************************************************

void *lista_iter_borrar(lista_iter_t *iter) {
	/*Verifico si el TDA esta vacio o si esta al final*/
	if (iter->nodo_act == NULL) {	 
		return NULL;
	}
	
	/*En caso que contenga solo un elemento o este parado en el primer lugar*/ 
	if (iter->nodo_act == iter->lista->primero && iter->nodo_ant == NULL) {
		void* dato = lista_borrar_primero(iter->lista);
		iter->nodo_act = iter->lista->primero;
		iter->nodo_ant = NULL;
		return dato;
	}
	
	//Para otros casos debo hacerlo manual
	/*Guardo la referencia al nodo actual para luego liberarlo*/
	nodo_t* nodo_aux = iter->nodo_act;
	void* dato = iter->nodo_act->dato;
	
	/*En caso en que nodo_act sea el ultimo nodo del TDA*/
	if (iter->nodo_act->prox == NULL) {
		iter->nodo_act = NULL;	
		iter->lista->ultimo = iter->nodo_ant;
		iter->nodo_ant->prox = iter->nodo_act;
	}
			
	/*En otro caso*/
	if (iter->nodo_act != NULL && iter->nodo_ant != NULL) {
		iter->nodo_act = iter->nodo_act->prox;
		iter->nodo_ant->prox = iter->nodo_act;
	}
	
	free(nodo_aux);
	iter->lista->largo--;
	return dato;

}



/* *****************************************************************
 *               PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/



void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra) {
	nodo_t* nodo_actual = lista->primero;
	while (nodo_actual) {
		void* dato = nodo_actual->dato;
		if (visitar(dato, extra)  == false) {
			printf("Se interrumpio el llamado\n");
			return;
		}
		nodo_actual = nodo_actual->prox;
	}	
}










