#define _XOPEN_SOURCE 500
#include "heap.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definicion de struct para heap
struct heap {
	void** arreglo;
	cmp_func_t cmp;
	size_t tamanio;
	size_t cantidad;		
};

#define TAM_INI 10

//Funciones Auxiliares
//Recibe como parametro la posicion de un hijo ,un padre y un heap. Realiza
//un swap entre el hijo y el padre.
void swap(size_t pos_hijo,size_t pos_padre,void** p_arreglo[]) {
	void** arreglo = *p_arreglo;
	void* padre = arreglo[pos_padre];
	void* hijo = arreglo[pos_hijo];
	arreglo[pos_padre] = hijo;
	arreglo[pos_hijo] = padre;
}

//Recibe la posicion de un hijo y devuevle la posicion de su padre
size_t posicion_padre(size_t posicion_hijo) {
	return (size_t)((posicion_hijo-1)/2);
}

//Recibe la posicion de un padre y devuevle la posicion de su hijo izquierdo
size_t posicion_hijo_izq(size_t pos_padre) {
	return (2*pos_padre+1);
}

//Recibe la posicion de un padre y devuevle la posicion de su hijo derecho
size_t posicion_hijo_der(size_t pos_padre) {
	return (2*pos_padre+2);
}

//Recibe como parametro la posicion de un hijo y un heap. Se busca al padre
//del hijo en el heap. En caso que no tenga padre devuelve NULL.
void* devolver_padre(size_t posicion_hijo, void *arreglo[]) {
	if (posicion_hijo == 0) return NULL;
	size_t pos_padre = posicion_padre(posicion_hijo);
	return arreglo[pos_padre];
}

//Recibe como parametro una posicion y un heap. La posicion es la de un padre
//a la cual se busca su hijo izquierdo.
//Devuelve NULL en caso que no tenga hijo izquierdo
void* devolver_hijo_izq(size_t pos_padre, void *arreglo[],size_t largo) {
	size_t pos_hijo = posicion_hijo_izq(pos_padre);
	if (pos_hijo > largo-1) return NULL;
	return arreglo[pos_hijo];
}
//Recibe como parametro una posicion y un heap. La posicion es la de un padre
//a la cual se busca su hijo derecho.
//Devuelve NULL en caso que no tenga hijo derecho
void* devolver_hijo_der(size_t pos_padre, void *arreglo[],size_t largo) {
	size_t pos_hijo = posicion_hijo_der(pos_padre);
	if (pos_hijo > largo-1) return NULL;
	return arreglo[pos_hijo];
}
//Recibe como parametro un elemento, una posicion (la del elemento), un heap
//y una funcion de comparacion y sube al elemento en la posicion adecuada
//para cumplir las variantes del heap.
void upheap(void* elem, size_t posicion, heap_t* heap, cmp_func_t cmp) {
	if (posicion == 0) return;
	void* padre = devolver_padre(posicion,heap->arreglo);
	if (cmp(elem, padre) > 0) {
		size_t pos_padre = posicion_padre(posicion);
		swap(posicion, pos_padre,&heap->arreglo);
		upheap(elem,pos_padre,heap,cmp);
	}
}
//Recibe como parametro un elemento, una posicion (la del elemento), un heap
//y una funcion de comparacion y baja al elemento en la posicion adecuada
//para cumplir las variantes del heap.
void downheap(void* elem, size_t posicion,void **p_arreglo[], cmp_func_t cmp,size_t cantidad_heap) {
	void** arreglo = *p_arreglo;
	if (posicion > cantidad_heap-1) return;
	size_t max = posicion;
	void* hijo_izq = devolver_hijo_izq(posicion, arreglo,cantidad_heap);
	void* hijo_der = devolver_hijo_der(posicion, arreglo,cantidad_heap);
	if (hijo_izq) {
		if (cmp(hijo_izq, elem) > 0) {
			max = posicion_hijo_izq(posicion);
		}
	}
	if (hijo_der) {
		void* mayor_actual = arreglo[max];
		if (cmp(hijo_der,mayor_actual) > 0) {
			max = posicion_hijo_der(posicion);
		}
	}
	if (max != posicion) {
		swap(max,posicion,&arreglo);
		downheap(elem,max,&arreglo,cmp,cantidad_heap);
	 }
}
//Entre como parametro un heap y un nuevo tamaño para el heap y lo redimensiona.
//Devuelve un booleano indicando si la redimension fue o no exitosa
//Pre: el heap fue creado
bool redimensionar_heap(heap_t* heap, size_t nuevo_tam) {
	void** heap_aux = realloc(heap->arreglo, nuevo_tam * sizeof(void*));	
	if (!heap_aux) return false;
	heap->arreglo = heap_aux;
	heap->tamanio = nuevo_tam;
	return true;
}
//***********************************************************************
void heapify(void **p_arreglo[],size_t n,cmp_func_t cmp) {
	void** arreglo = *p_arreglo;
	for (size_t i = 0; i<= n/2; i++) {
		size_t pos = (n/2)-i;
		downheap(arreglo[pos],pos,&arreglo,cmp,n);
	}	
}
/* *****************************************************************
 *                    PRIMITIVAS DEL HEAP
 * *****************************************************************/
 
