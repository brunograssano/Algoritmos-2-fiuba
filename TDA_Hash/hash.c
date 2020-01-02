#include <stdlib.h>
#include <string.h>

#include "hash.h"
#include "hash_iterador.h"
#include "abb.h"
#include "lista.h"

#define EXITO 0
#define ERROR -1
#define NO_EXISTE 0
#define ES_MAYOR 1
#define SON_IGUALES 0
#define ES_MENOR -1

const size_t FACTOR_CARGA=6;
const int FACTOR_HASH=7;

extern char* strdup(const char*);

struct hash{
  abb_t** arboles;
  size_t cantidad;
  size_t capacidad;
  hash_destruir_dato_t destructor;
};

typedef struct paquete{
  void* elemento;
  char* clave;
  void (*destructor_elemento)(void*);
}paquete_t;

/* Funcion que se utiliza para comparar claves. Si el primero es mayor devuelve 1, si es menor -1,
 * si son iguales devuelve 0.
 */
int comparador_de_claves(void* elemento1,void* elemento2){
	if(strcmp(((paquete_t*)elemento1)->clave,((paquete_t*)elemento2)->clave)>0){
		return ES_MAYOR;
	}
	else if(strcmp(((paquete_t*)elemento1)->clave,((paquete_t*)elemento2)->clave)<0){
		return ES_MENOR;
	}
	else{
		return SON_IGUALES;
	}
}

/* Llama al destructor del elemento guardado y borra el conjunto de elementos, ya que se encuentra en memoria dinamica.
 * Si el destructor del elemento es NULL no lo borra.
 */
void destructor_de_paquetes(void* paquete){
  if(((paquete_t*)paquete)->destructor_elemento!=NULL){
    ((paquete_t*)paquete)->destructor_elemento(((paquete_t*)paquete)->elemento);
  }
  free(((paquete_t*)paquete)->clave);
  free(paquete);
}

/* Se encarga del proceso de la creacion de los arboles del hash, en caso de que ocurra un error en alguno, el proceso se detiene,
 * libera la memoria, y devuelve NULL.
 */
hash_t* crear_arboles(hash_t* hash){
  int i=0;
  bool error_en_creacion=false;
  while(i<hash->capacidad && !error_en_creacion){
    hash->arboles[i]=arbol_crear(comparador_de_claves,destructor_de_paquetes);
    if(hash->arboles[i]==NULL){
      error_en_creacion=true;
    }
    else{
      i++;
    }
  }
  if(error_en_creacion){
    for(int j=0;j<i;j++){
      arbol_destruir(hash->arboles[j]);
    }
    free(hash->arboles);
    free(hash);
    hash=NULL;
  }
  return hash;
}

/*
 * Crea el hash reservando la memoria necesaria para el.
 * Destruir_elemento es un destructor que se utilizará para liberar
 * los elementos que se eliminen del hash.
 * Capacidad indica la capacidad minima inicial con la que se crea el hash.
 * Devuelve un puntero al hash creado o NULL en caso de no poder crearlo.
 */
hash_t* hash_crear(hash_destruir_dato_t destruir_elemento, size_t capacidad){
  hash_t* hash=malloc(sizeof(hash_t));
  if(hash==NULL){
    return NULL;
  }
  hash->cantidad=0;
  hash->destructor=destruir_elemento;
  hash->capacidad=capacidad;
  hash->arboles=malloc(capacidad*sizeof(abb_t*));
  if(hash->arboles==NULL){
    free(hash);
    return NULL;
  }
  return crear_arboles(hash);
}

/* Obtiene la posicion en que se va a guardar un elemento,
 * para eso utiliza un hash de modulo que requiere de la capacidad del hash.
 */
size_t hashear(const char* clave,size_t capacidad){
  int numero=1;
  for(int i=0;i<strlen(clave);i++){
    numero*=(int)clave[i];
  }
  numero/=FACTOR_HASH;
  return (size_t)numero%capacidad;
}

/* Crea un paquete de elementos, este va a contener la clave, el elemento a guardar, y el destructor del elemento.\
 * Se necesita del destructor del elemento ya que este puede estar en memoria.
 */
