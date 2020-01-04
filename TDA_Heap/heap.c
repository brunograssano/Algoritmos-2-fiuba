#include <stdlib.h>
#include "heap.h"

const int EXITO=0,ERROR=-1,MAXIMAL=1,MINIMAL=-1;
const size_t MINIMA_CAPACIDAD=5;
const unsigned FACTOR_AUMENTO_DISMINUCION=2;

struct heap{
  void** elementos;
  size_t tope;
  size_t maxima_cantidad;
  int tipo_heap;
  heap_destructor destructor;
  heap_comparador comparador;
};

///--------------------FUNCIONES AUXILIARES---------------------////

  /* Devolvera la posicion del padre de un elemento
   */
  size_t obtener_posicion_padre(size_t posicion){
    if(posicion==0){
      return 0;
    }
    if(posicion%2==0){
      return (posicion/2-1);
    }
    else{
      return posicion/2;
    }
  }

  /* Intercambiara posiciones en un vector.
   */
  void swap(void** elementos,size_t i,size_t j){
    void* aux=elementos[i];
    elementos[i]=elementos[j];
    elementos[j]=aux;
  }

  /* Realizara sift up dependiendo del tipo de heap que sea, ya sea maximal o minimal,
   * va a comparar con el padre e intercambiar las posiciones de ser necesario.
   */
  void sift_up(void** elementos,size_t posicion,heap_comparador comparador,int tipo_sift_up){
    if(posicion==0){
      return;
    }
    size_t pos_padre=obtener_posicion_padre(posicion);
    if(comparador(elementos[posicion],elementos[pos_padre])==tipo_sift_up){
      swap(elementos,pos_padre,posicion);
      sift_up(elementos,pos_padre,comparador,tipo_sift_up);
    }
  }

  /* Devuelve la posicion del hijo derecho.
   */
  size_t hijo_derecho(size_t posicion){
    return 2*posicion+2;
  }

  /* Devuelve la posicion del hijo izquierdo.
   */
  size_t hijo_izquierdo(size_t posicion){
    return 2*posicion+1;
  }

  /* Obtendra la cantidad de hijos que tenga el padre, para eso necesita de la posicion del padre y de
   * la cantidad guardada de elementos.
   */
  int obtener_cantidad_hijos(size_t posicion,size_t tope){
    if(hijo_derecho(posicion)<tope){
      return 2;
    }
    else if(hijo_izquierdo(posicion)<tope){
      return 1;
    }
    else{
      return 0;
    }
  }

  /* Devolevera el hijo mayor/menor dependiendo el caso viendo el resultado de la comparacion.
   */
  size_t obtener_hijo_indicado(size_t pos_padre,void** elementos,heap_comparador comparador,int tipo_sift_down){
    size_t hijo_izq=hijo_izquierdo(pos_padre);
    size_t hijo_der=hijo_derecho(pos_padre);
    int resultado_comparacion=comparador(elementos[hijo_izq],elementos[hijo_der]);
    if(tipo_sift_down==MAXIMAL){
      return resultado_comparacion>0 ? hijo_izq:hijo_der;
    }
    else{
      return resultado_comparacion>0 ? hijo_der:hijo_izq;
    }
  }

  /* Realiza sift down dependiendo del tipo de heap. Esto se le indica pasandole el resultado esperado por el comparador.
   * El sift down consiste en comparar el hijo mayor o menor con el padre, una vez hecho eso se intercambian o no.
   */
  void sift_down(void** elementos,size_t pos_padre,heap_comparador comparador,size_t tope,int tipo_sift_down){
    int cant_hijos=obtener_cantidad_hijos(pos_padre,tope);
    if(cant_hijos==2){
      size_t hijo_indicado=obtener_hijo_indicado(pos_padre,elementos,comparador,tipo_sift_down);
      if(comparador(elementos[hijo_indicado],elementos[pos_padre])==tipo_sift_down){
        swap(elementos,pos_padre,hijo_indicado);
        sift_down(elementos,hijo_indicado,comparador,tope,tipo_sift_down);
      }
    }
    else if(cant_hijos==1){
      size_t hijo_izq=hijo_izquierdo(pos_padre);
      if(comparador(elementos[hijo_izq],elementos[pos_padre])==tipo_sift_down){
        swap(elementos,pos_padre,hijo_izq);
      }
    }
  }

  /* Convertira un vector en un heap haciendo sift down a partir de las hojas (de fin del vector al inicio), ya que cada hoja cumple
   * con la propiedad de heap.
   */
  void heapify(void** elementos,size_t max_vector,heap_comparador comparador,int tipo_orden){
    for(int i=(int)max_vector;0<=i;i--){
      sift_down(elementos,(size_t)i,comparador,max_vector,tipo_orden);
    }
  }

  /* Aumenta o disminuye el tamanio del vector.
   */
  int redimensionar_heap(void*** elementos,size_t* tamanio,size_t redimension){
    void* auxiliar=realloc(*elementos,redimension*sizeof(void*));
    if(auxiliar==NULL){
      return ERROR;
    }
    (*elementos)=auxiliar;
    (*tamanio)=redimension;
    return EXITO;
  }

