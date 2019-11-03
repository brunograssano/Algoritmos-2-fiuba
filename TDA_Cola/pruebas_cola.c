#include <stdio.h>
#include <stdlib.h>
#include "cola.h"
#define EXITO 0
#define ERROR -1
#define NO_EXISTE 0
#define MAX 3
const int PRUEBA=1,PRUEBAS_ESPERADAS=5,PRUEBAS_PASADAS=4,CANTIDAD_ESPERADA=1,PRIMER_ENTERO=10,MAXIMO=400;
const int SIN_ELEMENTOS=0;
const char PRIMER_CARACTER='A';
const double PI=3.14159,EULER=2.71828,GAS_IDEAL=0.082;

/* Muestra el resultado general de la prueba
 */
void mostrar_resultado(bool estado,int* pruebas_pasadas){
	printf("\n------>Resultado de la prueba:%s \n",estado?" PASSED :)":" FAILED :(");
	if(estado){
		(*pruebas_pasadas)++;
	}
}

/* Comprueba si paso las pruebas internas de cada prueba.
 * Para ello, recibe una cantidad que indica las que paso, y otro que indica las esperadas.
 * Imprime por pantalla el resultado.
 */
void verificar_si_paso_las_pruebas(int contador_pruebas_pasadas,int pruebas_a_pasar,bool* resultado){
	if(contador_pruebas_pasadas==pruebas_a_pasar){
		printf("Paso las %i pruebas internas.\n",pruebas_a_pasar);
		(*resultado)=true;
	}
	else{
		printf("No paso todas las pruebas internas, paso solo %i de %i\n",contador_pruebas_pasadas,pruebas_a_pasar);
	}
}

/* Encola en la cola caracteres. Necesita del tope positivo.
 */
void encolar_caracteres(cola_t* cola,char* elementos,int tope){
	for(int i=0;i<tope;i++){
		cola_encolar(cola,&elementos[i]);
	}
}

/* Encola en la cola flotantes(Recibe douuble). Necesita del tope positivo.
 */
void encolar_flotantes(cola_t* cola,double elementos[MAX],int tope){
	for(int i=0;i<tope;i++){
		cola_encolar(cola,&elementos[i]);
	}
}

/* Encola en la cola enteros. Necesita del tope positivo.
 */
void encolar_enteros(cola_t* cola,int elementos[MAXIMO],int tope){
	for(int i=0;i<tope;i++){
		cola_encolar(cola,&elementos[i]);
	}
}

/* Desencola de la cola varios elementos. Necesita del tope positivo.
 */
void desencolar_varias_veces(cola_t* cola,int tope){
	for(int i=0;i<tope;i++){
		cola_desencolar(cola);
	}
}

/* Carga un vector con numeros enteros generados de forma semirandom. La funcion necesita un tope que sea positivo.
 */
void cargar_enteros(int enteros[MAXIMO],int tope){
	for(int i=0;i<tope;i++){
		enteros[i]=rand()%MAXIMO;
	}
}

/* Verifica si la cola tiene la cantidad esperada de elementos guardados.
 */
void ver_si_cumple_con_cantidad_esperada(cola_t* cola,int* contador_pruebas_pasadas,int esperados){
	printf("Espero %i elementos guardados.\n",esperados);
	if(cola_cantidad(cola)==esperados){
		(*contador_pruebas_pasadas)++;
		printf("-->Hay %i elementos guardados, por lo tanto paso la prueba.\n",cola_cantidad(cola));
	}
	else{
		printf("-->Hay %i elementos guardados,no son los esperados.\n",cola_cantidad(cola));
	}
}



/* Se manda una cola que no fue creada a cada accion que puede hacer. En cada una,
 * se verifica que devuelvan el estado esperado.
 */
