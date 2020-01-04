#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "juego_de_tronos.h"

#define EXITO 0
const char INICIO_SIMULACION='S',AGREGAR_CASA='A',LISTAR_CASAS='L',MOSTRAR_CASAS_EXTINTAS='E',FINALIZAR_PROGRAMA='Q', MOSTRAR_MIEMBROS='M';

/* Verifica que el caracter ingresado sea uno de los validos (S-A-L-E-M-Q), en caso de que no lo sea, devolvera false.
 */
bool es_caracter_valido(char caracter){
  return caracter==MOSTRAR_MIEMBROS || caracter==INICIO_SIMULACION || caracter==AGREGAR_CASA || caracter==LISTAR_CASAS || caracter==MOSTRAR_CASAS_EXTINTAS || caracter==FINALIZAR_PROGRAMA;
}

/* Mostrara por pantalla las diferentes opciones que tiene el programa.
 */
void mostrar_opciones(){
  printf("\n\n///---------------------ACCIONES POSIBLES-------------------------///\n");
  printf("Ingrese el caracter de la accion que quiere realizar\n");
  printf("Las acciones son las siguientes:\n");
  printf("---->Correr la simulacion (S)\n");
  printf("---->Agregar una casa al arbol (A)\n");
  printf("---->Listar las casas por cantidad de integrantes de forma descendente (L)\n");
  printf("---->Mostrar las casas extintas en el orden de desaparicion (E)\n");
  printf("---->Mostrar miembros de una casa (M)\n");
  printf("---->Finalizar el programa (Q)\n");
  printf("\n-------->");
}

/* Pregunta al usuario La accion que deasea realizar. El caracter ingresado sera uno de los validos, ya que se valida.
 */
void preguntar_accion_a_realizar(char* accion){
  do{
    mostrar_opciones();
    scanf(" %c",accion);
    if(!es_caracter_valido(*accion)){
      printf("**Ingrese uno de los caracteres validos. (S-A-L-E-M-Q)\n");
    }
  }while(!es_caracter_valido(*accion));
}

/* Realiza la accion indicada por el usuario. El caracter representando la accion ya fue validado.
 */
void realizar_accion(juego_t* juego,char accion){
  system("clear");
  printf("\n------------RESULTADO------------\n");
  if(accion==INICIO_SIMULACION){
    iniciar_simulacion(juego);
  }
  else if(accion==AGREGAR_CASA){
    agregar_casa_al_arbol(juego);
  }
  else if(accion==LISTAR_CASAS){
    listar_casas_en_orden(*juego);
  }
  else if(accion==MOSTRAR_CASAS_EXTINTAS){
    mostrar_casas_extintas(*juego);
  }
  else if(accion==MOSTRAR_MIEMBROS){
    mostrar_miembros_casa(*juego);
  }
  else{
    printf("\nTerminando el juego...\n");
  }
}

/* Inicializa el programa creando la estructura para la simulacion y preguntandole al usuario la accion
 * a realizar.
 */
int main() {
  char accion=0;
  juego_t juego;
  int estado=inicializar_juego(&juego);
  while(accion!=FINALIZAR_PROGRAMA && estado==EXITO){
    preguntar_accion_a_realizar(&accion);
    realizar_accion(&juego,accion);
  }
  destruir_juego(juego);
  return 0;
}
