#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "juego_de_tronos.h"

#define FORMATO_CASAS "%[^;];%zu;%zu\n"
#define FORMATO_PERSONAS "%[^;];%zu\n"
#define LECTURA "r"
#define NOMBRE_ARCHIVO "casas_juego.txt"
#define ARCHIVO_NACIMIENTOS "nombres_nacimientos.txt"

const char CASA='C';
const size_t SIN_NACIMIENTOS=0;
const int EDAD_MAXIMA=60;
const int ERROR=-1,EXITO=0;
const int ES_MAYOR=1,SON_IGUALES=0,ES_MENOR=-1;
#define MAX_NOMBRE 50


typedef struct persona{
  char nombre[MAX_NOMBRE];
  size_t edad;
}persona_t;

typedef struct casa{
  char nombre_casa[MAX_NOMBRE];
  size_t factor_envejecimiento;
  size_t factor_nacimiento;
  lista_t* personas;
}casa_t;

///--------------FUNCIONES AUXILIARES-------------///

  /* Funcion que se utiliza para comparar casas. En la comparacion toma el nombre de las mismas.
   * Si el primero es mayor devuelve 1, si es menor -1,
   * si son iguales devuelve 0.
   */
  int comparador_de_casas(void* casa1,void* casa2){
  	if(strcmp(((casa_t*)casa1)->nombre_casa,((casa_t*)casa2)->nombre_casa)>0){
  		return ES_MAYOR;
  	}
  	else if(strcmp(((casa_t*)casa1)->nombre_casa,((casa_t*)casa2)->nombre_casa)<0){
  		return ES_MENOR;
  	}
  	else{
  		return SON_IGUALES;
  	}
  }

  /* Se encargara de liberar la memoria que se usa para guardar a una persona
   */
  void destructor_de_personas(void* persona){
    free(persona);
  }

  /* Liberara la memoria que ocupa una casa entera. Es decir, la memoria que ocupan las personas en la lista,
   * la lista, y la casa misma.
   */
  void destructor_de_casas(void* casa){
    lista_con_cada_elemento(((casa_t*)casa)->personas,destructor_de_personas);
    lista_destruir(((casa_t*)casa)->personas);
    free(casa);
  }

  /* El archivo es de texto y se tiene que encontrar abierto y con el formato esperado para casa_t.
   */
  int leer_casas(FILE* archivo_casas,casa_t* casa){
    return fscanf(archivo_casas,FORMATO_CASAS,casa->nombre_casa,&(casa->factor_envejecimiento),&(casa->factor_nacimiento));
  }

  /* El archivo esta abierto y es de texto. Este archivo tendra el formato esperado para leer un persona_t.
   */
  int leer_personas(FILE* archivo_personas,persona_t* persona){
    return fscanf(archivo_personas,FORMATO_PERSONAS,persona->nombre,&(persona->edad));
  }

  /* Leera el primer caracter de un archivo de texto que se tiene que encontrar abierto.
   */
  int leer_incio(FILE* archivo,char* inicio){
    return fscanf(archivo,"%c;",inicio);
  }

  /* Creara la estructura de una casa en memoria. Si ocurre un error devolvera NULL.
   * Esta estructura tambien tiene una lista que se encuentra en memoria.
   */
  casa_t* crear_casa(casa_t casa){
    casa_t* casa_en_memoria=malloc(sizeof(casa_t));
    if(casa_en_memoria==NULL){
      return NULL;
    }
    strcpy(casa_en_memoria->nombre_casa,casa.nombre_casa);
    casa_en_memoria->factor_nacimiento=casa.factor_nacimiento;
    casa_en_memoria->factor_envejecimiento=casa.factor_envejecimiento;
    casa_en_memoria->personas=lista_crear();
    if(casa_en_memoria->personas==NULL){
      free(casa_en_memoria);
      return NULL;
    }
    return casa_en_memoria;
  }

  /* Creara una persona en memoria dinamica. Si sucede un error en la creacion devuelve NULL.
   */
  persona_t* crear_persona(persona_t persona){
    persona_t* persona_en_memoria=malloc(sizeof(persona_t));
    if(persona_en_memoria==NULL){
      return NULL;
    }
    strcpy(persona_en_memoria->nombre,persona.nombre);
    persona_en_memoria->edad=persona.edad;
    return persona_en_memoria;
  }

  /* Insertara una persona en una lista. Si logra insertar y crear bien a la persona, devuelve 0
   * caso contrario, devuelve -1 y borra a la persona que creo y no pudo insertar, de forma tal de no perder esa memoria.
   */
  int insertar_persona(lista_t* lista_personas,persona_t persona_a_agregar){
    int estado;
    persona_t* persona=crear_persona(persona_a_agregar);
    if(persona==NULL){
      estado=ERROR;
    }
    else{
      estado=lista_insertar(lista_personas,persona);
      if(estado==ERROR){
        destructor_de_personas(persona);
      }
    }
    return estado;
  }

  /* Leera una persona y la agregara a la lista de la casa a la que pertenece.
   * Devuelve 0 si salio todo bien, caso contrario, devolvera -1.
   */
  int agregar_persona(FILE* archivo_casas,lista_t* personas){
    persona_t persona_leida;
    leer_personas(archivo_casas,&persona_leida);
    return insertar_persona(personas,persona_leida);
  }

