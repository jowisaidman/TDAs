#ifndef HEAP_H
#define HEAP_H

#include <stdbool.h>
#include <stddef.h>



typedef struct heap heap_t;
typedef int (*cmp_func_t) (const void *a, const void *b);

//Recibe como parametro una funcion de comparacion y crea un heap en su 
//estado inicial vacio. Devulve NULL en caso de error.
heap_t *heap_crear(cmp_func_t cmp);

//Recibe como parametro un arreglo, un numero que es el largo del arreglo
//y una funcion de comparacion y crea un heap apartir de dicho arreglo.
//Devuelve NULL en caso de error
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp);

//Recibe como parametro un heap y una funcion que podra ser NULL. Destruye
//el heap y los elementos del heap en caso que el usuario lo pida.
//Pre: La funcion que se le pasa como parametro unicamente sirve para
//destruir los elementos del heap o es un NULL
void heap_destruir(heap_t *heap, void destruir_elemento(void *e));

//Recibe como parametro un heap y devuelve su cantidad. 
//Pre: El heap fue creado
size_t heap_cantidad(const heap_t *heap);

//Recibe como parametro un heap e indica si esta vacio. 
//Pre: El heap fue creado
bool heap_esta_vacio(const heap_t *heap);

//Recibe como parametro un heap y un elemento y encola el elemeto en el 
//heap.
bool heap_encolar(heap_t *heap, void *elem);

//Recibe como parametro un heap e indica su maximo. No modifica el heap. 
void *heap_ver_max(const heap_t *heap);

//Recibe como parametro un heap y desencola el primer elemento. Devuelve
//el elemento desencolado o NULL en caso que el heap este vacio
void *heap_desencolar(heap_t *heap);

//Corre las pruebas necesarias para ver el correcto funcionamiento del heap
void pruebas_heap_alumno();

//Recibe como parametro un arreglo, su largo y una funcion de comparacion
// y ordena el arreglo mediante el metodo heap_sort.
void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp);




#endif // HEAP_H
