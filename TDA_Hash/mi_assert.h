#ifndef __MI_ASSERT_H__
#define __MI_ASSERT_H__
#include <stdio.h>
#include <stdbool.h>
#define MAX_VECTOR 300
#define assert(resultado,mensaje,contador) mi_assert(resultado,mensaje,&contador,__FILE__, __LINE__)
#define assert_vectores(obtenido,esperado,tope,mensaje,contador) assert_vectores_iguales(obtenido,esperado,tope,mensaje,&contador,__FILE__, __LINE__)

/* Muestra el resultado general de la prueba
 */
void mostrar_resultado(bool estado,int* pruebas_pasadas);

/* Comprueba si se cumple la expresion booleana recibida, muestra el mensaje por pantalla.
 */
void mi_assert(bool resultado,char* mensaje,int *contador,char* file,int line);

/* Comprueba que dos vectores de enteros sean iguales, en caso de serlo, llama a mi_assert y esta funcion dira el resultado obtenido.
 */
void assert_vectores_iguales(int* obtenido[MAX_VECTOR],int esperado[MAX_VECTOR],int tope,char* mensaje,int *contador,char* file,int line);

/* Comprueba si paso las pruebas internas de cada prueba.
 * Para ello, recibe una cantidad que indica las que paso, y otro que indica las esperadas.
 * Imprime por pantalla el resultado.
 */
bool verificar_si_paso_las_pruebas(int contador_pruebas_pasadas,int pruebas_a_pasar);


#endif /* __MI_ASSERT_H__ */
