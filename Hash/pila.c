#include "pila.h"
#include <stdlib.h>
#include <stdio.h>

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila {
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

#define TAM_INICIAL 10

/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/


bool pila_redimensionar(pila_t *pila, size_t nuevo_tam) {
	/*Redimensiona la pila cambiando la capacidad, si es necesario agrega 
	capacidad y sino la reduce*/
	
	void *datos_nuevos = realloc(pila->datos, nuevo_tam * sizeof(void*));
	if (datos_nuevos == NULL) {
		return false;
	}
	pila->datos = datos_nuevos;
	pila->capacidad = nuevo_tam;
	return true;
}

//******************************************************************************

pila_t* pila_crear(void) {
	pila_t* pila = malloc(sizeof(pila_t)); 
	if (pila == NULL) {
		return NULL;
	}
	pila->datos = malloc(TAM_INICIAL * sizeof(void*));
	if (pila->datos==NULL) {
		free(pila);
		return NULL;
	}
	pila->cantidad=0;
	pila->capacidad = TAM_INICIAL;	
	return pila;
}

//******************************************************************************

void pila_destruir(pila_t *pila) {
	//libero toda la memoria que pedi al heap
	free(pila->datos);
	free(pila);
}

//******************************************************************************

bool pila_esta_vacia(const pila_t *pila) {
	return pila->cantidad==0;
}

//******************************************************************************

bool pila_apilar(pila_t *pila, void* valor) {
	if (pila->capacidad==pila->cantidad) {
		bool redimension_exitosa = pila_redimensionar(pila,pila->cantidad *2);
		if (redimension_exitosa == false) {
			return false;
		}
	}
	
	pila->datos[pila->cantidad]=valor;
	pila->cantidad++;
	return true;
}

//******************************************************************************

void* pila_ver_tope(const pila_t *pila) {
	if (pila->cantidad==0) {
		return NULL;
	}

	return pila->datos[pila->cantidad-1];
}

//******************************************************************************

void* pila_desapilar(pila_t *pila) {
	//Si la pila esta vacia debe devolver NULL
	if (pila->cantidad==0) {
		return NULL; 	
	}

	//Tomo el ultimo puntero para luego devolverlo y le resto 1 a la cantidad
	void* puntero = pila->datos[pila->cantidad-1]; 
	pila->cantidad--;

	//Si la cantidad es un cuarto de la capacidad y la capacidad es
	//mayor que la inicial debo reducir la capacidad.
	if (pila->capacidad/4 == pila->cantidad && pila->capacidad / 2 > TAM_INICIAL) {
		pila_redimensionar(pila, pila->capacidad / 2);
	}

	return puntero;
}

//******************************************************************************



