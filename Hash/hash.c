#define _XOPEN_SOURCE 500

#include "hash.h"
#include "lista.h"
#include "pila.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* Definicion de los structs para hash, nodo_hash y hash_iter  */

struct hash{
	hash_destruir_dato_t destruir_dato;  
	lista_t** tabla_hash;
	size_t tam;
	size_t cant;
};

typedef struct nodo_hash{
	char* clave;
	void* valor;
}nodo_hash_t;

struct hash_iter{
	const hash_t* hash;
	lista_iter_t* iter_lista;
	size_t pos_hash;
};

#define TAMT 100
#define FACTOR_MAX 2
#define FACTOR_MIN 1

//Funciones Auxiliares
//***********************************************************************


size_t f_hashing(const hash_t* hash,const char* clave) {
	size_t tam = hash->tam;	
	unsigned int num1 = 378551;
	unsigned int num2 = 63689;
	unsigned int clave_numerica = 0;
	for(int i = 0; *clave; clave++, i++){
		 clave_numerica = clave_numerica * num2 + (unsigned int)(*clave);
		 num2 = num2 * num1;
		 }
	return (clave_numerica%tam);
}

//***********************************************************************

nodo_hash_t* nodo_hash_crear(char* clave, void* valor) {
	//Pido memoria para el nodo
	nodo_hash_t* nodo_act = malloc(sizeof(nodo_hash_t));
	
	//Verifico que no es NULL
	if (!nodo_act) {
		return NULL;
	}
	
	//Asigno clave y valor
	nodo_act->clave = clave;
	nodo_act->valor = valor;
	
	return nodo_act;		
}

//***********************************************************************

bool hash_redimensionar (hash_t* hash, double factor_carga) {
	size_t tamanio_nuevo = 0;
	if (factor_carga >= FACTOR_MAX){
		tamanio_nuevo = (hash->tam)*2;
	}
	else if (factor_carga <= FACTOR_MIN) {
		tamanio_nuevo = (hash->tam)/2;
	}
	
	lista_t** tabla_aux = hash->tabla_hash;
	size_t tam_aux = hash->tam;
	hash->tam = tamanio_nuevo;
	hash->tabla_hash = malloc(sizeof(lista_t*)* tamanio_nuevo);
	if(hash->tabla_hash == NULL) return false;
	
	for(int i=0; i < tamanio_nuevo; i++) {
		hash->tabla_hash[i] = NULL;
	}
	for(size_t i=0; i<tam_aux; i++) {
		if(tabla_aux[i]) {
			lista_iter_t* lista_iter = lista_iter_crear(tabla_aux[i]);
			if(lista_iter == NULL) return false;
			nodo_hash_t* nodo_act = lista_iter_ver_actual(lista_iter);
			while(lista_iter_al_final(lista_iter) == false) {
				size_t pos_nueva = f_hashing(hash,nodo_act->clave);
				lista_t* lista_act = hash->tabla_hash[pos_nueva];
				if(lista_act == NULL) {
					lista_t* lista_nueva = lista_crear();
					lista_insertar_primero(lista_nueva,nodo_act);
					hash->tabla_hash[pos_nueva]=lista_nueva;
					lista_iter_avanzar(lista_iter);
					nodo_act = lista_iter_ver_actual(lista_iter);
					continue;
				}
				lista_insertar_ultimo(lista_act,nodo_act);
				lista_iter_avanzar(lista_iter);
				nodo_act = lista_iter_ver_actual(lista_iter);
			}
			lista_iter_destruir(lista_iter);
		}
	}
	
	for(size_t i=0; i<tam_aux; i++) {
		if(tabla_aux[i]) {
			lista_destruir(tabla_aux[i],NULL);
		}
	}
	free(tabla_aux);
	return true;
}
//**********************************************************************

/* *****************************************************************
 *                    PRIMITIVAS DEL HASH
 * *****************************************************************/