///--------------FUNCIONES INICIALIZAR-------------///

  /* Leera todas las casas que se encuentren en el archivo de texto enviado.
   * Este archivo se encuentra abierto. Necesita tambien del arbol con las casas ya creado y
   * la cantidad de casas guardadas hasta el momento en el juego, de forma tal de ir aumentando su cantidad.
   * Si ocurre un error cargando una casa, la casa que no se pudo cargar es destruida, y se enviara -1 como estado.
   * Si todo sale bien, se envia 0.
   */
  int cargar_casas(FILE* file_casas,abb_t* casas,int* cantidad_casas){
    casa_t casa_leida;
    casa_t* casa_en_memoria=NULL;
    int estado = EXITO;
    char inicio;
    int leidos = leer_incio(file_casas,&inicio);
    while(0<leidos && estado == EXITO){
      if(inicio==CASA){
        leer_casas(file_casas,&casa_leida);
        casa_en_memoria = crear_casa(casa_leida);
        if(casa_en_memoria==NULL){
          estado=ERROR;
        }
        else{
          estado=arbol_insertar(casas,casa_en_memoria);
          if(estado==EXITO){
            (*cantidad_casas)++;
          }
          else{
            destructor_de_casas(casa_en_memoria);
          }
        }
      }
      else{
        estado=agregar_persona(file_casas,casa_en_memoria->personas);
      }
      leidos = leer_incio(file_casas,&inicio);
    }
    return estado;
  }

  /* Cargara todos los nombres y edades (0) de las personas sin nacer, de forma tal de que queden en una lista y poder acceder ella
   * sin tener que realizar varias lecturas en el disco.
   * El archivo tiene que ser de texto, y estar abierto.
   */
  int cargar_nombres_nacimientos(FILE* file_nacimientos,lista_t* personas_nacimientos){
    persona_t persona_temporal;
    int estado=EXITO;
    int leidos=leer_personas(file_nacimientos,&persona_temporal);
    while(0<leidos && estado==EXITO){
      estado=insertar_persona(personas_nacimientos,persona_temporal);
      leidos=leer_personas(file_nacimientos,&persona_temporal);
    }
    return estado;
  }

  /* Creara las estructuras necesarias pera el correcto funcionamiento del juego.
   * Si alguna falla, la memoria sera libera y se devolve ERROR.
   */
  int crear_estructuras(juego_t* juego){
    juego->casas=arbol_crear(comparador_de_casas,destructor_de_casas);
    if(juego->casas==NULL){
      return ERROR;
    }

    juego->casas_extintas=cola_crear();
    if(juego->casas_extintas==NULL){
      destruir_juego(*juego);
      return ERROR;
    }

    juego->nombres_nacimientos=lista_crear();
    if(juego->nombres_nacimientos==NULL){
      destruir_juego(*juego);
      return ERROR;
    }
    return EXITO;
  }

  /* Se encarga de crear el juego y dejarlo en un estado valido.
   * Leera todas las casas y las cargara a un ABB.
   * En caso de que ocurra un error durante su creacion liberara la memoria tomada y devolvera
   * mediante un entero -1, caso contrario sera 0.
   */
  int inicializar_juego(juego_t* juego){
    srand((unsigned)time(NULL));
    FILE* file_casas=fopen(NOMBRE_ARCHIVO,LECTURA);
    if(file_casas==NULL){
      printf("***Error abriendo el archivo inicial***\n");
      return ERROR;
    }

    FILE* file_nacimientos=fopen(ARCHIVO_NACIMIENTOS,LECTURA);
    if(file_nacimientos==NULL){
      fclose(file_casas);
      printf("***Error abriendo el archivo con los nombres de nacimientos***\n");
      return ERROR;
    }

    int estado=crear_estructuras(juego);
    if(estado==ERROR){
      fclose(file_nacimientos);
      fclose(file_casas);
      return ERROR;
    }

    estado=cargar_nombres_nacimientos(file_nacimientos,juego->nombres_nacimientos);
    if(estado==ERROR){
      fclose(file_nacimientos);
      fclose(file_casas);
      destruir_juego(*juego);
      return ERROR;
    }

    juego->cantidad_casas=0;
    estado=cargar_casas(file_casas,juego->casas,&(juego->cantidad_casas));
    if(estado==ERROR){
      destruir_juego(*juego);
    }

    fclose(file_nacimientos);
    fclose(file_casas);
    return estado;
  }

