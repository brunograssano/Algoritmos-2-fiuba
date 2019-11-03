#include "pila.h"
#include <stdio.h>
#include <stdlib.h>
#define EXITO 0
#define ERROR -1
#define NO_EXISTE 0
const int FALLOS_ESPERADOS=5,CANT_ELEMENTOS=4,MAX_ELEMENTOS=150,TAMANIO_ESPERADO=5,CANT_ELEMENTOS_ESPERADOS=0;
const int TAMANIO_CARACTERES_ESPERADO=10,CANTIDAD_CARACTERES_ESPERADA=5,MAX_DESAPILAR_CARACTERES=5,MAX_MENSAJE=3,MAX_APILAR=15;
const int TAMANIO_ESTABLE=10,ERRORES_ESPERADOS=2;

/* Llenara un vector de enteros con un entero que surge de la iteracion.
 */
void cargar_elementos_con_valores(int elementos[],int tope){
	for (int i = 0; i < tope; i++) {
		elementos[i]=i;
	}
}

/* Muestra el estado actual de la pila.
 */
void mostrar_tamanio_y_tope(pila_t* pila){
	printf("\n\nTamanio de %i elementos con una cantidad de %i guardados\n",pila->tamanio,pila_cantidad(pila) );
}

/* Evaluo si todas las acciones devuelven el mensaje de error, ya sea -1 o NULL. Luego, comparo esa cantidad con la esperada,
 * y ahi se decide el estado de la prueba.
 */
bool intentar_acceder_con_pila_nula(){
	bool estado_prueba=false;
	int estado,contador_fallos=0,elemento_de_prueba=0;
	void* contador_null;
	pila_t* pila=NULL;

	estado=pila_apilar(pila,&elemento_de_prueba);
	if(estado==ERROR){
		printf("No apilo. Paso prueba interna 1\n");
		contador_fallos++;
	}
	
	estado=pila_desapilar(pila);
	if(estado==ERROR){
		printf("No desapilo. Paso prueba interna 2\n");
		contador_fallos++;
	}
	
	if(pila_vacia(pila)){
		printf("La pila esta vacia. Paso prueba interna 3\n");
		contador_fallos++;
	}

	estado=pila_cantidad(pila);
	if(estado==NO_EXISTE){
		printf("La cantidad es 0. Paso prueba interna 4\n");
		contador_fallos++;
	}

	contador_null=pila_tope(pila);
	if(contador_null==NULL){
		printf("No entro en el tope. Paso prueba interna 5\n");
		contador_fallos++;
	}

	if(contador_fallos==FALLOS_ESPERADOS){
		printf("No realizo ninguna accion.\n");
		estado_prueba=true;
	}

	return estado_prueba;
}

/* Pruebo si devuelven el mensaje de error cuando el vector dinamico de elementos no existe pero si la pila.
 * Para conseguir esto, libero su memoria y lo apunto a NULL.
 * Si el contador de fallos coincide con el esperado pasa la prueba.
 */
bool intentar_acceder_con_pila_creada_pero_elementos_en_null(){
	bool estado_prueba=false;
	int estado,contador_fallos=0,elemento_de_prueba=0;
	void* contador_null;

	pila_t* pila=pila_crear();
	free(pila->elementos);
	pila->elementos=NULL;

	estado=pila_apilar(pila,&elemento_de_prueba);
	if(estado==ERROR)contador_fallos++;
	
	estado=pila_desapilar(pila);
	if(estado==ERROR)contador_fallos++;
	
	if(pila_vacia(pila))contador_fallos++;

	estado=pila_cantidad(pila);
	if(estado==NO_EXISTE)contador_fallos++;

	contador_null=pila_tope(pila);
	if(contador_null==NULL)contador_fallos++;

	if(contador_fallos==FALLOS_ESPERADOS){
		printf("\nNo realizo ninguna accion de las posibles para una pila. Paso las pruebas internas\n");
		estado_prueba=true;
	}

	pila_destruir(pila);
	return estado_prueba;
}