hash_t* hash_crear(hash_destruir_dato_t destruir_dato) {
	hash_t* hash = malloc(sizeof(hash_t));
	if (!hash) return NULL;

	hash->destruir_dato = destruir_dato;
	hash->tam = TAMT;//aca defino el tamanio inicial
	hash->cant = 0;
	hash->tabla_hash = malloc(sizeof(lista_t*)* hash->tam);
	
	if (!hash->tabla_hash) {
		free(hash);
		return NULL;
	}
	for(int i=0; i < hash->tam; i++) {
		hash->tabla_hash[i] = NULL; 
	}
	return hash;
}

//***********************************************************************

bool hash_pertenece(const hash_t* hash, const char* clave) {
	if (hash_cantidad(hash) == 0) return false;
	size_t pos_act = f_hashing(hash, clave);
	if (!(hash->tabla_hash[pos_act]))return false;
	lista_t* lista_act = hash->tabla_hash[pos_act];
	lista_iter_t* lista_iter = lista_iter_crear(lista_act); 
	while(!lista_iter_al_final(lista_iter)) {
		nodo_hash_t* nodo_act = lista_iter_ver_actual(lista_iter);
		if (strcmp(nodo_act->clave, clave) == 0) {
			lista_iter_destruir(lista_iter);
			return true;
		}
		lista_iter_avanzar(lista_iter);
	}
	lista_iter_destruir(lista_iter);
	return false;	
}

//***********************************************************************

void* hash_obtener(const hash_t* hash, const char* clave) {
	if (!hash_pertenece(hash,clave)) return NULL;
	size_t pos_act = f_hashing(hash, clave);
	lista_t* lista_act = hash->tabla_hash[pos_act];
	lista_iter_t* lista_iter = lista_iter_crear(lista_act); 	
	while(!lista_iter_al_final(lista_iter)) {	
		nodo_hash_t* nodo_act = lista_iter_ver_actual(lista_iter);
		if (strcmp(nodo_act->clave, clave) == 0) {
			lista_iter_destruir(lista_iter);
			return nodo_act->valor;
		}
		lista_iter_avanzar(lista_iter);
	}
	return NULL;
}

//***********************************************************************

size_t hash_cantidad(const hash_t* hash) { 
	return hash->cant;
}

//***********************************************************************

bool hash_guardar(hash_t* hash, const char* key, void* dato) {
	if((double)hash->cant / (double)hash->tam >=FACTOR_MAX){
		double factor_carga = (double) hash->cant / (double)hash->tam;
		bool redimension_exitosa = hash_redimensionar(hash,factor_carga);
		if(redimension_exitosa == false) {
			return false;
		}
	}
	char* clave = strdup(key);
	if (clave == NULL) { 
		return false;
	}
	size_t pos = f_hashing (hash,clave);
	if(hash->tabla_hash[pos] == NULL){
		hash->tabla_hash[pos] = lista_crear();
		if (hash->tabla_hash[pos] == NULL){
			free(clave);
			return false;
		}
	}
	lista_t* lista = hash->tabla_hash[pos];
	lista_iter_t* iter = lista_iter_crear(lista);
	if (hash_pertenece(hash, clave)) {
		while(lista_iter_al_final(iter) == false){
			nodo_hash_t* nodo_act = lista_iter_ver_actual(iter);
			if(strcmp(nodo_act->clave, clave) == 0){
				if(hash->destruir_dato !=NULL){
					hash->destruir_dato(nodo_act->valor);
				}
				nodo_act->valor = dato;
				lista_iter_destruir(iter);
				free(clave);
				return true;
			}
			lista_iter_avanzar(iter);	
		}
	}
	nodo_hash_t* nodo_hash = nodo_hash_crear(clave, dato);
	lista_insertar_ultimo(lista,nodo_hash);
	hash->cant++;
	lista_iter_destruir(iter);
	return true;
}
	
//***********************************************************************		
	
void hash_destruir(hash_t* hash){
	for(int i=0; i<hash->tam; i++) {
		if(hash->tabla_hash[i] != NULL) {
			lista_t* lista = hash->tabla_hash[i];
			lista_iter_t* lista_iter = lista_iter_crear(lista);
			
			//Recorro toda la lista destruyendo los nodos
			while(lista_iter_al_final(lista_iter) == false) {
				nodo_hash_t* nodo_act = lista_iter_ver_actual(lista_iter);
				
				if(hash->destruir_dato !=NULL){
					hash->destruir_dato(nodo_act->valor);
				}
				free(nodo_act->clave);
				free(nodo_act);
				lista_iter_avanzar(lista_iter);
			}
			lista_destruir(lista,NULL);
			lista_iter_destruir(lista_iter);
				
		}	
	}	
	free(hash->tabla_hash);
	free(hash);
}	
	