///--------------FUNCIONES SIMULACION-------------///

  /* Pedira una cantidad de anios al usuario por consola.
   */
  void pedir_cantidad_de_anios(unsigned* anios_simulacion){
    printf("\nIngrese la cantidad de anios que quiere que dure la simulacion.\n\n");
    printf("-------->");
    scanf("%u", anios_simulacion);
  }

  /* Sumara a cada persona de una casa el factor de envejecimiento. Si esta persona tiene mas de 60 anios es eliminada de la lista.
   * En caso de que la lista se quede vacia (murieron todas las personas), La casa pasara a estar en una cola de casas extintas.
   * No se utiliza el iterador de la lista ya que se le realizan modificaciones a la lista, dejandolo invalido.
   */
  bool aplicar_muertes(void* casa_void,void* casas_extintas_void,void* extra){
    casa_t* casa=casa_void;
    cola_t* casas_extintas=casas_extintas_void;
    size_t posicion=0;
    size_t cantidad_personas=lista_elementos(casa->personas);
    while(posicion<cantidad_personas){
      persona_t* persona=lista_elemento_en_posicion(casa->personas,posicion);
      persona->edad+=casa->factor_envejecimiento;
      if(persona->edad>=EDAD_MAXIMA){
        destructor_de_personas(persona);
        lista_borrar_de_posicion(casa->personas,posicion);
        cantidad_personas--;
        posicion--;
      }
      posicion++;
    }
    if(cantidad_personas==0){
      cola_encolar(casas_extintas,casa);
    }
    return false;
  }

  /* Realizara el calculo para saber cuantas personas tienen que nacer en una determinada casa.
  */
  size_t obtener_cantidad_nuevas_personas(casa_t* casa){
    if(casa->factor_nacimiento==SIN_NACIMIENTOS){
      return SIN_NACIMIENTOS;
    }
    size_t cantidad_integrantes=lista_elementos(casa->personas);
    return cantidad_integrantes/(casa->factor_nacimiento);
  }

  /* Devuelve una posicion de un nombre en el archivo. Para eso, requiere de la cantidad de nombres que tiene guardados.
   */
  size_t obtener_posicion(size_t cantidad_nombres){
    if(cantidad_nombres==0){
      return 0;
    }
    return (size_t)rand()%cantidad_nombres;
  }

  /* Se encargara de agregar a las personas que van naciendo en cada casa.
   * Para ello, recibe una lista con personas sin nacer.
   * Si ocurre un error, se cambiara la variable extra a tal estado, notificando a la simulacion.
   */
  bool aplicar_nacimientos(void* casa,void* estado_void,void* nombres_nacimientos){
    lista_t* personas_nacimientos=nombres_nacimientos;
    int* estado=estado_void;
    size_t cantidad_a_nacer=obtener_cantidad_nuevas_personas((casa_t*)casa);
    if(cantidad_a_nacer==0){
      return false;
    }

    int i=0;
    size_t cantidad_nombres=lista_elementos(personas_nacimientos);
    while(i<cantidad_a_nacer && (*estado==EXITO)){
      size_t posicion_nombre=obtener_posicion(cantidad_nombres);
      persona_t* persona_a_nacer=lista_elemento_en_posicion(personas_nacimientos,posicion_nombre);
      (*estado)=insertar_persona(((casa_t*)casa)->personas,*persona_a_nacer);
      i++;
    }

    return (*estado)==ERROR;
  }

  /* Compara la cantidad de integrantes de dos casas. Si todavia no se definio cual es la casa ganadora
   * la casa actual pasara a serlo.
   */
  bool buscar_ganador(void* casa_actual_void,void* casa_ganadora_void,void* extra){
    casa_t* casa_ganadora=casa_ganadora_void;
    casa_t* casa_actual=casa_actual_void;
    if(strcmp(casa_ganadora->nombre_casa,"SIN GANADOR")==0){
      strcpy(casa_ganadora->nombre_casa,casa_actual->nombre_casa);
      casa_ganadora->personas=casa_actual->personas;
    }
    else if(lista_elementos(casa_actual->personas)>lista_elementos(casa_ganadora->personas)){
      strcpy(casa_ganadora->nombre_casa,casa_actual->nombre_casa);
      casa_ganadora->personas=casa_actual->personas;
    }
    return false;
  }

  /* Buscara en el arbol la casa con mas integrantes. En caso de que no haya ganador, sera devuelta una casa
   * con el nombre indicandolo.
   */
  casa_t buscar_casa_con_mas_integrantes(abb_t* casas){
    casa_t casa_ganadora;
    strcpy(casa_ganadora.nombre_casa,"SIN GANADOR");
    abb_con_cada_elemento(casas,ABB_RECORRER_INORDEN,buscar_ganador,&casa_ganadora,NULL);
    return casa_ganadora;
  }

  /* Quitara del arbol las casas que se extinguieron. Para ello las saca de la cola y las vuelve a encolar.
   * Si la encolo sin error devuelta, procede a borrarla del arbol. En caso de que ocurriese un error, la referencia
   * a esa casa no se perderia.
   * Durante el proceso se cambia temporalmente el destructor del arbol para evitar
   * que se destruya la casa extinta.
   * La funcion devolvera el estado, este puede ser 0 si todo salio bien o -1 si ocurrio un error.
   */
  int quitar_del_arbol_casas_extintas(abb_t* casas,cola_t* casas_extintas,int* casas_vivas){
    int i=0,borro_casa,estado=EXITO;
    int cantidad_casas_extintas=cola_cantidad(casas_extintas);
    casas->destructor=NULL;
    while(i<cantidad_casas_extintas && estado==EXITO){
      casa_t* casa_extinta=cola_primero(casas_extintas);
      cola_desencolar(casas_extintas);
      estado=cola_encolar(casas_extintas,casa_extinta);
      if(estado==EXITO){
        borro_casa=arbol_borrar(casas,casa_extinta);
        if(borro_casa==EXITO){
          (*casas_vivas)--;
        }
      }
      i++;
    }
    casas->destructor=destructor_de_casas;
    return estado;
  }

  /* Ejecutara la simulacion con la cantidad de anios indicada por el usuario. Al final de la simulacion, devolvera la casa con mas integrantes.
   */
  casa_t ejecutar_simulacion(unsigned anios_simulacion,abb_t* casas,cola_t* casas_extintas,lista_t* personas_nacimientos,int* casas_vivas){
    unsigned i=0;
    int estado=EXITO;
    while(i<anios_simulacion && estado==EXITO){
      abb_con_cada_elemento(casas,ABB_RECORRER_INORDEN,aplicar_muertes,casas_extintas,NULL);
      estado=quitar_del_arbol_casas_extintas(casas,casas_extintas,casas_vivas);
      if(estado==EXITO){
        abb_con_cada_elemento(casas,ABB_RECORRER_INORDEN,aplicar_nacimientos,&estado,personas_nacimientos);
      }
      i++;
    }
    if(estado!=EXITO){
      printf("\n***Ocurrio un error en la simulacion***\n");
    }
    return buscar_casa_con_mas_integrantes(casas);
  }

  /* Mostrara por pantalla la casa que haya quedado con mas miembros.
   * Si no quedo alguna casa se mostrara tambien un mensaje indicandolo.
   */
  void mostrar_ganador(unsigned anios_simulacion,casa_t casa_ganadora){
    if(strcmp(casa_ganadora.nombre_casa,"SIN GANADOR")==0){
      printf("\nNinguna casa a logrado sobrevivir a los conflictos que sucedieron en Westeros durante estos anios, el trono ha quedado vacio\n");
    }
    else{
      printf("\nLa casa que se ha quedado con el trono de hierro despues de estos %u anios fue la casa %s\n",anios_simulacion,casa_ganadora.nombre_casa);
      printf("La casa se quedo con el trono al tener %zu miembros\n",lista_elementos(casa_ganadora.personas));
    }
  }

  /* Se encargara de ejecutar la simulacion del juego.
   * Para ello, se le preguntara al usuario una cantidad de anios a transcurrir.
   * Pasados los anios mostrara por pantalla la casa que controla el trono de hierro.
   */
  void iniciar_simulacion(juego_t* juego){
    unsigned anios_simulacion;
    pedir_cantidad_de_anios(&anios_simulacion);
    casa_t casa_ganadora=ejecutar_simulacion(anios_simulacion,juego->casas,juego->casas_extintas,juego->nombres_nacimientos,&(juego->cantidad_casas));
    mostrar_ganador(anios_simulacion,casa_ganadora);
  }

