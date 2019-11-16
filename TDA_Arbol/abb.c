#include "abb.h"
const int ERROR=-1,EXITO=0,NO_EXISTE=0;
const int ES_MAYOR=1,SON_IGUALES=0,ES_MENOR=-1;

/*
 * Crea el arbol y reserva la memoria necesaria de la estructura.
 * Comparador se utiliza para comparar dos elementos.
 * Destructor es invocado sobre cada elemento que sale del arbol,
 * puede ser NULL indicando que no se debe utilizar un destructor.
 *
 * Devuelve un puntero al arbol creado o NULL en caso de error.
 */
abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){
	abb_t* arbol=malloc(sizeof(abb_t));
	if(arbol==NULL){
		return NULL;
	}
	arbol->nodo_raiz=NULL;
	arbol->comparador=comparador;
	arbol->destructor=destructor;

	return arbol;
}

/* Crea un nuevo nodo en el se guarda el elemento. una vez creado se lo devuelve.
 * En caso de un error en el proceso, devuelve NULL al nodo de arriba,
 * y guarda el estado en una variable pasada por referencia.
 */
nodo_abb_t* crear_nodo(void** elemento,int* estado){
	nodo_abb_t* nuevo_nodo=malloc(sizeof(nodo_abb_t));
	if(nuevo_nodo==NULL){
		(*estado)=ERROR;
		return NULL;
	}
	nuevo_nodo->elemento=(*elemento);
	nuevo_nodo->izquierda=NULL;
	nuevo_nodo->derecha=NULL;
	(*estado)=EXITO;
	return nuevo_nodo;
}

/* Va recorriendo el arbol buscando el lugar en que insertar el elemento. Necesita del comparador para saber
 * en donde ubicarlo.
 */
nodo_abb_t* insertar_elemento(nodo_abb_t* nodo,abb_comparador comparador,void** elemento,int* estado){
	if(nodo==NULL){
		return crear_nodo(elemento,estado);
	}
	else if(comparador(*elemento,nodo->elemento)==ES_MAYOR){
		nodo->derecha=insertar_elemento(nodo->derecha,comparador,elemento,estado);
	}
	else if(comparador(*elemento,nodo->elemento)==ES_MENOR){
		nodo->izquierda=insertar_elemento(nodo->izquierda,comparador,elemento,estado);
	}
	else if(comparador(*elemento,nodo->elemento)==SON_IGUALES){
		nodo->derecha=insertar_elemento(nodo->derecha,comparador,elemento,estado);
	}
	return nodo;
}

/*
 * Inserta un elemento en el arbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
int arbol_insertar(abb_t* arbol, void* elemento){
 	if(arbol==NULL){
 		return ERROR;
 	}
 	int estado;
 	arbol->nodo_raiz=insertar_elemento(arbol->nodo_raiz,arbol->comparador,&elemento,&estado);
 	return estado;
}

/* Determina si el nodo no tiene hijos.
 */
bool es_nodo_hoja(nodo_abb_t* nodo){
	return (nodo->izquierda==NULL && nodo->derecha==NULL);
}

/* Verifica que tenga dos hijos el nodo.
 */
bool tiene_dos_hijos(nodo_abb_t* nodo){
	return (nodo->izquierda!=NULL && nodo->derecha!=NULL);
}

/* Busca el nodo que este mas a la izquierda posible. Se utiliza para agarrar el menor de los mayores.
 * Recibe otro puntero que se usa para actualizar el padre del nodo que va a tomar el lugar del nodo a eliminar.
 */
nodo_abb_t* buscar_nodo_mas_izquierda(nodo_abb_t* nodo){
	if(nodo->izquierda!=NULL){
		return buscar_nodo_mas_izquierda(nodo->izquierda);
	}
	return nodo;
}

/* Busca el nodo que seria el padre del menor de los mayores, en caso de que este no tenga un padre (el menor es el nodo derecho),
 * se devuelve NULL. El nodo no deberia de ser NULL cuando se recibe.
 */
nodo_abb_t* buscar_padre(nodo_abb_t* nodo,nodo_abb_t* nodo_hijo){
	if(nodo->izquierda==NULL){
		return NULL;
	}
	if(nodo->izquierda==nodo_hijo){
		return nodo;
	}
	return buscar_padre(nodo->izquierda,nodo_hijo);
}

/* Realiza la accion correspondiente cuando se va a borrar un elemento en el arbol.
 * Borra el nodo deseado y se encarga de que se mantenga la estructura, ya sea el nodo tenga uno, dos, o ningun hijo.
 */