///----------------------FUNCIONES DEL HEAP----------------///

  /* Creara la estructura del heap reservando la memoria inicial indicada. El entero que indicara el tipo de heap tiene que ser 1 para MAXIMAL
   * o -1 para MINIMAL.
   * Se debe de incluir tambien un comparador de los elementos que cumpla con lo pedido y un destructor. En caso de que el destructor sea NULL,
   * se esta indicando que no se debe de aplicar.
   * Si ocurre un error durante la creacion se devolvera NULL.
   * El comparador no puede ser NULL.
   */
  heap_t* heap_crear(heap_destructor destructor_elementos,heap_comparador comparador_elementos,size_t min_cant_elementos,int tipo_de_heap){
    if((tipo_de_heap!=MAXIMAL && tipo_de_heap!=MINIMAL) || comparador_elementos==NULL){
      return NULL;
    }

    heap_t* heap=malloc(sizeof(heap_t));
    if(heap==NULL){
      return NULL;
    }
    heap->elementos=calloc(min_cant_elementos,sizeof(void*));
    if(heap->elementos==NULL){
      free(heap);
      return NULL;
    }

    heap->tope=0;
    heap->tipo_heap=tipo_de_heap;
    heap->maxima_cantidad=min_cant_elementos;
    heap->destructor=destructor_elementos;
    heap->comparador=comparador_elementos;

    return heap;
  }

  /* Devolvera el elemento ubicado en la primera posicion. El maximo si es maximal o minimo si es minimal.
   */
  void* heap_ver_primer_elemento(heap_t* heap){
    if(heap==NULL || heap->tope==0){
      return NULL;
    }
    return heap->elementos[0];
  }

  /* Insertara un elemento en el heap. Devuelve 0 si tuvo exito, caso contrario devolvera -1.
   */
  int heap_insertar(heap_t* heap,void* elemento){
    if(heap==NULL){
      return ERROR;
    }

    if(heap->tope==heap->maxima_cantidad){
      int estado=redimensionar_heap(&(heap->elementos),&(heap->maxima_cantidad),FACTOR_AUMENTO_DISMINUCION*heap->tope);
      if(estado==ERROR){
        return ERROR;
      }
    }

    heap->elementos[heap->tope]=elemento;
    sift_up(heap->elementos,heap->tope,heap->comparador,heap->tipo_heap);
    heap->tope++;

    return EXITO;
  }

  /* Eliminara el primer elemento, ya sea el maximo o minimo invocando al destructor de ser necesario.
   * Devolvera 0 si salio bien, o -1 si ocurrio un error.
   */
  int heap_eliminar_primero(heap_t* heap){
    if(heap==NULL || heap->tope==0){
      return ERROR;
    }

    if(heap->tope<(heap->maxima_cantidad/FACTOR_AUMENTO_DISMINUCION) && MINIMA_CAPACIDAD<heap->tope){
      int estado=redimensionar_heap(&(heap->elementos),&(heap->maxima_cantidad),heap->maxima_cantidad/FACTOR_AUMENTO_DISMINUCION);
      if(estado==ERROR){
        return ERROR;
      }
    }

    if(heap->destructor!=NULL){
      heap->destructor(heap->elementos[0]);
    }
    heap->elementos[0]=heap->elementos[heap->tope-1];
    heap->elementos[heap->tope-1]=NULL;
    heap->tope--;
    sift_down(heap->elementos,0,heap->comparador,heap->tope,heap->tipo_heap);

    return EXITO;
  }

  /* Devuelve la cantidad de elementos almacenados en el heap.
   */
  size_t heap_cantidad(heap_t* heap){
    if(heap==NULL){
      return 0;
    }
    return heap->tope;
  }

  /* Ordena un vector mediante heapsort. Esto lo hace inplace.
   * Necesita del comparador y que se le indique el tipo de orden (MAXIMAL==1|MINIMAL==-1)
   */
  void heapsort(void** elementos,size_t max_vector,heap_comparador comparador,int tipo_orden){
    if(elementos==NULL || comparador==NULL){
      return;
    }
    heapify(elementos,max_vector,comparador,tipo_orden);
    size_t raiz=0;
    while (max_vector>0){
      swap(elementos,raiz,max_vector-1);
      max_vector--;
      sift_down(elementos,raiz,comparador,max_vector,tipo_orden);
    }
  }

  /* Destruira toda le memoria utilizada e invocara al destructor de ser necesario.
   */
  void heap_destruir(heap_t* heap){
    if(heap==NULL){
      return;
    }
    if(heap->destructor!=NULL){
      for(size_t i=0;i<heap->tope;i++){
        heap->destructor(heap->elementos[i]);
      }
    }
    free(heap->elementos);
    free(heap);
  }