bool intentar_realizar_acciones_con_cola_nula(){
	printf("\n-----------PRUEBA DE COLA SIN CREAR-----------\n");
	int estado,elemento_de_prueba=PRUEBA,contador_pruebas_pasadas=0;
	void* estado_null;
	bool resultado=false;
	cola_t* cola=NULL;

	estado=cola_encolar(cola,&elemento_de_prueba);
	if(estado==ERROR){
		contador_pruebas_pasadas++;
		printf("-->Paso prueba de intentar encolar\n");
	}

	estado=cola_desencolar(cola);
	if(estado==ERROR){
		contador_pruebas_pasadas++;
		printf("-->Paso prueba de intentar desencolar\n");
	}

	if(cola_vacia(cola)){
		contador_pruebas_pasadas++;
		printf("-->La cola esta vacia\n");
	}

	ver_si_cumple_con_cantidad_esperada(cola,&contador_pruebas_pasadas,NO_EXISTE);

	estado_null=cola_primero(cola);
	if(estado_null==NULL){
		contador_pruebas_pasadas++;
		printf("-->Paso prueba de intentar ver el primer elemento\n");
	}

	verificar_si_paso_las_pruebas(contador_pruebas_pasadas,PRUEBAS_ESPERADAS,&resultado);

	return resultado;
}

/* Se encola un elemento NULL, y se ve si la cola realiza las acciones. 
 */
bool encolar_elemento_nulo_y_realizar_acciones_con_el(){
	printf("\n-----------PRUEBA DE ENCOLAR NULL-----------\n");
	int estado,contador_pruebas_pasadas=0;
	void* elemento_nulo=NULL;
	bool resultado=false;
	cola_t* cola=cola_crear();

	estado=cola_encolar(cola,&elemento_nulo);
	if(estado==EXITO){
		contador_pruebas_pasadas++;
		printf("-->Paso prueba de encolar NULL\n");
	}

	ver_si_cumple_con_cantidad_esperada(cola,&contador_pruebas_pasadas,CANTIDAD_ESPERADA);

	if(!cola_vacia(cola)){
		contador_pruebas_pasadas++;
		printf("-->Paso prueba de ver si estaba vacia la cola\n");
	}

	void** estado_null= cola_primero(cola);
	if((*estado_null)==NULL){
		contador_pruebas_pasadas++;
		printf("-->Paso prueba ver el primer elemento\n");
	}

	estado=cola_desencolar(cola);
	if(estado==EXITO){
		contador_pruebas_pasadas++;
		printf("-->Paso prueba de desencolar NULL\n");
	}

	verificar_si_paso_las_pruebas(contador_pruebas_pasadas,PRUEBAS_ESPERADAS,&resultado);

	cola_destruir(cola);
	return resultado;
}

/* Desencolo diferentes tipos de datos. En la prueba se ve que guarde correctamente enteros, flotantes (double), y caracteres.
 * Luego los desencolo y verifico que salgan en el orden esperado.
 */
bool encolo_diferentes_tipos_de_elementos_y_los_voy_desencolando(){
	printf("\n-----------PRUEBA DE ENCOLAR DIFERENTES ELEMENTOS-----------\n");
	int contador_pruebas_pasadas=0;
	bool resultado=false;

	int enteros[MAX]={10,20,30};
	double constantes[MAX]={PI,EULER,GAS_IDEAL};
	char letras[MAX]="ASD";

	cola_t* cola=cola_crear();

	encolar_enteros(cola,enteros,MAX);
	encolar_flotantes(cola,constantes,MAX);
	encolar_caracteres(cola,letras,MAX);

	ver_si_cumple_con_cantidad_esperada(cola,&contador_pruebas_pasadas,3*MAX);

	if(!cola_vacia(cola)){
		contador_pruebas_pasadas++;
		printf("-->La cola no esta vacia, paso la prueba\n");
	}

	int entero_desencolado=*(int*) cola_primero(cola);
	if(entero_desencolado==PRIMER_ENTERO){
		contador_pruebas_pasadas++;
		printf("-->Devolvio con exito el primer elemento encolado (%i)\n",entero_desencolado);
	}

	desencolar_varias_veces(cola,MAX);
	printf("Se desencolaron los enteros, espero un numero irracional ahora.\n");

	double constante_desencolada=*(double*) cola_primero(cola);
	if(constante_desencolada==PI){
		contador_pruebas_pasadas++;
		printf("-->Paso prueba de desencolar un numero irracional (%f)\n",constante_desencolada);
	}

	desencolar_varias_veces(cola,MAX);
	printf("Se desencolaron las constantes, espero un caracter ahora.\n");

	char caracter_desencolado=*(char*) cola_primero(cola);
	if(caracter_desencolado==PRIMER_CARACTER){
		contador_pruebas_pasadas++;
		printf("-->Devolvio el caracter esperado (%c)\n",caracter_desencolado);
	}

	verificar_si_paso_las_pruebas(contador_pruebas_pasadas,PRUEBAS_ESPERADAS,&resultado);

	cola_destruir(cola);
	return resultado;
}

