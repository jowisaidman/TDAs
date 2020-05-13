#define _XOPEN_SOURCE 500
#include "abb.h"
#include "pila.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definicion de los structs para abb y abb_nodo
typedef struct abb_nodo{
    struct abb_nodo *izq;
    struct abb_nodo *der;
    char *clave;
    void *dato;
} abb_nodo_t;

struct abb {
	abb_nodo_t* raiz;
	abb_comparar_clave_t cmp;
	abb_destruir_dato_t destruir_dato;
	size_t cantidad;		
};

//Funciones Auxiliares
//***********************************************************************
//Recive como parametro una clave y un dato y crea un nodo.
//Devuelve NULL en casa de error.
abb_nodo_t* nodo_abb_crear(char* clave, void* valor) {
	abb_nodo_t* nodo_act = malloc(sizeof(abb_nodo_t));
	if (!nodo_act) return NULL;
	nodo_act->clave = clave;
	nodo_act->dato = valor;
	nodo_act->izq = NULL;
	nodo_act->der = NULL; 
	return nodo_act;		
}
//***********************************************************************
//Recive como parametro un nodo y una funcion destruir dato y se encarga
//de destruir el nodo.
void destruir_nodo_abb(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato) {
	if (nodo == NULL) return;
	if (destruir_dato != NULL) destruir_dato(nodo->dato);
	free(nodo->clave);
	free(nodo);	
}
//***********************************************************************
//Recive como parametro un arbol, un nodo_cmp que cuando se llame la funcion
//incialmente sera NULL, un nodo_ubicar que sera el nodo al cual se le quiere
//buscar el padre y un nodo padre que inicialmente sera NULL. Busca el padre de
//nodo_ubicar. Devuelve NULL si no tiene padre o no se encuentra el nodo en el arbol.
//Pre: Cuando se llama a la funcion nodo_cmp y padre son NULL.
abb_nodo_t* buscar_padre(abb_t* arbol, abb_nodo_t* nodo_cmp, abb_nodo_t* nodo_ubicar,abb_nodo_t* padre) {
	if (arbol->raiz == NULL) {
		return NULL;
	}
	int ubicar_es_mayor;
	if (padre == NULL) {
		ubicar_es_mayor = arbol->cmp(arbol->raiz->clave, nodo_ubicar->clave);
		if(ubicar_es_mayor > 0) {
			return buscar_padre(arbol, arbol->raiz->izq, nodo_ubicar, arbol->raiz);
		}
		if (ubicar_es_mayor < 0) {
			return buscar_padre(arbol, arbol->raiz->der, nodo_ubicar, arbol->raiz);
		}
		if (ubicar_es_mayor == 0) return NULL;
	}
	
	if (nodo_cmp != NULL) {
		ubicar_es_mayor= arbol->cmp(nodo_cmp->clave, nodo_ubicar->clave);
		if (ubicar_es_mayor > 0) {
			return buscar_padre(arbol, nodo_cmp->izq,nodo_ubicar,nodo_cmp);
		}
		if (ubicar_es_mayor < 0) {
			return buscar_padre(arbol, nodo_cmp->der,nodo_ubicar,nodo_cmp);
		}
	}
	return padre;
}
//***********************************************************************
//Recive como parametro una clave, un nodo_act que cuando se llama por primera vez a la
//funcion sera NULL y una f_cmp que sera la funcion para comparar nodos. Busca el nodo que 
//tenga la clave que se paso como parametro Devuelve NULL en caso de que no se encuentre el 
//nodo en el arbol.
//Pre: nodo_act sera NULL el primer llamado
abb_nodo_t* buscar_nodo(const char* clave,abb_nodo_t* nodo_act,abb_comparar_clave_t f_cmp) {;
	if (nodo_act == NULL) return NULL;
	int cmp = f_cmp(nodo_act->clave, clave);
	if (cmp == 0) {
		return nodo_act;
	}
	if (cmp > 0) { 
		return buscar_nodo(clave,nodo_act->izq,f_cmp);
	}
	return buscar_nodo(clave,nodo_act->der,f_cmp);	
}
//***********************************************************************
//Itera sobre todo el arbol en post orden. Se utiliza para destruir el arbol. f
//es la funcion que destruye los nodos.
//Pre: Destruir_dato es la funcion que se utiliza para destruir los datos de los nodos
void abb_iterar(abb_nodo_t* nodo_act, abb_destruir_dato_t destruir_dato,void f(abb_nodo_t* nodo, abb_destruir_dato_t destruir_dato)) {
	if (nodo_act == NULL) return;
	abb_iterar(nodo_act->izq,destruir_dato,f);
	abb_iterar(nodo_act->der,destruir_dato,f);
	f(nodo_act,destruir_dato);
}
//***********************************************************************
//Busca el sucesor de un nodo. Devuelve NULL si no tiene sucesor.
abb_nodo_t* buscar_sucesor(abb_nodo_t* nodo_ubicar_sucesor,abb_nodo_t* nodo_act) {
	if (nodo_ubicar_sucesor == NULL) return NULL;
	if (nodo_act == NULL) {
		if (nodo_ubicar_sucesor->der == NULL) return NULL;
		return buscar_sucesor(nodo_ubicar_sucesor,nodo_ubicar_sucesor->der);
	}
	if (nodo_act->izq != NULL) {
		return buscar_sucesor(nodo_ubicar_sucesor,nodo_act->izq);
	}
	return nodo_act;
}
//***********************************************************************
//Realiza un swap de los nodos.
//Pre: nodo1, nodo2 y arbol != NULL
void swap_abb_nodos(abb_nodo_t** nodo1_p, abb_nodo_t** nodo2_p, abb_t* arbol) {
	char* clave_aux = (*nodo1_p)->clave;
	void* dato_aux = (*nodo1_p)->dato;
	(*nodo1_p)->clave = (*nodo2_p)->clave;
	(*nodo1_p)->dato = (*nodo2_p)->dato;
	(*nodo2_p)->clave = clave_aux;
	(*nodo2_p)->dato = dato_aux;
}
/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato) {
	abb_t* arbol = malloc(sizeof(abb_t));
	if (arbol == NULL) return NULL;
	arbol->raiz=NULL; 
	arbol->cmp = cmp;
	arbol->destruir_dato = destruir_dato;
	arbol->cantidad = 0;
	return arbol;
}

