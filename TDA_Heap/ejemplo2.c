#include <stdio.h>
#include <string.h>
#include "heap.h"
#include <stdlib.h>
#include "mi_assert.h"
#define EXITO 0
#define ERROR -1
#define MAXIMAL 1
extern char* strdup(const char*);

typedef struct vehiculo{
  char* modelo;
  int precio;
  int aceleracion;
  char* fabricante;
} vehiculo_t;

/* Compara dos vehiculos por el precio.
 */
int comparar_vehiculos_por_precio(void* elemento1,void* elemento2){
  vehiculo_t* vehiculo1=elemento1;
  vehiculo_t* vehiculo2=elemento2;
  if((vehiculo1->precio)>(vehiculo2->precio)){
    return 1;
  }
  else if((vehiculo1->precio)<(vehiculo2->precio)){
    return -1;
  }
  else{
    return 0;
  }
}

/* Creara un vehiculo en memoria.
 */
vehiculo_t* crear_vehiculo(const char* modelo,int precio,int aceleracion,const char* fabricante){
  vehiculo_t* vehiculo=malloc(sizeof(vehiculo_t));
  if(vehiculo==NULL){
    return NULL;
  }
  vehiculo->modelo=strdup(modelo);
  if(vehiculo->modelo==NULL){
    free(vehiculo);
    return NULL;
  }
  vehiculo->fabricante=strdup(fabricante);
  if(vehiculo->fabricante==NULL){
    free(vehiculo->modelo);
    free(vehiculo);
    return NULL;
  }
  vehiculo->precio=precio;
  vehiculo->aceleracion=aceleracion;
  return vehiculo;
}

/* Libera la memoria tomada por el vehiculo
 */
void destruir_vehiculo(void* elemento){
  vehiculo_t* vehiculo=elemento;
  printf(" Destruyendo el vehiculo %s del fabricante %s\n",vehiculo->modelo,vehiculo->fabricante);
  if(vehiculo!=NULL){
    free(vehiculo->modelo);
    free(vehiculo->fabricante);
  }
  free(vehiculo);
}

/* Realiza el segundo ejemplo
 */
int main(){
  int pruebas_pasadas=0,pruebas=17;

  printf("\n------------EJEMPLO 2----------\n");
  printf("Pruebo el heap con elementos en memoria\n");
  heap_t* vehiculos=heap_crear(destruir_vehiculo,comparar_vehiculos_por_precio,3,MAXIMAL);
  vehiculo_t* vehiculo1=crear_vehiculo("408",1500,12,"Peugot");
  vehiculo_t* vehiculo2=crear_vehiculo("A8",2700,18,"Audi");
  vehiculo_t* vehiculo3=crear_vehiculo("Vento",2000,14,"Volkswagen");
  vehiculo_t* vehiculo4=crear_vehiculo("Fiesta",1400,12,"Ford");
  vehiculo_t* vehiculo5=crear_vehiculo("F12",3500,22,"Ferrari");

  assert(heap_insertar(vehiculos,vehiculo1)==EXITO,"Inserto el vehiculo 1",pruebas_pasadas);
  assert(comparar_vehiculos_por_precio(heap_ver_primer_elemento(vehiculos),vehiculo1)==0,"El vehiculo 1 esta primero",pruebas_pasadas);
  assert(heap_insertar(vehiculos,vehiculo2)==EXITO,"Inserto el vehiculo 2",pruebas_pasadas);
  assert(comparar_vehiculos_por_precio(heap_ver_primer_elemento(vehiculos),vehiculo2)==0,"El vehiculo 2 esta primero",pruebas_pasadas);
  assert(heap_insertar(vehiculos,vehiculo3)==EXITO,"Inserto el vehiculo 3",pruebas_pasadas);
  assert(heap_eliminar_primero(vehiculos)==EXITO,"Se elimino el vehiculo 2",pruebas_pasadas);
  assert(comparar_vehiculos_por_precio(heap_ver_primer_elemento(vehiculos),vehiculo3)==0,"El vehiculo 3 esta primero",pruebas_pasadas);
  assert(heap_insertar(vehiculos,vehiculo4)==EXITO,"Inserto el vehiculo 4",pruebas_pasadas);
  assert(heap_insertar(vehiculos,vehiculo5)==EXITO,"Inserto el vehiculo 5",pruebas_pasadas);
  assert(comparar_vehiculos_por_precio(heap_ver_primer_elemento(vehiculos),vehiculo5)==0,"El vehiculo 5 esta primero",pruebas_pasadas);
  assert(heap_cantidad(vehiculos)==4,"Hay 4 vehiculos",pruebas_pasadas);
  assert(heap_eliminar_primero(vehiculos)==EXITO,"Se elimino un vehiculo",pruebas_pasadas);
  assert(heap_eliminar_primero(vehiculos)==EXITO,"Se elimino un vehiculo",pruebas_pasadas);
  assert(heap_eliminar_primero(vehiculos)==EXITO,"Se elimino un vehiculo",pruebas_pasadas);
  assert(heap_eliminar_primero(vehiculos)==EXITO,"Se elimino un vehiculo",pruebas_pasadas);
  assert(heap_cantidad(vehiculos)==0,"El heap esta vacio",pruebas_pasadas);
  assert(heap_eliminar_primero(vehiculos)==ERROR,"No puede eliminar otro vehiculo",pruebas_pasadas);
  heap_destruir(vehiculos);

  verificar_si_paso_las_pruebas(pruebas_pasadas,pruebas);
  return 0;
}
