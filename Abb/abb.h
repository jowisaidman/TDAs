#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include <stddef.h>

/*
 * DEFINICION DE TIPOS DE DATOS
 */

typedef struct abb abb_t;
typedef struct abb_iter abb_iter_t;

/*
 * DEFINICION DE FUNCIONES
 */

//Funcion de comparacion. Es definida por el usuario
typedef int (*abb_comparar_clave_t) (const char *, const char *);

//Funcion para destruir los datos. Definida por el usuario
typedef void (*abb_destruir_dato_t) (void *);

/*
 * PRIMITIVAS DEL ABB
 */

//Se crea un abb
//Pre: La funcion cmp existe y destruir_dato puede ser NULL
//Post: Devuelve un abb
abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato);

//Guarda un elemento en el abb
//Pre: el abb fue creado
//Post: Se inserto un nuevo elemento con clave y un dato
//Si la clave pertenece al abb se reemplaza el dato y devuelve true
//Devuelve false si ocurrio un fallo
bool abb_guardar(abb_t *arbol, const char *clave, void *dato);

//Elimina unn elemento del abb
//Pre: El abb fue creado
//Post: Se elimina el nodo clave y dato del abb si pertenece
//Devuelve el dato asociado a la clave o NULL si no pertenece al abb
void *abb_borrar(abb_t *arbol, const char *clave);

//Se obtiene el dato de la clave buscada
//Pre: el abb fue creado
//Post: Busca la clave en el abb y devuelve el dato asociado a esa clave
//Devuelve NULL si no pertenece al abb
void *abb_obtener(const abb_t *arbol, const char *clave);

//Verifica si una clave pertenece al abb
//Pre: el abb fue creado
//Post: Devuelve true si pertence, false en caso contrario
bool abb_pertenece(const abb_t *arbol, const char *clave);

//Devuelve la cantidad de elementos del abb
size_t abb_cantidad(abb_t *arbol);

//Destruye el abb
//Pre: El abb fue creado
//Post: Se destruye el abb y cada elemento es destruido
void abb_destruir(abb_t *arbol);

/*
 * ITERADOR IN ORDER INTERNO
 */

//Itera un arbol in order
//Pre: el abb fue creado
//Post: Aplica una funcion visitar en cada elemento segun corresponda
void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra);

/*
 * PRIMITIVAS ITERADOR IN ORDER EXTERNO
 */

//Crea un iterador de abb
//Pre: el abb fue creado
abb_iter_t *abb_iter_in_crear(const abb_t *arbol);

//Avanza 1 elemento del iterador
//Devuelve true si avanzo, false en caso de no poder avanzar
bool abb_iter_in_avanzar(abb_iter_t *iter);

//Devuelve la clave actual del iterador
const char *abb_iter_in_ver_actual(const abb_iter_t *iter);

//Devuelve true si el iterador esta al final del abb
bool abb_iter_in_al_final(const abb_iter_t *iter);

//Destruye el iterador
//Pre: iter fue creado
void abb_iter_in_destruir(abb_iter_t* iter);


void pruebas_abb_alumno();


#endif // HASH_H



