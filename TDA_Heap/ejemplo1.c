#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "heap.h"
#include "mi_assert.h"
#define MAXIMO 500
#define EXITO 0
#define ERROR -1
#define MAXIMAL 1
#define MINIMAL -1

///--------------------FUNCIONES AUXILIARES--------------///
/* Compara dos enteros, si el primero es mayor devuelve 1, -1 si es menor o 0 si son iguales.
 */
int comparador_enteros(void* elemento1,void* elemento2){
  int* entero1=elemento1;
  int* entero2=elemento2;
  if(*entero1>*entero2){
    return 1;
  }
  else if(*entero1<*entero2){
    return -1;
  }
  else{
    return 0;
  }
}

/* Compara dos caracteres, si el primero es mayor devuelve 1, -1 si es menor o 0 si son iguales.
 */
int comparador_caracteres(void* elemento1,void* elemento2){
  char* caracter1=elemento1;
  char* caracter2=elemento2;
  if(*caracter1>*caracter2){
    return 1;
  }
  else if(*caracter1<*caracter2){
    return -1;
  }
  else{
    return 0;
  }
}

/* Inserta enteros hasta el tope indicado.
 */
void insertar_enteros(heap_t* heap,int enteros[MAXIMO],int tope){
  for(int i=0;i<tope;i++){
    heap_insertar(heap,&enteros[i]);
  }
}

/* Inserta caracteres hasta el tope indicado.
 */
void insertar_caracteres(heap_t* heap,char* letras,int tope){
  for(int i=0;i<tope;i++){
    heap_insertar(heap,&letras[i]);
  }
}

/* Borra varias veces del heap. Hay que indicarle la cantidad.
 */
void borrar_varias_veces(heap_t* heap,int cant_a_borrar){
  for (int i = 0; i < cant_a_borrar; i++) {
    heap_eliminar_primero(heap);
  }
}

/* Carga un vector con numeros enteros generados de forma semirandom. La funcion necesita un tope que sea positivo.
 */
void cargar_enteros(int enteros[MAXIMO],int tope){
	for(int i=0;i<tope;i++){
		enteros[i]=rand()%MAXIMO;
	}
}

///--------------------FUNCIONES DE EJEMPLOS--------------///

/* Evalua las funciones del heap con enteros
 */
void pruebas_con_enteros(){
  int pruebas_pasadas=0,pruebas=16;
  int enteros[12]={10,5,9,4,3,8,8,3,5,4,11,12};
  int enteros_ordenados_may_a_men[12]={12,11,10,9,8,8,5,5,4,4,3,3};
  int enteros_ordenados_men_a_may[12]={3,3,4,4,5,5,8,8,9,10,11,12};
  printf("\nCreo un heap maximal\n");
  heap_t* heap=heap_crear(NULL,comparador_enteros,12,MAXIMAL);

  insertar_enteros(heap,enteros,12);
  assert(heap_cantidad(heap)==12,"Hay 12 elementos en el heap",pruebas_pasadas);
  assert(*(int*)heap_ver_primer_elemento(heap)==12,"El primer elemento del heap es el 12",pruebas_pasadas);
  assert(heap_eliminar_primero(heap)==EXITO,"Elimino el primer elemento del heap",pruebas_pasadas);
  assert(*(int*)heap_ver_primer_elemento(heap)==11,"El primer elemento es el 11",pruebas_pasadas);
  assert(heap_eliminar_primero(heap)==EXITO,"Elimino el 11 del heap",pruebas_pasadas);
  assert(*(int*)heap_ver_primer_elemento(heap)==10,"Espero que el primer elemento sea el 10",pruebas_pasadas);
  assert(heap_cantidad(heap)==10,"El heap tiene 10 elementos",pruebas_pasadas);

  heap_destruir(heap);

  printf("\nCreo otro heap, en este caso minimal\n");
  heap=heap_crear(NULL,comparador_enteros,12,MINIMAL);
  insertar_enteros(heap,enteros,12);

  assert(heap_cantidad(heap)==12,"Hay 12 elementos en el heap minimal",pruebas_pasadas);
  assert(*(int*)heap_ver_primer_elemento(heap)==3,"El primer elemento del heap es el 3",pruebas_pasadas);
  assert(heap_eliminar_primero(heap)==EXITO,"Elimino el primer elemento del heap",pruebas_pasadas);
  assert(*(int*)heap_ver_primer_elemento(heap)==3,"El primer elemento del heap es otro 3",pruebas_pasadas);
  printf("Borro un par de elementos\n");
  borrar_varias_veces(heap,3);
  assert(*(int*)heap_ver_primer_elemento(heap)==5,"El primer elemento del heap es el 5",pruebas_pasadas);
  assert(heap_cantidad(heap)==8,"El heap tiene 8 elementos",pruebas_pasadas);
  printf("Borro hasta que quede uno\n");
  borrar_varias_veces(heap,7);
  assert(*(int*)heap_ver_primer_elemento(heap)==12,"El elemento que queda es un 12",pruebas_pasadas);
  heap_destruir(heap);

  printf("\nPruebo el heapsort pasandole los enteros anteriores. (De mayor a menor)\n");
  int* enteros_en_heapsort[12];
  for(int i=0;i<12;i++){
    enteros_en_heapsort[i]=&enteros[i];
  }
  heapsort((void**)enteros_en_heapsort,12,comparador_enteros,MINIMAL);
  assert_vectores(enteros_en_heapsort,enteros_ordenados_may_a_men,12,"Se obtuvo el vector esperado",pruebas_pasadas);

  printf("\nPruebo el heapsort devuelta (De menor a mayor)\n");
  for(int i=0;i<12;i++){
    enteros_en_heapsort[i]=&enteros[i];
  }
  heapsort((void**)enteros_en_heapsort,12,comparador_enteros,MAXIMAL);
  assert_vectores(enteros_en_heapsort,enteros_ordenados_men_a_may,12,"Se obtuvo el vector esperado",pruebas_pasadas);

  verificar_si_paso_las_pruebas(pruebas_pasadas,pruebas);
}