///--------------FUNCIONES AGREGAR CASAS-------------///

  /* Pedira al usuario el nombre del archivo de donde desea cargar una nueva casa.
   * El nombre de este archivo no debe contener espacios.
   */
  void pedir_nombre_archivo(char nombre_archivo[MAX_NOMBRE]){
    printf("\nIngrese el nombre del archivo donde se encuentra la casa que quiere agregar.\n");
    printf("Si la casa ya existe, se cargaran los miembros que contenga el archivo.\n");
    printf("\n------->");
    scanf("%s",nombre_archivo);
  }

  /* Agregara la casa leida al arbol si esta no se encuentra.
   * Si la casa ya esta cargada, agregara las personas que lea en la lista de personas.
   * Devolvera un entero representando el estado, 0 si salio todo bien, -1 si fallo.
   */
  int agregar_casa(FILE* archivo_casa,abb_t* casas,int* cantidad_casas){
    char inicio;
    casa_t casa_leida;
    int estado=EXITO;
    int leidos=leer_incio(archivo_casa,&inicio);
    if(0<leidos){
      leidos=leer_casas(archivo_casa,&casa_leida);
      casa_t* casa_a_agregar=arbol_buscar(casas,&casa_leida);
      if(casa_a_agregar==NULL){
        fseek(archivo_casa,0,SEEK_SET);
        estado=cargar_casas(archivo_casa,casas,cantidad_casas);
      }
      else{
        leidos=leer_incio(archivo_casa,&inicio);
        while(0<leidos && estado==EXITO){
          estado=agregar_persona(archivo_casa,casa_a_agregar->personas);
          leidos=leer_incio(archivo_casa,&inicio);
        }
      }
    }
    return estado;
  }

  /* Agregara una casa al arbol. Esta va a surgir de un nombre de un archivo que da el usuario
   * Si la casa a agregar ya existe, se le suman los integrantes a la casa ya creada.
   */
  void agregar_casa_al_arbol(juego_t* juego){
    char nombre_archivo[MAX_NOMBRE];
    pedir_nombre_archivo(nombre_archivo);

    FILE* archivo_casa=fopen(nombre_archivo,LECTURA);
    if(archivo_casa==NULL){
      printf("\n***No se pudo abrir el achivo indicado***\n");
      return;
    }

    int estado=agregar_casa(archivo_casa,juego->casas,&(juego->cantidad_casas));
    if(estado==EXITO){
      printf("\n*Se agrego exitosamente la casa a la simulacion\n");
    }
    else{
      printf("\n***Ocurrio un error agregando la casa***\n");
    }

    fclose(archivo_casa);
  }

