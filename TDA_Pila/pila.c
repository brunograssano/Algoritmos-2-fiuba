#include <stdlib.h>
#include <stdio.h>
#include "pila.h"
const int ERROR=-1,EXITO=0,NO_EXISTE=0;
const int TAMANIO_INICIAL=5,CANT_AUMENTO=2,CANT_REDUCCION=2;


/* 
 * Crea una pila, reservando la memoria necesearia para almacenar la
 * estructura.
 * Devuelve un puntero a la estructura pila_t creada o NULL si no pudo
 * crearla.
 */
pila_t* pila_crear(){
	pila_t* pila = malloc(sizeof(pila_t));
	if(pila==NULL){
		return NULL;
	}
	pila->tope=0;
	pila->tamanio=TAMANIO_INICIAL;
	pila->elementos=malloc((unsigned int)TAMANIO_INICIAL*sizeof(void*));
	
	if(pila->elementos==NULL){
		free(pila);
		return NULL;
	}

	return pila;
}

/* precondiciones: Recibe el vector dinamico de elementos junto con el tamanio que tiene actualmente.
 * postcondiciones:Aumenta o disminuye el tamanio y copia cada elemento al nuevo vector si la asignacion de memoria salio bien,
 *				   caso contrario devuelve -1, indicando el error.
 */
int redimensionar_pila(void*** elementos,int* tamanio,int redimension){
    void* auxiliar=realloc(*elementos,(unsigned int) redimension * sizeof(void*));
    if(auxiliar==NULL){
        return ERROR;
    }
    (*elementos)=auxiliar;
    (*tamanio)=redimension;
    return EXITO;
}

/* precondiciones: Los datos que recibe son enteros, estos tendrian que ser positivos.
 * postcondiciones:Devuelve true en caso de que quede espacio en la pila.
 */
bool hay_espacio(int tope,int tamanio){
	return tope<tamanio;
}

/* precondiciones: El tope es positivo.
 * postcondiciones:El elemento a guardar queda asignado en la pila y es aumentado el tope.
 */
void guardar_elemento(void** elementos,void** elemento_a_guardar,int* tope){
	elementos[*tope]=(*elemento_a_guardar);
	(*tope)++;
}

/* 
 * Apila un elemento.
 * Devuelve 0 si pudo o -1 en caso contrario.
 */
int pila_apilar(pila_t* pila, void* elemento){
	if(pila==NULL){
		return ERROR;
	}
	if(pila->elementos==NULL){
		return ERROR;
	}

	int estado=EXITO;
	if(hay_espacio(pila->tope,pila->tamanio)){
		guardar_elemento(pila->elementos,&elemento,&(pila->tope));
	}
	else{
		int nuevo_tamanio=pila->tamanio*CANT_AUMENTO;
		estado=redimensionar_pila(&(pila->elementos),&(pila->tamanio),nuevo_tamanio);
		
		if(estado==EXITO){
			guardar_elemento(pila->elementos,&elemento,&(pila->tope));
		}
	}
	return estado;
}

/* precondiciones: El tope y tamanio son positivos
 * postcondiciones:Si cumple con las condiciones para liberar memoria devuelve true, para eso, su tamanio tiene que ser si o si mayor al inicial,
 				   ya que seria el minimo posible de la pila.
 */
bool se_puede_liberar_memoria(int tope,int tamanio){
	return tamanio>TAMANIO_INICIAL && tope<tamanio/CANT_REDUCCION;
}

/* 
 * Desapila un elemento.
 * Devuelve 0 si pudo desapilar o -1 si no pudo.
 */
int pila_desapilar(pila_t* pila){
	if(pila==NULL){
		return ERROR;
	}
	if(pila->elementos==NULL){
		return ERROR;
	}
	if(pila->tope==0){
		return ERROR;
	}

	(pila->tope)--;

	int estado=EXITO;
	if(se_puede_liberar_memoria(pila->tope,pila->tamanio)){
		int nuevo_tamanio=pila->tamanio/CANT_REDUCCION;
		estado=redimensionar_pila(&(pila->elementos),&(pila->tamanio),nuevo_tamanio);
	}

	return estado;
}

/* 
 * Determina si la pila está vacia.
 * Devuelve true si está vacía, false en caso contrario.
 * Si la pila no existe devolverá true.
 */
bool pila_vacia(pila_t* pila){
	if(pila==NULL){
		return true;
	}
	if(pila->elementos==NULL){
		return true;
	}
	return pila->tope==0;
}

/* 
 * Devuelve la cantidad de elementos almacenados en la pila.
 * Si la pila no existe devolverá 0.
 */
int pila_cantidad(pila_t* pila){
	if(pila==NULL){
		return NO_EXISTE;
	}
	if(pila->elementos==NULL){
		return NO_EXISTE;
	}
	return pila->tope;
}

/*
 * Devuelve el elemento en el tope de la pila o NULL
 * en caso de estar vacía.
 * Si la pila no existe devolverá NULL.
 */
void* pila_tope(pila_t* pila){
	if(pila==NULL){
		return NULL;
	}
	if(pila->elementos==NULL){
		return NULL;
	}
	if(pila->tope==0){
		return NULL;
	}
	return pila->elementos[pila->tope-1];
}

/* 
 * Destruye la pila liberando la memoria reservada para la misma.
 */
void pila_destruir(pila_t* pila){
	if(pila!=NULL){
		free(pila->elementos);
	}
	free(pila);
}