//**********************************************************************

size_t abb_cantidad(abb_t *arbol) {
	return arbol->cantidad;
}

//**********************************************************************

bool abb_guardar(abb_t *arbol, const char *key, void *dato) {
	if (abb_pertenece(arbol,key)) {
		abb_nodo_t* nodo = buscar_nodo(key,arbol->raiz,arbol->cmp);
		if (arbol->destruir_dato != NULL) arbol->destruir_dato(nodo->dato);
		nodo->dato = dato;
		return true;
	}
	char* clave = strdup(key);
	abb_nodo_t* nodo_act = nodo_abb_crear(clave, dato);
	if (!nodo_act) return false;
	abb_nodo_t* padre = buscar_padre(arbol, NULL, nodo_act, NULL);
	if (padre == NULL) {
		arbol->raiz = nodo_act;
		arbol->cantidad++;
		return true;
	}
	int hijo_es_mayor = arbol->cmp(padre->clave,nodo_act->clave);
	if (hijo_es_mayor < 0) {
		destruir_nodo_abb(padre->der,arbol->destruir_dato);
		padre->der = nodo_act;
		arbol->cantidad++;
		return true;
	}
	destruir_nodo_abb(padre->izq,arbol->destruir_dato);
	padre->izq = nodo_act;
	arbol->cantidad++;	
	return true;
}

//**********************************************************************

//Devuelve NULL en caso que no se encuentra la clave en el arbol
void *abb_obtener(const abb_t *arbol, const char *clave) {
	if (arbol == NULL) return NULL;
	abb_nodo_t* nodo = buscar_nodo(clave,arbol->raiz,arbol->cmp);
	if (nodo==NULL) return NULL;
	return nodo->dato; 	
}

//**********************************************************************

bool abb_pertenece(const abb_t *arbol, const char *clave) {
	if (arbol == NULL) return false;
	abb_nodo_t* nodo = buscar_nodo(clave,arbol->raiz,arbol->cmp);
	if (nodo == NULL) return false;
	return true;
}

//**********************************************************************

void abb_destruir(abb_t *arbol) {
	if (arbol == NULL) return;
	abb_iterar(arbol->raiz,arbol->destruir_dato,destruir_nodo_abb);
	free(arbol);
}


//**********************************************************************
void abb_borrar_hoja(abb_t* arbol, abb_nodo_t* nodo_act, abb_nodo_t* padre) {
	if (padre == NULL) {
		arbol->raiz = NULL;
		arbol->cantidad--;
		destruir_nodo_abb(nodo_act, arbol->destruir_dato);
		return;
	}
	int hijo_es_mayor = arbol->cmp(padre->clave,nodo_act->clave);
	if (hijo_es_mayor > 0) padre->izq = NULL;
	if (hijo_es_mayor < 0) padre->der = NULL;
	arbol->cantidad--;
	destruir_nodo_abb(nodo_act, arbol->destruir_dato);		
}	
//**********************************************************************
void abb_borrar_hijo_izq(abb_t* arbol, abb_nodo_t* nodo_act, abb_nodo_t* padre) {
	if (padre == NULL) {
		arbol->raiz = nodo_act->izq;
		arbol->cantidad--;
		destruir_nodo_abb(nodo_act, arbol->destruir_dato);
		return;
	}
	int hijo_es_mayor = arbol->cmp(padre->clave,nodo_act->clave);
	if (hijo_es_mayor > 0) padre->izq = nodo_act->izq;
	if (hijo_es_mayor < 0) padre->der = nodo_act->izq;
	arbol->cantidad--;
	destruir_nodo_abb(nodo_act, arbol->destruir_dato);
}
//**********************************************************************	
void abb_borrar_hijo_der(abb_t* arbol, abb_nodo_t* nodo_act, abb_nodo_t* padre) {	
	if (padre == NULL) {
		arbol->raiz = nodo_act->der;
		arbol->cantidad--;
		destruir_nodo_abb(nodo_act, arbol->destruir_dato);
		return;
	}
	int hijo_es_mayor = arbol->cmp(padre->clave,nodo_act->clave);
	if (hijo_es_mayor > 0) padre->izq = nodo_act->der;
	if (hijo_es_mayor < 0) padre->der = nodo_act->der;
	arbol->cantidad--;
	destruir_nodo_abb(nodo_act, arbol->destruir_dato);	
}
//**********************************************************************

