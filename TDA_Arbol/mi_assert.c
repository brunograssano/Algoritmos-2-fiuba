#include "mi_assert.h"
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_RESET   "\x1b[0m"

/* Muestra el resultado general de la prueba
 */
void mostrar_resultado(bool estado,int* pruebas_pasadas){
	printf("\n------>Resultado de la prueba:%s \n",estado?COLOR_GREEN" PASSED :)"COLOR_RESET:COLOR_RED" FAILED :("COLOR_RESET);
	if(estado){
		(*pruebas_pasadas)++;
	}
}

/* Comprueba si se cumple la expresion booleana recibida, muestra el mensaje por pantalla.
 * En caso de error mostrara la linea y el archivo. Si paso la prueba aumenta el contador.
 */
void mi_assert(bool resultado,char* mensaje,int *contador,char* archivo,int linea){
	if(resultado){
		printf("-->%s:"COLOR_GREEN" OK\n"COLOR_RESET,mensaje );
		(*contador)++;
	}
	else{
		printf("-->%s:"COLOR_RED" ERROR\n" COLOR_RESET,mensaje);
		printf("----> Archivo: %s , Linea: %i\n",archivo,linea);
	}
}

/* Comprueba que dos vectores sean iguales, en caso de serlo, llama a mi_assert y esta funcion dira el resultado obtenido.
 */
void assert_vectores_iguales(int* obtenido[MAX_VECTOR],int esperado[MAX_VECTOR],int tope,char* mensaje,int *contador,char* archivo,int linea){
	bool iguales=true;
	int i=0;
	while(iguales && i<tope){
		if(*(obtenido[i])!=esperado[i]){
			iguales=false;
		}
		i++;
	}
	mi_assert(iguales,mensaje,contador,archivo,linea);
	
	printf("------>Esperaba:");
	for(int j=0;j<tope;j++){
		printf("%i-",esperado[j]);
	}
	printf("\n------>Se obtuvo:");
	for(int j=0;j<tope;j++){
		printf("%i-",*(obtenido[j]));
	}
	printf("\n");
	
}

/* Comprueba si paso las pruebas internas de cada prueba.
 * Para ello, recibe una cantidad que indica las que paso, y otro que indica las esperadas.
 * Imprime por pantalla el resultado.
 */
void verificar_si_paso_las_pruebas(bool* resultado,int contador_pruebas_pasadas,int pruebas_a_pasar){
	if(contador_pruebas_pasadas==pruebas_a_pasar){
		printf("\nPaso las %i pruebas internas.\n",pruebas_a_pasar);
		(*resultado)=true;
	}
	else{
		printf("\nNo paso todas las pruebas internas, paso solo %i de %i\n",contador_pruebas_pasadas,pruebas_a_pasar);
	}
}