#include <stdbool.h>
#include <stdio.h>



/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/
 
//Crea una lista
//Post: Devuelve una lista vacia
lista_t *lista_crear(void);

// Devuelve verdadero o falso, según si la lista tiene o no elementos enlazados.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento a la lista en la primera posicion.
// Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al comienzo
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento a la lista al final. 
// Devuelve falso en caso de error.
// Pre: la lista fue creada.
// Post: se agregó un nuevo elemento a la lista, valor se encuentra al final
// de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);



// Saca el primer elemento de la lista. Si la lista tiene elementos, se quita el
// primero de la lista, y se devuelve su valor, si está vacía, devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el valor del primer elemento anterior, la lista
// contiene un elemento menos, si la lista no estaba vacía.
void *lista_borrar_primero(lista_t *lista);

// Obtiene el valor del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del primero, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el primer elemento de la lista, cuando no está vacía.
void *lista_ver_primero(const lista_t *lista);

// Obtiene el valor del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el valor del ultimo, si está vacía devuelve NULL.
// Pre: la lista fue creada.
// Post: se devolvió el ultimo elemento de la lista, cuando no está vacía.
void *lista_ver_ultimo(const lista_t* lista);

// Obtiene el largo de la lista.
// Pre: La lista fue creada.
// Post: Devuelve el largo de la lista.
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));


/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR INTERNO
 * *****************************************************************/

//Entra como parametro una lista, una funcion y un extra. Recorre la lista
//aplicandole la funcion visitar.
//Pre: La lista esta creada, visitar esta definida.
//Post: Se aplico la funcion visitar a los elementos de la lista mientras
//visitar devuelva true.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/* ******************************************************************
 *                PRIMITIVAS DEL ITERADOR EXTERNO
 * *****************************************************************/

//Crea un iterador 
//Pre: Itera sobre un TDA ya creado
//Post: Devuelve un iterador del TDA
lista_iter_t *lista_iter_crear(lista_t *lista);

//Permite avanzar un posicion sobre el TDA. Em caso de llegar al final devuelve false
//Pre: El iterador ya fue creado
//Post: Se avanzo una posicion sobre el iterador, si este ya no estaba al final. En
//caso de estar al final devuelve false.
bool lista_iter_avanzar(lista_iter_t *iter);

//Permite ver el dato actual del TDA
//Pre: El iterador ya fue creado
//Post: Devuelve el dato actual del TDA
void *lista_iter_ver_actual(const lista_iter_t *iter);

//Verifica si el iterador esta en la posicion NULL deL TDA (al final),
//indicando con true o false.
//Pre: El iterador ya fue creado
//Post: Devuelve un booleano diciendo si esta o no alfinal del TDA
bool lista_iter_al_final(const lista_iter_t *iter);

//Destruye el iterador del TDA pero no al TDA sobre el que itera
//Pre: El iterador ya fue creado
//Post: El iterador fue destruido
void lista_iter_destruir(lista_iter_t *iter);

//Inserta un dato entre la posicion anterior y la actual del TDA.
//Pre: El iterador ya fue creado.
//Post: El TDA contiene un nuevo dato y el iterador esta en esa posicion
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

//Borra el nodo actual del iterador y lo devuelve. En caso que este 
//vacio el TDA devuelve NULL.
////Pre: El iterador ya fue creado.
//Post: Devuelve el dato del nodo actual o NULL si el TDA esta vacio
void *lista_iter_borrar(lista_iter_t *iter);




void pruebas_lista_alumno(void); 