paquete_t* crear_paquete(void* elemento,const char* clave,hash_destruir_dato_t destruir_elemento){
  paquete_t* paquete=malloc(sizeof(paquete_t));
  if(paquete==NULL){
    return NULL;
  }
  paquete->elemento=elemento;
  paquete->destructor_elemento=destruir_elemento;
  paquete->clave=strdup(clave);
  if(paquete->clave==NULL){
    free(paquete);
    paquete=NULL;
  }
  return paquete;
}

/* Creara un paquete de busqueda que contiene solamente a la clave.
 * Este paquete se encuentra en el stack ya que no es necesario guardarlo despues.
 */
paquete_t crear_paquete_busqueda(const char* clave){
  paquete_t paquete;
  paquete.clave=(char*)clave;
  return paquete;
}

/* Verifica si es necesario hacer un rehash, viendo el grado de ocupacion y el factor de carga.
 */
bool es_necesario_rehashear(size_t capacidad,size_t cantidad_guardada){
  size_t grado_ocupacion=cantidad_guardada/capacidad;
  return grado_ocupacion>FACTOR_CARGA;
}

/* Carga todos los paquetes en una lista, para ser pasados a un nuevo hash despues
 */
bool cargar_paquetes_en_lista(void* paquete,void* lista){
  int estado=lista_insertar((lista_t*)lista,paquete);
  return estado==ERROR;
}

/* Verifica si un numero es primo salteando los primeros 5 numeros, ya que se cubren antes.
 */
bool es_primo(size_t posible_primo){
  if(posible_primo<=1){
    return false;
  }
  if(posible_primo<=3){
    return true;
  }
  if (posible_primo%2==0 || posible_primo%3==0){
    return false;
  }
  for (size_t i=5; i*i<=posible_primo; i+=6){
    if (posible_primo%i == 0 || posible_primo%(i+2) == 0){
      return false;
    }
  }
  return true;
}

/* Buscara el siguiente numero primo al de la capacidad dada, ya que estos ayudan a la dispersion de los elementos.
 */
size_t obtener_nueva_capacidad(size_t capacidad_vieja){
  bool encontrado=false;
  size_t posible_primo=capacidad_vieja;
  while(!encontrado){
    posible_primo++;
    if(es_primo(posible_primo)){
      encontrado=true;
    }
  }
  return posible_primo;
}

/* Creara un conjunto nuevo de arboles con la capacidad obtenida. Si ocurre un error, se cancela el rehash
 * liberando toda la memoria liberada para este proceso. Este nuevo conjunto de arboles es creado con un destructor NULL,
 * ya que despues todavia puede fallar el proceso de rehash y sea necesario borrarlos sin tocar los elementos.
 */
int crear_nuevos_arboles(abb_t** arboles_nuevos,size_t nueva_capacidad,lista_t* lista){
  int i=0,estado=EXITO;
  while(i<nueva_capacidad && estado==EXITO){
    arboles_nuevos[i]=arbol_crear(comparador_de_claves,NULL);
    if(arboles_nuevos[i]==NULL){
      estado=ERROR;
    }
    else{
      i++;
    }
  }
  if(estado==ERROR){
    for(int j=0;j<i;j++){
      arbol_destruir(arboles_nuevos[j]);
    }
    lista_destruir(lista);
    free(arboles_nuevos);
  }
  return estado;
}

/* Carga en el conjunto de nuevos arboles los paquetes utilizando la nueva capacidad del hash. Si ocurre un error
 * se detiene la carga y se procede a cancelar el proceso de rehash, liberando la memoria reservada por la lista y los arboles nuevos
 */
int insertar_en_nuevos_arboles(size_t cantidad_guardada,size_t nueva_capacidad,lista_t* lista,abb_t** arboles_nuevos){
  int i=0,estado=EXITO;
  while(i<cantidad_guardada && estado==EXITO){
    paquete_t* paquete=lista_elemento_en_posicion(lista,0);
    size_t nueva_posicion=hashear(paquete->clave,nueva_capacidad);
    estado=arbol_insertar(arboles_nuevos[nueva_posicion],paquete);
    lista_borrar_de_posicion(lista,0);
    if(estado==EXITO){
          i++;
    }
  }
  if(estado==ERROR){
    for(int j=0;j<i;j++){
      arbol_destruir(arboles_nuevos[j]);
    }
    lista_destruir(lista);
    free(arboles_nuevos);
  }
  return estado;
}

