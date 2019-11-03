#include "pila.h"
#include <stdio.h>

int main(){
  pila_t* pila = pila_crear();

  char elemento1 = '!';
  pila_apilar(pila, &elemento1);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));
  char elemento2 = '2';
  pila_apilar(pila, &elemento2);
  char elemento3 = 'o';
  pila_apilar(pila, &elemento3);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));
  char elemento4 = 'g';
  pila_apilar(pila, &elemento4);
  char elemento5 = 'l';
  pila_apilar(pila, &elemento5);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));
  char elemento6 = 'A';
  pila_apilar(pila, &elemento6);


  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));
  printf("%c\n", *(char*)pila_tope(pila));
  pila_desapilar(pila);
  printf("Tamanio pila: %i\n", pila_cantidad(pila));

  pila_destruir(pila);
  return 0;
}