heap_t *heap_crear(cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
	if (heap == NULL) return NULL;
	void** arreglo = malloc(TAM_INI * sizeof(void*));
	if (arreglo == NULL) {
		free(heap);
		return NULL;
	}
	heap->arreglo = arreglo;
	heap->cmp = cmp;
	heap->tamanio = TAM_INI;
	heap->cantidad = 0;
	return heap;
}

//*********************************************************************

heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp) {
	heap_t* heap = malloc(sizeof(heap_t));
	if (heap == NULL) return NULL;
	void** arr = malloc(n * sizeof(void*));
	if (arr == NULL) {
		free(heap);
		return NULL;
	}
	
	for (size_t i = 0; i<n; i++) {
		arr[i] = arreglo[i];
	}
	heap->arreglo = arr;
	heap->cmp = cmp;
	heap->cantidad = n;
	heap->tamanio = n;
	heapify(&arr,n,cmp);
	return heap;
}


//**********************************************************************

size_t heap_cantidad(const heap_t *heap) {
	return heap->cantidad;	
}

//**********************************************************************

bool heap_esta_vacio(const heap_t *heap) {
	return (heap->cantidad == 0);
}

//**********************************************************************

void *heap_ver_max(const heap_t *heap) {
	if (heap->cantidad == 0) return NULL;
	return heap->arreglo[0];	
}

//**********************************************************************

bool heap_encolar(heap_t* heap, void* elem) {
	if (heap->cantidad == heap->tamanio) {
		bool redimension_exitosa = redimensionar_heap(heap,heap->tamanio*2);
		if (!redimension_exitosa) return false;
	}
	size_t posicion_actual = heap->cantidad;
	heap->arreglo[posicion_actual] = elem;
	upheap(elem,posicion_actual,heap,heap->cmp);
	heap->cantidad++;
	return true;
}

//**********************************************************************

void* heap_desencolar(heap_t *heap) {
	if (heap == NULL || heap->cantidad == 0) return NULL;
	if (heap->cantidad < (heap->tamanio)/4 && heap->cantidad > TAM_INI) {
		bool redimension_exitosa = redimensionar_heap(heap,heap->tamanio/2);
		if (!redimension_exitosa) return NULL;
	}	
	void* devolver_dato = heap->arreglo[0];
	heap->arreglo[0] = heap->arreglo[heap->cantidad-1];
	heap->arreglo[heap->cantidad-1] = NULL;
	downheap(heap->arreglo[0],0,&heap->arreglo,heap->cmp,heap->cantidad);
	heap->cantidad--;
	return devolver_dato;	
}

//**********************************************************************

void heap_destruir(heap_t *heap, void destruir_elemento(void *e)) {
	for(size_t i = 0; i < heap->cantidad; i++) {
		void* dato_actual = heap->arreglo[i];
		if (destruir_elemento != NULL) {
			destruir_elemento(dato_actual);
		}
	} 
	free(heap->arreglo);
	free(heap);
}

//**********************************************************************

void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp) {
	heapify(&elementos,cant,cmp);
	size_t ultimo_relativo= cant-1;
	for(size_t i=0; i<cant-1; i++) {
		swap(0,ultimo_relativo,&elementos);
		downheap(elementos[0],0,&elementos,cmp,ultimo_relativo);
		ultimo_relativo--;
	}
}