/* Se prueba que se guarden correctamente 400 elementos. Estos elementos son numeros generados de forma random.
 * Una vez encolados, se desencola hasta la mitad y se verifica que lo haya hecho hecho de forma correcta. Luego,
 * se vacia la cola y se prueba que quede vacia.
 */
bool encolo_en_cantidad_400_elementos(){
	printf("\n-----------PRUEBA DE ENCOLAR EN CANTIDAD-----------\n");
	int contador_pruebas_pasadas=0;
	int enteros[MAXIMO];
	bool resultado=false;
	cargar_enteros(enteros,MAXIMO);

	cola_t* cola=cola_crear();

	encolar_enteros(cola,enteros,MAXIMO);
	
	ver_si_cumple_con_cantidad_esperada(cola,&contador_pruebas_pasadas,MAXIMO);

	if(!cola_vacia(cola)){
		contador_pruebas_pasadas++;
		printf("-->La cola no esta vacia, paso la prueba\n");
	}

	desencolar_varias_veces(cola,MAXIMO/2);
	printf("Se desencolo hasta la mitad.\n");

	ver_si_cumple_con_cantidad_esperada(cola,&contador_pruebas_pasadas,MAXIMO/2);

	desencolar_varias_veces(cola,MAXIMO/2);
	printf("Se desencolo lo que quedaba.\n");

	ver_si_cumple_con_cantidad_esperada(cola,&contador_pruebas_pasadas,SIN_ELEMENTOS);

	if(cola_vacia(cola)){
		contador_pruebas_pasadas++;
		printf("-->La cola esta vacia\n");
	}

	verificar_si_paso_las_pruebas(contador_pruebas_pasadas,PRUEBAS_ESPERADAS,&resultado);

	cola_destruir(cola);
	return resultado;
}

/* Encola 3 elementos y luego desencola 4. De esta forma, se verifica que devuelva NULL y error para cada caso.
 */
bool intentar_desencolar_mas_elementos_de_los_que_hay(){
	printf("\n-----------PRUEBA DE DESENCOLAR MAS DE LO GUARDADO-----------\n");
	int estado,contador_pruebas_pasadas=0;
	int enteros[MAX];
	cargar_enteros(enteros,MAX);
	bool resultado=false;
	
	cola_t* cola=cola_crear();

	encolar_enteros(cola,enteros,MAX);
	
	ver_si_cumple_con_cantidad_esperada(cola,&contador_pruebas_pasadas,MAX);

	desencolar_varias_veces(cola,MAX);
	printf("Se desencolo todo\n");

	if(cola_vacia(cola)){
		contador_pruebas_pasadas++;
		printf("-->Esta vacia la cola\n");
	}

	estado=cola_desencolar(cola);

	if(estado==ERROR){
		contador_pruebas_pasadas++;
		printf("-->No pudo desencolar con la cola vacia\n");
	}

	if(cola_primero(cola)==NULL){
		contador_pruebas_pasadas++;
		printf("-->Devuelve NULL si intento acceder al primero.\n");
	}

	verificar_si_paso_las_pruebas(contador_pruebas_pasadas,PRUEBAS_PASADAS,&resultado);

	cola_destruir(cola);
	return resultado;
}

/* Realiza las pruebas
 */
void realizar_pruebas(){
	int pruebas_pasadas=0;
	bool estado;

	printf("\n////--------------------PRUEBAS DE CASOS NULOS--------------------////\n");

	estado=intentar_realizar_acciones_con_cola_nula();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=encolar_elemento_nulo_y_realizar_acciones_con_el();
	mostrar_resultado(estado,&pruebas_pasadas);

	printf("\n////---------------------PRUEBAS DE ENCOLAR---------------------////\n");

	estado=encolo_diferentes_tipos_de_elementos_y_los_voy_desencolando();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=encolo_en_cantidad_400_elementos();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=intentar_desencolar_mas_elementos_de_los_que_hay();
	mostrar_resultado(estado,&pruebas_pasadas);

	printf("\n////-------------------------------------------------------------////\n");

	printf("Paso %i pruebas de 5\n",pruebas_pasadas);
}

/* Realiza las pruebas
 */
int main(){
	printf("----------------PRUEBAS DE LA COLA----------------\n");
	realizar_pruebas();

	return 0;
}