nodo_abb_t* reacomodar_arbol(nodo_abb_t* nodo,abb_liberar_elemento destructor,int* estado){
	nodo_abb_t* nodo_devuelto;
	if(es_nodo_hoja(nodo)){
		nodo_devuelto=NULL;
	}
	else if(tiene_dos_hijos(nodo)){
		nodo_devuelto=buscar_nodo_mas_izquierda(nodo->derecha);
		nodo_abb_t* padre=buscar_padre(nodo->derecha,nodo_devuelto);
		if(padre!=NULL){
			padre->izquierda=nodo_devuelto->derecha;
		}
		nodo_devuelto->izquierda=nodo->izquierda;
		if(nodo_devuelto!=nodo->derecha){
			nodo_devuelto->derecha=nodo->derecha;
		}
	}
	else{
		if(nodo->izquierda!=NULL){
			nodo_devuelto=nodo->izquierda;
		}
		else{
			nodo_devuelto=nodo->derecha;
		}
	}
	if(destructor!=NULL){
		destructor(nodo->elemento);
	}
	free(nodo);
	nodo=NULL;
	(*estado)=EXITO;
	return nodo_devuelto;
}

/* Busca el nodo que contiene al elemento a borrar, una vez encontrado se encarga de eliminarlo y que quede acomodado el arbol.
 */
nodo_abb_t* borrar_elemento(abb_comparador comparador,abb_liberar_elemento destructor,nodo_abb_t* nodo,void** elemento,int* estado){
	if(nodo==NULL){
		(*estado)=ERROR;
		return NULL;
	}
	if(comparador(*elemento,nodo->elemento)==SON_IGUALES){
		return reacomodar_arbol(nodo,destructor,estado);
	}
	else if(comparador(*elemento,nodo->elemento)==ES_MAYOR){
		nodo->derecha=borrar_elemento(comparador,destructor,nodo->derecha,elemento,estado);
	}
	else{
		nodo->izquierda=borrar_elemento(comparador,destructor,nodo->izquierda,elemento,estado);
	}

	return nodo;
}


/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.  
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
int arbol_borrar(abb_t* arbol, void* elemento){
	if(arbol==NULL){
		return ERROR;
	}
	int estado;
	arbol->nodo_raiz=borrar_elemento(arbol->comparador,arbol->destructor,arbol->nodo_raiz,&elemento,&estado);
	return estado;
}


/* Recorre el arbol en busca del elemento que le mandan. Si el elemento no esta devuelve NULL.
 * Necesita del comparador del arbol.
 */
void* buscar_en_nodo(abb_comparador comparador,nodo_abb_t* nodo,void** elemento){
	if(nodo==NULL){
		return NULL;
	}
	else if(comparador(*elemento,nodo->elemento)==SON_IGUALES){
		return nodo->elemento;
	}
	else if(comparador(*elemento,nodo->elemento)==ES_MAYOR){
		return buscar_en_nodo(comparador,nodo->derecha,elemento);
	}
	else{
		return buscar_en_nodo(comparador,nodo->izquierda,elemento);
	}
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 * 
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
	if(arbol==NULL){
		return NULL;
	}
	return buscar_en_nodo(arbol->comparador,arbol->nodo_raiz,&elemento);
}

/*
 * Devuelve el elemento almacenado como raiz o NULL si el árbol está
 * vacío.
 */
void* arbol_raiz(abb_t* arbol){
	if(arbol==NULL){
		return NULL;
	}
	if(arbol->nodo_raiz==NULL){
		return NULL;
	}
	return arbol->nodo_raiz->elemento;
}


/*
 * Determina si el árbol está vacío. 
 * Devuelve true si lo está, false en caso contrario.
 */
bool arbol_vacio(abb_t* arbol){
	if(arbol==NULL){
		return true;
	}
	return arbol->nodo_raiz==NULL;
}

/* Recorre el arbol de forma inorden, es decir (izq->nodo->der).
 * Los elementos los va guardando en un array del cual se necesita su tamanio, asi se compara con la cantidad
 * de elementos guardados.
 */
void recorrer_inorden_recursivo(nodo_abb_t* nodo,void** array,int tamanio_array,int* cantidad_guardada){
	if(nodo==NULL){
		return;
	}
	recorrer_inorden_recursivo(nodo->izquierda,array,tamanio_array,cantidad_guardada);
	if((*cantidad_guardada)>=tamanio_array){
		return;
	}
	array[*cantidad_guardada]=nodo->elemento;
	(*cantidad_guardada)++;
	recorrer_inorden_recursivo(nodo->derecha,array,tamanio_array,cantidad_guardada);
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_inorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol==NULL){
		return NO_EXISTE;
	}
	int cantidad_guardada=0;
	recorrer_inorden_recursivo(arbol->nodo_raiz,array,tamanio_array,&cantidad_guardada);
	return cantidad_guardada;
}


/* Recorre el arbol de forma preorden, es decir (nodo->izq->der).
 * Los elementos los va guardando en un array del cual se necesita su tamanio, asi se compara con la cantidad
 * de elementos guardados.
 */