/* Eliminara los arboles viejos, asegurandose de que no se toquen los paquetes, y le asignara al hash su nueva capacidad
 * con sus arboles nuevos. Para esto, se cambia le cambia el destructor a los arboles viejos y se le asigna el destructor a los nuevos.
 */
void poner_en_hash_arboles_nuevos(hash_t* hash,size_t nueva_capacidad,abb_t** arboles_nuevos){
  for(int i=0;i<hash->capacidad;i++){
    hash->arboles[i]->destructor=NULL;
    arbol_destruir(hash->arboles[i]);
  }
  for(int i=0;i<nueva_capacidad;i++){
    arboles_nuevos[i]->destructor=destructor_de_paquetes;
  }

  hash->capacidad=nueva_capacidad;
  free(hash->arboles);
  hash->arboles=arboles_nuevos;
}

/* Se encarga de hacer el rehash completo. Creara los nuevos arboles, pasara los paquetes de los viejos a los nuevos,
 * y eliminara a los viejos. En caso de que ocurra algun error en el proceso, el hash original no se va a tocar.
 */
int pasar_elementos_a_nuevo_hash(hash_t* hash){
  lista_t* lista=lista_crear();
  if(lista==NULL){
    return ERROR;
  }

  for(int i=0;i<hash->capacidad;i++){
    abb_con_cada_elemento(hash->arboles[i],ABB_RECORRER_INORDEN,cargar_paquetes_en_lista,lista);
  }
  if(lista_elementos(lista)!=hash->cantidad){
    lista_destruir(lista);
    return ERROR;
  }

  size_t nueva_capacidad=obtener_nueva_capacidad(hash->capacidad);
  abb_t** arboles_nuevos=malloc(nueva_capacidad*sizeof(abb_t*));
  if(arboles_nuevos==NULL){
    lista_destruir(lista);
    return ERROR;
  }

  int estado=crear_nuevos_arboles(arboles_nuevos,nueva_capacidad,lista);
  if(estado==ERROR){
    return ERROR;
  }

  estado=insertar_en_nuevos_arboles(hash->cantidad,nueva_capacidad,lista,arboles_nuevos);
  if(estado==ERROR){
    return ERROR;
  }
  poner_en_hash_arboles_nuevos(hash,nueva_capacidad,arboles_nuevos);

  lista_destruir(lista);
  return estado;
}


/*
 * Inserta un elemento reservando la memoria necesaria para el mismo.
 * Devuelve 0 si pudo guardarlo o -1 si no pudo.
 */
int hash_insertar(hash_t* hash, const char* clave, void* elemento){
  if(hash==NULL || clave==NULL){
    return ERROR;
  }
  int estado;
  if(es_necesario_rehashear(hash->capacidad,hash->cantidad)){
    estado=pasar_elementos_a_nuevo_hash(hash);
    if(estado==ERROR){
      return ERROR;
    }
  }

  size_t posicion=hashear(clave,hash->capacidad);
  if(!hash_contiene(hash,clave)){
    paquete_t* paquete=crear_paquete(elemento,clave,hash->destructor);
    if(paquete==NULL){
      return ERROR;
    }
    estado=arbol_insertar(hash->arboles[posicion],paquete);
    if(estado==EXITO){
      hash->cantidad++;
    }
  }
  else{
    paquete_t* paquete_nuevo=crear_paquete(elemento,clave,hash->destructor);
    if(paquete_nuevo==NULL){
      return ERROR;
    }
    arbol_borrar(hash->arboles[posicion],paquete_nuevo);
    estado=arbol_insertar(hash->arboles[posicion],paquete_nuevo);
  }
  return estado;
}

/*
 * Quita un elemento del hash e invoca la funcion destructora
 * pasandole dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 si no pudo.
 */
int hash_quitar(hash_t* hash, const char* clave){
  if(hash==NULL || clave==NULL){
    return ERROR;
  }
  size_t posicion=hashear(clave,hash->capacidad);
  paquete_t paquete_a_quitar=crear_paquete_busqueda(clave);
  int estado=arbol_borrar(hash->arboles[posicion],&paquete_a_quitar);
  if(estado==EXITO){
    (hash->cantidad)--;
  }
  return estado;
}

