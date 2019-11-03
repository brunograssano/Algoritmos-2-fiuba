#include <stdlib.h>
#include "lista.h"
const int EXITO=0,ERROR=-1,NO_EXISTE=0;

typedef struct nodo {
	void* elemento;
	struct nodo* siguiente;
}nodo_t;

struct lista{
	nodo_t* nodo_primero;
	nodo_t* nodo_ultimo;
	size_t cantidad;
};

struct lista_iterador{
	lista_t* lista;
	nodo_t* pos_actual;
};

/*
 * Crea la lista reservando la memoria necesaria.
 * Devuelve un puntero a la lista creada o NULL en caso de error.
 */
lista_t* lista_crear(){
	lista_t* lista=malloc(sizeof(lista_t));
	if(lista==NULL){
		return NULL;
	}
	lista->cantidad=0;
	lista->nodo_primero=NULL;
	lista->nodo_ultimo=NULL;

	return lista;
}

/*
 * Inserta un elemento al final de la lista.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar(lista_t* lista, void* elemento){
	if(lista==NULL){
		return ERROR;
	}

	nodo_t* nodo=malloc(sizeof(nodo_t));
	if(nodo==NULL){
		return ERROR;
	}

	nodo->siguiente=NULL;

	if(lista_vacia(lista)){
		lista->nodo_primero=nodo;
		lista->nodo_ultimo=nodo;
	}
	else{
		lista->nodo_ultimo->siguiente=nodo;
		lista->nodo_ultimo=nodo;
	}

	(lista->cantidad)++;
	nodo->elemento=elemento;

	return EXITO;
}

/* Mueve un axiliar hasta la posicion anterior del lugar en que se quiere insertar en la lista.
 * La posicion tiene que mayor que 1.
 */
void ir_hasta_posicion_anterior(nodo_t** aux,size_t posicion){
	for(int i=0;i<posicion-1;i++){
		if((*aux)!=NULL){
			(*aux)=(*aux)->siguiente;
		}
	}
}

/*
 * Inserta un elemento en la posicion indicada, donde 0 es insertar
 * como primer elemento y 1 es insertar luego del primer elemento.  
 * En caso de no existir la posicion indicada, lo inserta al final.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int lista_insertar_en_posicion(lista_t* lista, void* elemento, size_t posicion){
	if(lista==NULL){
		return ERROR;
	}
	if(lista->cantidad<posicion || lista->cantidad==0){
		return lista_insertar(lista,elemento);
	}

	nodo_t* nodo=malloc(sizeof(nodo_t));
	if(nodo==NULL){
		return ERROR;
	}

	if(posicion==0){
		nodo->siguiente=lista->nodo_primero;
		lista->nodo_primero=nodo;
	}
	else{
		nodo_t* aux=lista->nodo_primero;
		ir_hasta_posicion_anterior(&aux,posicion);
		nodo->siguiente=aux->siguiente;
		aux->siguiente=nodo;
	}

	(lista->cantidad)++;
	nodo->elemento=elemento;
	return EXITO;
}

/*
 * Quita de la lista el elemento que se encuentra en la ultima posición.
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar(lista_t* lista){
	if(lista==NULL){
		return ERROR;
	}

	if(lista->cantidad==0 || lista->nodo_primero==NULL){
		return ERROR;
	}
	else if(lista->cantidad==1){
		free(lista->nodo_primero);
		lista->nodo_primero=NULL;
		lista->nodo_ultimo=NULL;
	}
	else{
		nodo_t* auxiliar=lista->nodo_primero;
		ir_hasta_posicion_anterior(&auxiliar,lista->cantidad-1);
		free(auxiliar->siguiente);
		lista->nodo_ultimo=auxiliar;
		lista->nodo_ultimo->siguiente=NULL;
	}
	(lista->cantidad)--;

	return EXITO;
}

/*
 * Quita de la lista el elemento que se encuentra en la posición
 * indicada, donde 0 es el primer elemento.  
 * En caso de no existir esa posición se intentará borrar el último
 * elemento.  
 * Devuelve 0 si pudo eliminar o -1 si no pudo.
 */