///--------------FUNCIONES LISTAR CASAS-------------///

  /* Hace el intercambio de posiciones en un vector de casas
   */
  void swap(casa_t** vector_casas,int i,int j){
    casa_t* aux=vector_casas[i];
    vector_casas[i]=vector_casas[j];
    vector_casas[j]=aux;
  }

  /* Devuelve la posicion del pivote en el vector mandado.
   */
  int pivotear(casa_t** vector_casas,int inicio,int fin){
    int pos_pivote=inicio;
    size_t valor_pivote=lista_elementos(vector_casas[fin]->personas);
    for(int i=inicio;i<fin;i++){
      if(lista_elementos(vector_casas[i]->personas)>valor_pivote){
        swap(vector_casas,pos_pivote,i);
        pos_pivote++;
      }
    }
    swap(vector_casas,pos_pivote,fin);

    return pos_pivote;
  }

  /* Realizara QuickSort en el vector de casas, ordenandolo de mayor a menor.
   */
  void quick_sort(casa_t** vector_casas,int inicio,int fin){
    if(inicio>=fin){
      return;
    }
    int pivote=pivotear(vector_casas,inicio,fin);
    quick_sort(vector_casas,inicio,pivote-1);
    quick_sort(vector_casas,pivote+1,fin);
  }

  /* Ordenada un vector de casas de mayor a menor analizando la cantidad de miembros.
   */
  void ordenar_casas_por_miembros(casa_t** vector_casas,int cantidad_casas){
    quick_sort(vector_casas,0,cantidad_casas-1);
  }

  /* Mostrara por pantalla una lista de las casas ordenadas por cantidad de miembros.
   */
  void mostrar_casas_ordenadas(casa_t** vector_casas,int cantidad_casas){
    printf("\nEstas son las casas ordenadas por la cantidad de miembros en forma descendente:\n\n");
    for(int i=0;i<cantidad_casas;i++){
      printf("---->Casa %s con %zu miembros\n\n",vector_casas[i]->nombre_casa, lista_elementos(vector_casas[i]->personas));
    }
  }

  /* Listara las casas por cantidad de integrantes en orden descendente.
   * Si ocurre un error creando el vector, se le indicara al usuario de lo ocurrido.
   */
  void listar_casas_en_orden(juego_t juego){
    if(juego.cantidad_casas==0){
      printf("\nNo han quedado casas vivas, nadie a sobrevivido a estos crueles anios de guerras y traiciones en Westeros.\n");
      return;
    }

    casa_t** vector_casas=malloc((unsigned)juego.cantidad_casas*sizeof(casa_t*));
    if(vector_casas==NULL){
      printf("\n***Ocurrio un error listando las casas***\n");
      return;
    }

    arbol_recorrido_inorden(juego.casas,(void**)vector_casas,juego.cantidad_casas);
    ordenar_casas_por_miembros(vector_casas,juego.cantidad_casas);
    mostrar_casas_ordenadas(vector_casas,juego.cantidad_casas);

    free(vector_casas);
  }