/*
 * Devuelve un elemento del hash con la clave dada o NULL si dicho
 * elemento no existe.
 */
void* hash_obtener(hash_t* hash, const char* clave){
  if(hash==NULL || clave==NULL){
    return NULL;
  }
  size_t posicion=hashear(clave,hash->capacidad);
  paquete_t paquete_a_buscar=crear_paquete_busqueda(clave);
  void* elemento=arbol_buscar(hash->arboles[posicion],&paquete_a_buscar);
  if(elemento==NULL){
    return NULL;
  }
  return ((paquete_t*)elemento)->elemento;
}

/*
 * Devuelve true si el hash contiene un elemento almacenado con la
 * clave dada o false en caso contrario.
 */
bool hash_contiene(hash_t* hash, const char* clave){
  return hash_obtener(hash,clave)!=NULL;
}

/*
 * Devuelve la cantidad de elementos almacenados en el hash.
 */
size_t hash_cantidad(hash_t* hash){
  if(hash==NULL){
    return (size_t)NO_EXISTE;
  }
  return hash->cantidad;
}

/*
 * Destruye el hash liberando la memoria reservada y asegurandose de
 * invocar la funcion destructora con cada elemento almacenado en el
 * hash.
 */
void hash_destruir(hash_t* hash){
  if(hash==NULL){
    return;
  }
  for(int i=0;i<hash->capacidad;i++){
    arbol_destruir(hash->arboles[i]);
  }
  free(hash->arboles);
  free(hash);
}


//------------------FUNCIONES ITERADOR------------------//

/* Iterador externo para el HASH */
struct hash_iter{
  hash_t* hash;
  lista_t* lista;
};

/* Cargara todas las claves en una lista, en caso de que ocurra un error, devolvera true,
 * de forma tal de parar la carga de las claves y poder avisarle al hash de lo ocurrido.
 */
bool cargar_claves_en_lista(void* paquete,void* lista){
  int estado=lista_insertar((lista_t*)lista,(void*)((paquete_t*)paquete)->clave);
  return estado==ERROR;
}


/*
 * Crea un iterador de claves para el hash reservando la memoria
 * necesaria para el mismo. El iterador creado es válido desde su
 * creación hasta que se modifique la tabla de hash (insertando o
 * removiendo elementos);
 *
 * Devuelve el puntero al iterador creado o NULL en caso de error.
 */
hash_iterador_t* hash_iterador_crear(hash_t* hash){
  if(hash==NULL){
    return NULL;
  }

  hash_iterador_t* iterador=malloc(sizeof(hash_iterador_t));
  if(iterador==NULL){
    return NULL;
  }

  lista_t* lista=lista_crear();
  if(lista==NULL){
    free(iterador);
    return NULL;
  }

  iterador->lista=lista;
  iterador->hash=hash;
  for(int i=0;i<hash->capacidad;i++){
    abb_con_cada_elemento(hash->arboles[i],ABB_RECORRER_INORDEN,cargar_claves_en_lista,iterador->lista);
  }
  if(lista_elementos(iterador->lista)!=hash->cantidad){
    lista_destruir(iterador->lista);
    free(iterador);
    return NULL;
  }
  return iterador;
}

/*
 * Devuelve la próxima clave almacenada en el hash y avanza el iterador.
 * Devuelve la clave o NULL si no habia mas.
 */
void* hash_iterador_siguiente(hash_iterador_t* iterador){
  if(iterador==NULL){
    return NULL;
  }
  void* clave=lista_elemento_en_posicion(iterador->lista,0);
  lista_borrar_de_posicion(iterador->lista,0);
  return clave;
}

/*
 * Devuelve true si quedan claves por recorrer o false en caso
 * contrario.
 */
bool hash_iterador_tiene_siguiente(hash_iterador_t* iterador){
  if(iterador==NULL){
    return false;
  }
  return !lista_vacia(iterador->lista);
}

/*
 * Destruye el iterador del hash.
 */
void hash_iterador_destruir(hash_iterador_t* iterador){
  lista_destruir(iterador->lista);
  free(iterador);
}