int lista_borrar_de_posicion(lista_t* lista, size_t posicion){
	if(lista==NULL){
		return ERROR;
	}
	if(lista->cantidad<=posicion || lista->cantidad<=1){
		return lista_borrar(lista);
	}

	if(posicion==0){
		nodo_t* aux=lista->nodo_primero;
		lista->nodo_primero=lista->nodo_primero->siguiente;
		free(aux);
	}
	else{
		nodo_t* iterador=lista->nodo_primero;
		ir_hasta_posicion_anterior(&iterador,posicion);
		nodo_t* aux=iterador;
		iterador=iterador->siguiente;
		aux->siguiente=iterador->siguiente;
		free(iterador);
	}

	(lista->cantidad)--;
	return EXITO;
}

/*
 * Devuelve el elemento en la posicion indicada, donde 0 es el primer
 * elemento.
 *
 * Si no existe dicha posicion devuelve NULL.
 */
void* lista_elemento_en_posicion(lista_t* lista, size_t posicion){
	if(lista==NULL){
		return NULL;
	}
	if(lista->cantidad<=posicion || lista->nodo_primero==NULL){
		return NULL;
	}

	if(posicion==0){
		return lista->nodo_primero->elemento;
	}
	
	nodo_t* iterador=lista->nodo_primero;
	ir_hasta_posicion_anterior(&iterador,posicion+1);
	return iterador->elemento;
}

/* 
 * Devuelve el último elemento de la lista o NULL si la lista se
 * encuentra vacía.
 */
void* lista_ultimo(lista_t* lista){
	if(lista==NULL){
		return NULL;
	}
	if(lista->cantidad==0 || lista->nodo_ultimo==NULL){
		return NULL;
	}
	return lista->nodo_ultimo->elemento;
}

/* 
 * Devuelve true si la lista está vacía o false en caso contrario.
 */
bool lista_vacia(lista_t* lista){
	if(lista==NULL){
		return true;
	}
	return lista->cantidad==0;
}

/*
 * Devuelve la cantidad de elementos almacenados en la lista.
 */
size_t lista_elementos(lista_t* lista){
	if(lista==NULL){
		return (size_t)NO_EXISTE;
	}
	return lista->cantidad;
}

/*
 * Libera la memoria reservada por la lista.
 */
void lista_destruir(lista_t* lista){
	while(!lista_vacia(lista)){
		lista_borrar(lista);
	}
	free(lista);
}

/*
 * Crea un iterador para una lista. El iterador creado es válido desde
 * el momento de su creación hasta que no haya mas elementos por
 * recorrer o se modifique la lista iterada (agregando o quitando
 * elementos de la lista).
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
lista_iterador_t* lista_iterador_crear(lista_t* lista){
	if(lista==NULL){
		return NULL;
	}

	lista_iterador_t* iterador=malloc(sizeof(lista_iterador_t));
	if(iterador==NULL){
		return NULL;
	}

	iterador->lista=lista;
	iterador->pos_actual=NULL;

	return iterador;
}

/*
 * Devuelve true si hay mas elementos sobre los cuales iterar o false
 * si no hay mas.
 */
bool lista_iterador_tiene_siguiente(lista_iterador_t* iterador){
	if(iterador==NULL){
		return false;
	}
	if(iterador->pos_actual==NULL){
		return true;
	}
	if(iterador->pos_actual->siguiente==NULL){
		return false;
	}
	return true;
}

/*
 * Avanza el iterador al proximo elemento y lo devuelve.
 * En caso de error devuelve NULL.
 */
void* lista_iterador_siguiente(lista_iterador_t* iterador){
	if(!lista_iterador_tiene_siguiente(iterador)){
		return NULL;
	}
	if(iterador->pos_actual==NULL){
		iterador->pos_actual=iterador->lista->nodo_primero;
	}
	else{
		iterador->pos_actual=iterador->pos_actual->siguiente;
	}

	return iterador->pos_actual->elemento;
}

/*
 * Libera la memoria reservada por el iterador.
 */
void lista_iterador_destruir(lista_iterador_t* iterador){
	free(iterador);
}

/*
 * Iterador interno. Recorre la lista e invoca la funcion con cada
 * elemento de la misma.
 */
void lista_con_cada_elemento(lista_t* lista, void (*funcion)(void*)){
	if(lista==NULL){
		return;
	}
	nodo_t* iterador=lista->nodo_primero;
	for(int i=0;i<lista->cantidad;i++){
		(*funcion)(iterador->elemento);
		iterador=iterador->siguiente;
	}
}