//***********************************************************************

void* hash_borrar(hash_t* hash, const char* clave) {
	if((double)hash->cant / (double)hash->tam <= FACTOR_MIN && hash->cant >= TAMT) {
		double factor_carga = (double)hash->cant / (double)hash->tam;
		bool redimension_exitosa = hash_redimensionar(hash,factor_carga);
		if(redimension_exitosa == false) {
			return NULL;
		}
	}
	if (!hash_pertenece(hash,clave)) {
		return NULL;
	}
	size_t pos_act = f_hashing(hash, clave);
	lista_t* lista = hash->tabla_hash[pos_act];
	lista_iter_t* lista_iter = lista_iter_crear(lista);
	while(!lista_iter_al_final(lista_iter)) {
		nodo_hash_t* nodo_act = lista_iter_ver_actual(lista_iter);
		if (strcmp(nodo_act->clave, clave) == 0) {
			void* dato_act = nodo_act->valor;
			free(nodo_act->clave);
			free(nodo_act);
			lista_iter_borrar(lista_iter);
			lista_iter_destruir(lista_iter);
			if (lista_esta_vacia(lista)) {
				lista_destruir(lista,NULL);
				hash->tabla_hash[pos_act] = NULL;
			}
			hash->cant--;
			return dato_act;
		}
		lista_iter_avanzar(lista_iter);
	}
	return NULL;
}
	


/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/

hash_iter_t *hash_iter_crear(const hash_t *hash){
	hash_iter_t* iter = malloc(sizeof(hash_iter_t));
	if(iter == NULL) {
		return NULL;
	}
	iter->hash = hash;
	if(hash_cantidad(hash) != 0){
		for(size_t i = 0 ;i<hash->tam ; i++){
			if(hash->tabla_hash[i] != NULL){
				iter->iter_lista = lista_iter_crear(hash->tabla_hash[i]);
				iter->pos_hash = i;
				return iter;
			}
		}
	}
	iter->iter_lista = NULL;
	iter->pos_hash = 0;
	return iter;
}

//***********************************************************************

bool hash_iter_avanzar(hash_iter_t *iter) {
	if(hash_iter_al_final(iter)) return false;
	if(lista_iter_al_final(iter->iter_lista) == false) {
		lista_iter_avanzar(iter->iter_lista);
	}
	if(lista_iter_al_final(iter->iter_lista)) {
		size_t i =  iter->pos_hash+1;
		while(i<iter->hash->tam) {
			lista_t* lista = iter->hash->tabla_hash[i];
			if(lista != NULL) {
				lista_iter_destruir(iter->iter_lista);
				iter->pos_hash = i;
				iter->iter_lista = lista_iter_crear(iter->hash->tabla_hash[i]);
				if(iter->iter_lista == NULL) return false;
				return true;
			}
			i++;
		}
	}
	return true;
}

// **********************************************************************

const char *hash_iter_ver_actual(const hash_iter_t *iter) {
	if(hash_iter_al_final(iter)) return NULL;
	nodo_hash_t* nodo_act = lista_iter_ver_actual(iter->iter_lista);
	if (nodo_act ==NULL) {
		return NULL;
	}
	return nodo_act->clave;
}

//***********************************************************************

bool hash_iter_al_final(const hash_iter_t *iter) {
	if(iter->iter_lista == NULL) {
		return true;
	}
	if(lista_iter_al_final(iter->iter_lista)) {
		for(size_t i = iter->pos_hash+1 ; i<iter->hash->tam; i++) {
			if(iter->hash->tabla_hash[i] != NULL) {
				return false;
			}
		}
		return true;
	}
	return false;	
}

//***********************************************************************

void hash_iter_destruir(hash_iter_t* iter) {
	if (iter->iter_lista) {
		lista_iter_destruir(iter->iter_lista);
	}
	free(iter);

}