void recorrer_preorden_recursivo(nodo_abb_t* nodo,void** array,int tamanio_array,int* cantidad_guardada){
	if(nodo==NULL){
		return;
	}
	if((*cantidad_guardada)>=tamanio_array){
		return;
	}
	array[*cantidad_guardada]=nodo->elemento;
	(*cantidad_guardada)++;
	recorrer_preorden_recursivo(nodo->izquierda,array,tamanio_array,cantidad_guardada);
	recorrer_preorden_recursivo(nodo->derecha,array,tamanio_array,cantidad_guardada);
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_preorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol==NULL){
		return NO_EXISTE;
	}
	int cantidad_guardada=0;
	recorrer_preorden_recursivo(arbol->nodo_raiz,array,tamanio_array,&cantidad_guardada);
	return cantidad_guardada;
}


/* Recorre el arbol de forma postorden, es decir (izq->der->nodo).
 * Los elementos los va guardando en un array del cual se necesita su tamanio, asi se compara con la cantidad
 * de elementos guardados.
 */
void recorrer_postorden_recursivo(nodo_abb_t* nodo,void** array,int tamanio_array,int* cantidad_guardada){
	if(nodo==NULL){
		return;
	}

	recorrer_postorden_recursivo(nodo->izquierda,array,tamanio_array,cantidad_guardada);
	recorrer_postorden_recursivo(nodo->derecha,array,tamanio_array,cantidad_guardada);
	if((*cantidad_guardada)>=tamanio_array){
		return;
	}
	array[*cantidad_guardada]=nodo->elemento;
	(*cantidad_guardada)++;
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
int arbol_recorrido_postorden(abb_t* arbol, void** array, int tamanio_array){
	if(arbol==NULL){
		return NO_EXISTE;
	}
	int cantidad_guardada=0;
	recorrer_postorden_recursivo(arbol->nodo_raiz,array,tamanio_array,&cantidad_guardada);
	return cantidad_guardada;
}

/* Recorre el arbol entero de forma postorden, liberando la memoria que ocupa cada nodo.
 */
void recorrer_arbol_entero(nodo_abb_t* nodo,abb_liberar_elemento destructor){
	if(nodo==NULL){
		return;
	}
	if(nodo->izquierda!=NULL){
		recorrer_arbol_entero(nodo->izquierda,destructor);
	}
	if(nodo->derecha!=NULL){
		recorrer_arbol_entero(nodo->derecha,destructor);
	}
	if(nodo!=NULL && destructor!=NULL){
		destructor(nodo->elemento);
	}
	free(nodo);
}

/*
 * Destruye el arbol liberando la memoria reservada por el mismo.
 * Adicionalmente invoca el destructor con cada elemento presente en
 * el arbol.
 */
void arbol_destruir(abb_t* arbol){
	if(arbol==NULL){
		return;
	}
	recorrer_arbol_entero(arbol->nodo_raiz,arbol->destructor);
	free(arbol);
}

/* Recorre el arbol de forma inorden hasta que lo recorra entero o que la funcion devuelva true.
 */
void inorden_con_cada_elemento(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra,bool* estado){
	if(nodo==NULL){
		return;
	}
	inorden_con_cada_elemento(nodo->izquierda,funcion,extra,estado);
	if(*estado){
		return;
	}
	(*estado)=(*funcion)(nodo->elemento,extra);
	inorden_con_cada_elemento(nodo->derecha,funcion,extra,estado);
}

/* Recorre el arbol de forma preorden hasta que lo recorra entero o que la funcion devuelva true.
 */
void preorden_con_cada_elemento(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra,bool* estado){
	if(nodo==NULL){
		return;
	}
	if(*estado){
		return;
	}
	(*estado)=(*funcion)(nodo->elemento,extra);
	preorden_con_cada_elemento(nodo->izquierda,funcion,extra,estado);
	preorden_con_cada_elemento(nodo->derecha,funcion,extra,estado);

}

/* Recorre el arbol de forma postorden hasta que lo recorra entero o que la funcion devuelva true.
 */
void postorden_con_cada_elemento(nodo_abb_t* nodo, bool (*funcion)(void*, void*), void* extra,bool* estado){
	if(nodo==NULL){
		return;
	}
	postorden_con_cada_elemento(nodo->izquierda,funcion,extra,estado);
	postorden_con_cada_elemento(nodo->derecha,funcion,extra,estado);
	if(*estado){
		return;
	}
	(*estado)=(*funcion)(nodo->elemento,extra);
}

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el 
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
*/
void abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
	if(arbol==NULL){
		return;
	}
	bool estado=false;
	if(recorrido==ABB_RECORRER_INORDEN){
		inorden_con_cada_elemento(arbol->nodo_raiz,funcion,extra,&estado);
	}
	else if(recorrido==ABB_RECORRER_PREORDEN){
		preorden_con_cada_elemento(arbol->nodo_raiz,funcion,extra,&estado);
	}
	else if(recorrido==ABB_RECORRER_POSTORDEN){
		postorden_con_cada_elemento(arbol->nodo_raiz,funcion,extra,&estado);
	}
}

