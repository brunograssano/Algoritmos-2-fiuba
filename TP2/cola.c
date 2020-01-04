#include <stdlib.h>
#include "cola.h"
const int EXITO_C=0,ERROR_C=-1,NO_EXISTE_C=0;

/*
 * Crea una cola reservando la memoria necesaria
 * para almacenar la estructura.
 * Devuelve un puntero a la estructura cola_t creada.
 */
cola_t* cola_crear(){
	cola_t* cola=malloc(sizeof(cola_t));
	if(cola==NULL){
		return NULL;
	}
	cola->cantidad=0;
	cola->nodo_inicio=NULL;
	cola->nodo_fin=NULL;

	return cola;
}

/*
 * Encola un elemento.
 * Devuelve 0 si pudo encolar o -1 si no pudo.
 */
int cola_encolar(cola_t* cola, void* elemento){
	if(cola==NULL){
		return ERROR_C;
	}

	nodo_t* nodo=malloc(sizeof(nodo_t));
	if(nodo==NULL){
		return ERROR_C;
	}

	if(cola_vacia(cola)){
		cola->nodo_inicio=nodo;
		nodo->siguiente=NULL;
		cola->nodo_fin=nodo;
	}
	else{
		nodo->siguiente=cola->nodo_fin;
		cola->nodo_fin=nodo;
	}

	(cola->cantidad)++;
	nodo->elemento=elemento;

	return EXITO_C;
}

/*
 * Desencola un elemento.
 * Devuelve 0 si pudo desencolar o -1 si no pudo.
 */
int cola_desencolar(cola_t* cola){
	if(cola==NULL){
		return ERROR_C;
	}

	if(cola->cantidad==0){
		return ERROR_C;
	}
	else if(cola->cantidad==1){
		free(cola->nodo_inicio);
		cola->nodo_inicio=NULL;
		cola->nodo_fin=NULL;
	}
	else if(cola->cantidad>1){
		nodo_t* auxiliar=cola->nodo_fin;
		for(int i=0; i<cola->cantidad-1;i++){
			if(auxiliar->siguiente==cola->nodo_inicio){
				free(cola->nodo_inicio);
				cola->nodo_inicio=auxiliar;
				cola->nodo_inicio->siguiente=NULL;
			}
			else{
				auxiliar=auxiliar->siguiente;
			}
		}
	}
	(cola->cantidad)--;

	return EXITO_C;
}

/*
 * Determina si la cola está vacia.
 * Devuelve true si está vacía y false si no.
 * Si la cola no existe devolverá true.
 */
bool cola_vacia(cola_t* cola){
	if(cola==NULL){
		return true;
	}
	return cola->cantidad==0;
}

/*
 * Devuelve la cantidad de elementos almacenados en la cola.
 * Si la cola no existe devolverá 0.
 */
int cola_cantidad(cola_t* cola){
	if(cola==NULL){
		return NO_EXISTE_C;
	}
	return cola->cantidad;
}

/*
 * Devuelve el primer elemento de la cola o NULL en caso de estar
 * vacía.
 * Si la cola no existe devolverá NULL.
 */
void* cola_primero(cola_t* cola){
	if(cola==NULL){
		return NULL;
	}
	if(cola->cantidad==0){
		return NULL;
	}
	return cola->nodo_inicio->elemento;
}

/*
 * Destruye la cola liberando toda la memoria reservada
 * por la cola.
 */
void cola_destruir(cola_t* cola){
	while(!cola_vacia(cola)){
		cola_desencolar(cola);
	}
	free(cola);
}