/* Se evalua el comportamiento del heap cuando se le insertan varios numeros. Se prueba insertandole
 * 2 numeros que no van a estar guardados.
 */
void pruebas_de_volumen(){
  int pruebas_pasadas=0,pruebas=5;
  int numeros[MAXIMO];
  int numero_unico_maximo=1000;
  int numero_unico_minimo=-1000;
  cargar_enteros(numeros,MAXIMO);
  heap_t* heap=heap_crear(NULL,comparador_enteros,200,MAXIMAL);
  insertar_enteros(heap,numeros,MAXIMO);
  assert(heap_cantidad(heap)==MAXIMO,"Hay 500 elementos en el heap",pruebas_pasadas);
  assert(heap_insertar(heap,&numero_unico_maximo)==EXITO,"Se inserto el numero unico",pruebas_pasadas);
  assert(*(int*)heap_ver_primer_elemento(heap)==1000,"El primer elemento es el numero unico",pruebas_pasadas);
  assert(heap_insertar(heap,&numero_unico_minimo)==EXITO,"Se inserto otro numero unico",pruebas_pasadas);
  borrar_varias_veces(heap,501);
  assert(*(int*)heap_ver_primer_elemento(heap)==-1000,"El primer elemento es el otro numero unico",pruebas_pasadas);

  heap_destruir(heap);

  verificar_si_paso_las_pruebas(pruebas_pasadas,pruebas);
}


/* Evalua las funciones del heap con caracteres
 */
void pruebas_con_caracteres(){
  int pruebas_pasadas=0,pruebas=7;
  char* abecedario="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  char* letras_desordenadas="XYHIJKABCDSTUVLEFGMNOPQRWZ";

  printf("\nCreo un heap maximal\n");
  heap_t* heap=heap_crear(NULL,comparador_caracteres,30,MAXIMAL);

  assert(heap_cantidad(heap)==0,"El heap esta vacio",pruebas_pasadas);
  insertar_caracteres(heap,letras_desordenadas,26);
  assert(heap_cantidad(heap)==26,"Hay 26 elementos en el heap",pruebas_pasadas);
  assert(*(char*)heap_ver_primer_elemento(heap)=='Z',"La primer letra del heap es la Z",pruebas_pasadas);
  assert(heap_eliminar_primero(heap)==EXITO,"Elimino la Z",pruebas_pasadas);
  assert(*(char*)heap_ver_primer_elemento(heap)=='Y',"La siguiente letra es la Y",pruebas_pasadas);
  printf("Borro varias veces\n");
  borrar_varias_veces(heap,23);
  assert(*(char*)heap_ver_primer_elemento(heap)=='B',"La primer letra es la B",pruebas_pasadas);

  heap_destruir(heap);

  printf("\nPruebo el heapsort (De menor a mayor)\n");
  char* letras_en_heapsort[26];
  for(int i=0;i<26;i++){
    letras_en_heapsort[i]=&letras_desordenadas[i];
  }
  heapsort((void**)letras_en_heapsort,26,comparador_caracteres,MAXIMAL);
  pruebas_pasadas++;
  int j=0;
  bool ordenado=true;
  while(j<26 && ordenado){
    if(abecedario[j]!=*(letras_en_heapsort[j])){
      ordenado=false;
      pruebas_pasadas--;
    }
    j++;
  }
  printf("------>Esperaba:");
	for(int j=0;j<26;j++){
		printf("%c-",abecedario[j]);
	}
	printf("\n------>Se obtuvo:");
	for(int j=0;j<26;j++){
		printf("%c-",*(letras_en_heapsort[j]));
	}

  verificar_si_paso_las_pruebas(pruebas_pasadas,pruebas);
}

/* Evalua el comportamiento de las primitivas del heap cuando este no esta creado.
 */
void pruebas_nulas(){
  int pruebas_pasadas=0,pruebas=6;
  char* prueba="ALGORITMOS 2";

  heap_t* heap=NULL;
  assert(heap_insertar(heap,prueba)==ERROR,"No puede insertar en un heap nulo",pruebas_pasadas);
  assert(heap_cantidad(heap)==0,"El heap estaria vacio",pruebas_pasadas);
  assert(heap_eliminar_primero(heap)==ERROR,"No puede eliminar el primero con heap nulo",pruebas_pasadas);
  assert(heap_ver_primer_elemento(heap)==NULL,"El primer elemento es NULL",pruebas_pasadas);

  heap=heap_crear(NULL,NULL,10,MAXIMAL);
  assert(heap==NULL,"El heap no puede tener como comparador NULL",pruebas_pasadas);
  heap=heap_crear(NULL,comparador_enteros,10,2);
  assert(heap==NULL,"El heap solo puede ser maximal o minimal",pruebas_pasadas);

  verificar_si_paso_las_pruebas(pruebas_pasadas,pruebas);
}

/* Realiza las pruebas
 */
int main(){
  printf("----------EJEMPLO 1 - HEAP----------\n");
  printf("Ejemplos con casos basicos\n");
  printf("\n-------CON ENTEROS-------\n");
  pruebas_con_enteros();

  printf("\n-------DE VOLUMEN-------\n");
  pruebas_de_volumen();

  printf("\n-------CON CARACTERES-------\n");
  pruebas_con_caracteres();

  printf("\n-------CASOS NULOS--------\n");
  pruebas_nulas();

  printf("-------------------------------------\n");
  return 0;
}
