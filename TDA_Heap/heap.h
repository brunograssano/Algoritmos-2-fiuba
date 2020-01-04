
typedef struct heap heap_t;

/*
 * Destructor de elementos. Cuando se quiera eliminar el heap se invocara este destructor.
 */
typedef void (*heap_destructor)(void*);

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, 1 si el primer elemento es mayor al
 * segundo o -1 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);


/* Creara la estructura del heap reservando la memoria inicial indicada. El entero que indicara el tipo de heap tiene que ser 1 para MAXIMAL
 * o -1 para MINIMAL.
 * Se debe de incluir tambien un comparador de los elementos que cumpla con lo pedido y un destructor. En caso de que el destructor sea NULL,
 * se esta indicando que no se debe de aplicar.
 * Si ocurre un error durante la creacion se devolvera NULL.
 * El comparador no puede ser NULL.
 */
heap_t* heap_crear(heap_destructor destructor_elementos,heap_comparador comparador_elementos,size_t min_cant_elementos,int tipo_de_heap);

/* Devolvera el elemento ubicado en la primera posicion. El maximo si es maximal, o minimo si es minimal.
 */
void* heap_ver_primer_elemento(heap_t* heap);

/* Insertara un elemento en el heap. Devuelve 0 si tuvo exito, caso contrario devolvera -1.
 */
int heap_insertar(heap_t* heap,void* elemento);

/* Eliminara el primer elemento, ya sea el maximo o minimo invocando al destructor de ser necesario.
 * Devolvera 0 si salio bien, o -1 si ocurrio un error.
 */
int heap_eliminar_primero(heap_t* heap);

/* Devuelve la cantidad de elementos almacenados en el heap.
 */
size_t heap_cantidad(heap_t* heap);

/* Ordena un vector mediante heapsort. Esto lo hace inplace.
 * Necesita del comparador y que se le indique el tipo de orden (MAXIMAL==1|MINIMAL==-1)
 */
void heapsort(void** elementos,size_t max_vector,heap_comparador comparador,int tipo_orden);

/* Destruira toda le memoria utilizada e invocara al destructor de ser necesario.
 */
void heap_destruir(heap_t* heap);