///--------------MOSTRAR Y DESTRUIR-------------///

  /* Preguntara al usuario el nombre de una casa, de la cual se mostraran los miembros que contiene.
   */
  casa_t preguntar_casa(){
    casa_t casa;
    printf("\nIngrese el nombre de la casa de la que quiere ver los miembros\n");
    scanf("%s",casa.nombre_casa);
    return casa;
  }

  /* Mustra el nombre y edad de una persona.
   */
  void mostrar_persona(void* persona){
    printf("--->Miembro %s con edad %zu\n", ((persona_t*)persona)->nombre,((persona_t*)persona)->edad);
  }

  /* Mostrara los miembros de una casa ingresada por el usuario.
   */
  void mostrar_miembros_casa(juego_t juego){
    casa_t casa_busqueda=preguntar_casa();
    casa_t* casa=arbol_buscar(juego.casas,&casa_busqueda);
    if(casa==NULL){
      printf("***No se encuentra la casa en el arbol.***\n");
    }
    else{
      printf("\nMiembros de la casa %s\n",casa->nombre_casa);
      lista_con_cada_elemento(casa->personas,mostrar_persona);
    }
  }

  /* Mostrara las casas extintas en el orden en que fueron desapareciendo.
   * Una vez mostradas son eliminadas las casas, no se mantienen.
   */
  void mostrar_casas_extintas(juego_t juego){
    if(cola_vacia(juego.casas_extintas)){
      printf("\nNo se extinguio ninguna casa, estos fueron unos anios pacificos en Westeros\n");
    }
    else{
      printf("\nLas casas extintas son las siguientes:\n");
      while(!cola_vacia(juego.casas_extintas)){
        casa_t* casa_extinta=cola_primero(juego.casas_extintas);
        cola_desencolar(juego.casas_extintas);
        printf("---->%s\n",casa_extinta->nombre_casa);
        destructor_de_casas(casa_extinta);
      }
    }
  }

  /* Destruira la memoria que haya sido reservada por el juego por alguna de las estructuras creadas.
   */
  void destruir_juego(juego_t juego){
    arbol_destruir(juego.casas);

    while(!cola_vacia(juego.casas_extintas)){
      casa_t* casa_extinta=cola_primero(juego.casas_extintas);
      cola_desencolar(juego.casas_extintas);
      destructor_de_casas(casa_extinta);
    }
    cola_destruir(juego.casas_extintas);

    lista_con_cada_elemento(juego.nombres_nacimientos,destructor_de_personas);
    lista_destruir(juego.nombres_nacimientos);
  }