bool apilo_elemento_nulo_y_veo_su_tope(){
	bool estado_prueba=false;

	pila_t* pila = pila_crear();
	void* elemento_nulo=NULL;
	void** desapilado_nulo;
	
	int estado_apilar=pila_apilar(pila, &elemento_nulo);
	if(estado_apilar==EXITO){
		printf("Apilo NULL con exito\n");
	}

	desapilado_nulo=pila_tope(pila);
	mostrar_tamanio_y_tope(pila);

	if((*desapilado_nulo)==NULL){
		estado_prueba=true;
	}
	
	pila_destruir(pila);
	return estado_prueba;
}

/* Situacion de uso tranquilo de la pila, si el tamanio y cantidad coinciden paso la prueba 
 */
bool apila_tres_veces_cinco_caracteres_muestra_mesaje_y_tamanio_y_desapila_los_ultimos_cinco(){
	pila_t* pila = pila_crear();
	bool estado_prueba=false;

	char elementos[5]="2ogla";
	printf("\nMensaje apilado 3 veces: %s\n",elementos);
	for (int i = 0; i < MAX_MENSAJE; i++) {
		pila_apilar(pila, &elementos[0]);
		pila_apilar(pila, &elementos[1]);
		pila_apilar(pila, &elementos[2]);
		pila_apilar(pila, &elementos[3]);
		pila_apilar(pila, &elementos[4]);
	}

	printf("Mensaje desapilado 1 vez:");
	for (int i = 0; i < MAX_DESAPILAR_CARACTERES; i++) {
		printf("%c", *(char*)pila_tope(pila));
		pila_desapilar(pila);
	}
	mostrar_tamanio_y_tope(pila);
	
	for (int i = 0; i < MAX_DESAPILAR_CARACTERES; i++) {
		pila_desapilar(pila);
	}
	mostrar_tamanio_y_tope(pila);

	if(pila_cantidad(pila)==CANTIDAD_CARACTERES_ESPERADA && pila->tamanio==TAMANIO_CARACTERES_ESPERADO){
		estado_prueba=true;
	}
	
	pila_destruir(pila);
	return estado_prueba;
}

/* El objetivo de la prueba es ver si apilando  desapilando varias veces, cambiando elementos, manteniendo su tamanio, el cual llega hasta el limite.
 * Si al final esta en el tamanio y tope esperado paso la prueba.
 */
bool apilar_y_desapilar_varias_veces_manteniendo_tamanio(){
	bool estado_prueba=false;
	pila_t* pila = pila_crear();

	int elementos[MAX_APILAR];
	cargar_elementos_con_valores(elementos,MAX_APILAR);

	printf("Elementos apilados inicialmente\n");
	for (int i = 0; i < 10; i++) {
		pila_apilar(pila, &elementos[i]);
		printf("%i-", *(int*)pila_tope(pila));
	}
	mostrar_tamanio_y_tope(pila);

	printf("Elementos desapilados\n");
	for (int i = 0; i < 5; i++) {
		printf("%i-", *(int*)pila_tope(pila));
		pila_desapilar(pila);
	}
	mostrar_tamanio_y_tope(pila);

	printf("Elementos apilados en remplazo a los otros\n");
	for (int i = 10; i < 15; i++) {
		pila_apilar(pila,&elementos[i]);
		printf("%i-", *(int*)pila_tope(pila));
	}
	mostrar_tamanio_y_tope(pila);

	if(pila_cantidad(pila)==TAMANIO_ESTABLE && pila->tamanio==TAMANIO_ESTABLE){
		estado_prueba=true;
	}
	
	pila_destruir(pila);
	return estado_prueba;
}

/* Se prueba el correcto uso de la memoria, para eso, se apilan 150 elementos que despues son desapilados.
 * Si el tamanio final es el esperado, paso la prueba
 */
bool cargar_150_elementos_y_desapilarlos_mostrando_tamanio(){
	bool estado_prueba=false;
	int elementos[MAX_ELEMENTOS];
	pila_t* pila = pila_crear();

	cargar_elementos_con_valores(elementos,MAX_ELEMENTOS);

	for (int i = 0; i < MAX_ELEMENTOS; i++) {
		pila_apilar(pila, &elementos[i]);
	}
	mostrar_tamanio_y_tope(pila);

	printf("ELEMENTOS DESAPILADOS\n");
	for (int i = 0; i < MAX_ELEMENTOS; i++) {
		printf("%i-", *(int*)pila_tope(pila));
		pila_desapilar(pila);
	}

	mostrar_tamanio_y_tope(pila);

	if(pila_cantidad(pila)==CANT_ELEMENTOS_ESPERADOS && pila->tamanio==TAMANIO_ESPERADO){
		estado_prueba=true;
	}

	pila_destruir(pila);

	return estado_prueba;
}