void* abb_borrar(abb_t *arbol, const char *clave) {
	if (!abb_pertenece(arbol,clave)) return NULL;
	abb_nodo_t* nodo_act = buscar_nodo(clave,arbol->raiz,arbol->cmp);
	if (nodo_act == NULL) return NULL;
	abb_nodo_t* padre = buscar_padre(arbol,NULL, nodo_act,NULL);
	void* dato = nodo_act->dato;
	//Caso hoja
	if (!nodo_act->der && !nodo_act->izq) {
		abb_borrar_hoja(arbol,nodo_act,padre);	
		return dato;
	}
	
	//Caso 1 hijo izq
	if (!nodo_act->der) {
		abb_borrar_hijo_izq(arbol,nodo_act,padre);
		return dato;
	}	
	
	//Caso 1 hijo der
	if (!nodo_act->izq) {
		abb_borrar_hijo_der(arbol,nodo_act,padre);
		return dato;
	}	
	//Caso 2 hijos
	abb_nodo_t* sucesor = buscar_sucesor(nodo_act,NULL);
	abb_nodo_t* padre_sucesor = buscar_padre(arbol,NULL, sucesor,NULL);
	swap_abb_nodos(&nodo_act, &sucesor, arbol);
	//Caso hoja
	if (!sucesor->der && !sucesor->izq) {
		if (arbol->cmp(sucesor->clave,nodo_act->der->clave) == 0) {
			nodo_act->der=NULL;
			destruir_nodo_abb(sucesor, arbol->destruir_dato);
			arbol->cantidad--;
			return dato;
		}
		abb_borrar_hoja(arbol,sucesor,padre_sucesor);
		return dato;	
	}	
	
	//Caso 1 hijo der
	if (arbol->cmp(sucesor->clave,nodo_act->der->clave) == 0) {
		nodo_act->der=sucesor->der;
		destruir_nodo_abb(sucesor, arbol->destruir_dato);
		arbol->cantidad--;
		return dato;
	}		
	abb_borrar_hijo_der(arbol, sucesor, padre_sucesor);
	return dato;
	
	
}	
	

/*
 * Iterador Interno 
 */
bool wrapper_abb_in_order(abb_nodo_t* nodo, bool visitar(const char *clave, void *dato, void *extra), void *extra) {
	if(!nodo) return true;
	if(!wrapper_abb_in_order(nodo->izq, visitar, extra)) return false;
	if(!visitar(nodo->clave, nodo->dato, extra)) return false;
	if(!wrapper_abb_in_order(nodo->der, visitar, extra)) return false;
	return true;
}
	
//**********************************************************************

void abb_in_order(abb_t *arbol, bool visitar(const char *clave, void *dato, void *extra), void *extra){
	if (arbol != NULL){
		wrapper_abb_in_order(arbol->raiz, visitar, extra);
	}
}

/*
 * Iterador Externo
 */

struct abb_iter{
	pila_t* pila;
};


void apilar_hijos_izquierdos(abb_nodo_t* nodo, pila_t* pila){
	if (nodo == NULL) return;
	if (!nodo->izq) return;
	
	pila_apilar(pila, nodo->izq);
	apilar_hijos_izquierdos(nodo->izq, pila);
}

//**********************************************************************

abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
	abb_iter_t* iter = malloc(sizeof(abb_iter_t));
	if (!iter) return NULL;
	iter->pila = pila_crear();
	if (!iter->pila){ 
		free(iter);
		return NULL;
	}
	if (!arbol->raiz) return iter;
	pila_apilar(iter->pila, arbol->raiz);
	apilar_hijos_izquierdos(arbol->raiz, iter->pila);
	return iter;
}

//**********************************************************************

bool abb_iter_in_avanzar(abb_iter_t *iter){
	if (abb_iter_in_al_final(iter)) return false;
	abb_nodo_t* nodo = pila_desapilar(iter->pila);
	if (nodo->der != NULL){
		pila_apilar(iter->pila, nodo->der);
		apilar_hijos_izquierdos(nodo->der, iter->pila);
	}
	return true;
}

//**********************************************************************

const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
	abb_nodo_t* nodo = pila_ver_tope(iter->pila);
	if (!nodo) return NULL;
	return nodo->clave;
}

//**********************************************************************

bool abb_iter_in_al_final(const abb_iter_t *iter){
	return pila_esta_vacia(iter->pila);
}

//**********************************************************************

void abb_iter_in_destruir(abb_iter_t* iter){
	pila_destruir(iter->pila);
	free(iter);

}