/* Se prueba que no se puedan desapilar mas elementos que los que hay.
 * Si el estado recibido es -1, pasa la prueba.
 */
bool intentar_ver_y_sacar_mas_elementos_de_los_que_hay(){
	bool estado_prueba=false;
	int estado,contador_pruebas=0;
	void* elemento_prueba;
	int elementos[4];
	cargar_elementos_con_valores(elementos,4);
	
	pila_t* pila = pila_crear();

	for (int i = 0; i < 4; i++) {
		pila_apilar(pila, &elementos[i]);
	}
	mostrar_tamanio_y_tope(pila);

	for (int i = 0; i < 5; i++) {
		
		if(i==4){
			elemento_prueba=pila_tope(pila);
			if(elemento_prueba==NULL){
				printf("No pudo ver con el tope en 0. Paso prueba interna 1\n");
				contador_pruebas++;
			}
		}

		estado=pila_desapilar(pila);
		if(estado==ERROR){
			printf("No se pudo sacar el elemento. Paso prueba interna 2.\n");
			contador_pruebas++;
		}

	}
	mostrar_tamanio_y_tope(pila);

	if(contador_pruebas==ERRORES_ESPERADOS){
		estado_prueba=true;
	}

	pila_destruir(pila);
	return estado_prueba;
}


/* Muestra si la prueba fue exitosa o no, para eso recibe tambien el nombre y un contador para tener registro de cuantas va pasando.
 */
void mostrar_resultado(bool estado,char* nombre_prueba,int* pruebas_pasadas){
	printf("\n---------->TEST %s:",nombre_prueba);
	if(estado){
		printf("PASSED :)\n");
		(*pruebas_pasadas)++;
	}
	else{
		printf("FAILED ):\n");
	}
	printf("\n            ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
}

/* Realiza todas las pruebas cargadas, mostrando al final cuantas pasaron del total.
 */
void realizar_pruebas(){
	
	int pruebas_pasadas=0;
	bool estado;

	printf("\n////--------------------PRUEBAS DE CASOS NULOS--------------------////\n");

	estado=intentar_acceder_con_pila_nula();
	mostrar_resultado(estado,"PILA NULA",&pruebas_pasadas);

	estado=intentar_acceder_con_pila_creada_pero_elementos_en_null();
	mostrar_resultado(estado,"SIN ELEMENTOS CREADOS",&pruebas_pasadas);

	estado=apilo_elemento_nulo_y_veo_su_tope();
	mostrar_resultado(estado,"APILAR ELEMENTO NULO",&pruebas_pasadas);

	printf("\n////------------------PRUEBAS DE USO DE MEMORIA------------------////\n");

	estado=apila_tres_veces_cinco_caracteres_muestra_mesaje_y_tamanio_y_desapila_los_ultimos_cinco();
	mostrar_resultado(estado,"USO NORMAL",&pruebas_pasadas);

	estado=apilar_y_desapilar_varias_veces_manteniendo_tamanio();
	mostrar_resultado(estado,"MANTENER TAMANIO",&pruebas_pasadas);

	estado=cargar_150_elementos_y_desapilarlos_mostrando_tamanio();
	mostrar_resultado(estado,"CARGAR CANTIDAD",&pruebas_pasadas);

	estado=intentar_ver_y_sacar_mas_elementos_de_los_que_hay();
	mostrar_resultado(estado,"SACAR MAS ELEMENTOS QUE EL TOPE",&pruebas_pasadas);

	printf("\n////-------------------------------------------------------------////\n");

	printf("Paso %i pruebas de 7\n",pruebas_pasadas);
}

/* Ejecuta las pruebas
 */
int main(){
	realizar_pruebas();
	return 0;
}