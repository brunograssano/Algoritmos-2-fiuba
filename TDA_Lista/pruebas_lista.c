#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mi_assert.h"
#include "lista.h"
#define EXITO 0
#define ERROR -1
#define NO_EXISTE 0
#define MAX 3
const int MAXIMO=800;
const int SIN_ELEMENTOS=0;
const double PI=3.14159,EULER=2.71828,GAS_IDEAL=0.082;


/* Funcion que se utiliza para evaluar el comportamiento del iterador interno, esta un string.
 */
void funcion_de_prueba_mostrar_string(void* frase){
	printf(" El string insertado es: %s\n",(char*)frase);
}

/* Inserta en la lista caracteres. Necesita del tope positivo.
 */
void insertar_caracteres(lista_t* lista,char* elementos,int tope){
	for(int i=0;i<tope;i++){
		lista_insertar(lista,&elementos[i]);
	}
}

/* Inserta en la lista flotantes(Recibe douuble). Necesita del tope positivo.
 */
void insertar_flotantes(lista_t* lista,double elementos[MAX],int tope){
	for(int i=0;i<tope;i++){
		lista_insertar(lista,&elementos[i]);
	}
}

/* Inserta en la lista enteros. Necesita del tope positivo.
 */
void insertar_enteros(lista_t* lista,int elementos[MAXIMO],int tope){
	for(int i=0;i<tope;i++){
		lista_insertar(lista,&elementos[i]);
	}
}

/* Borra de la lista varios elementos. Necesita del tope positivo.
 */
void borrar_varias_veces(lista_t* lista,int tope){
	for(int i=0;i<tope;i++){
		lista_borrar(lista);
	}
}

/* Carga un vector con numeros enteros generados de forma semirandom. La funcion necesita un tope que sea positivo.
 */
void cargar_enteros(int enteros[MAXIMO],int tope){
	for(int i=0;i<tope;i++){
		enteros[i]=rand()%MAXIMO;
	}
}



/* Se manda una lista que no fue creada, y se intenta realizar cada accion que puede hacer. En cada una,
 * se verifica que devuelvan el estado esperado.
 */
bool intentar_realizar_acciones_con_lista_nula(){
	printf("\n-----------PRUEBA DE LISTA SIN CREAR-----------\n");
	int estado,elemento_de_prueba=MAX,contador_pruebas_pasadas=0;
	int pruebas_a_pasar=8;
	void* estado_null;
	bool resultado=false;

	lista_t* lista=NULL;
	estado=lista_insertar(lista,&elemento_de_prueba);
 	assert(estado==ERROR,"Insertar con lista sin crear",contador_pruebas_pasadas);

 	estado=lista_insertar_en_posicion(lista,&elemento_de_prueba,3);
 	assert(estado==ERROR,"Insertar en posicion determinada",contador_pruebas_pasadas);

	estado=lista_borrar(lista);
	assert(estado==ERROR,"Borrar de lista sin crear",contador_pruebas_pasadas);

	estado=lista_borrar_de_posicion(lista,3);
	assert(estado==ERROR,"Borrar de posicion en lista sin crear",contador_pruebas_pasadas);

	assert(lista_vacia(lista),"La lista esta vacia",contador_pruebas_pasadas);

	estado_null=lista_elemento_en_posicion(lista,3);
	assert(estado_null==NULL,"Obtener elemento en posicion",contador_pruebas_pasadas);

	assert(lista_ultimo(lista)==NULL,"Obtener NULL si quiero el ultimo elemento",contador_pruebas_pasadas);

	assert(lista_elementos(lista)==0,"La lista devuelve que no tiene elementos",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	return resultado;
}

/* Se insertar un elemento NULL, y se ve si la lista realiza las acciones. 
 */
bool insertar_elemento_nulo_y_realizar_acciones_con_el(){
	printf("\n-----------PRUEBA DE INSERTAR NULL-----------\n");
	int estado,contador_pruebas_pasadas=0;
	int pruebas_a_pasar=9;
	void* elemento_nulo=NULL;
	bool resultado=false;

	lista_t* lista=lista_crear();

	estado=lista_insertar(lista,&elemento_nulo);
 	assert(estado==EXITO,"Insertar elemento nulo",contador_pruebas_pasadas);

 	estado=lista_insertar_en_posicion(lista,&elemento_nulo,0);
 	assert(estado==EXITO,"Insertar en posicion determinada",contador_pruebas_pasadas);

 	estado=lista_insertar_en_posicion(lista,&elemento_nulo,5);
 	assert(estado==EXITO,"Insertar en posicion determinada",contador_pruebas_pasadas);

 	assert(lista_elementos(lista)==3,"La lista devuelve que tiene 3 elementos",contador_pruebas_pasadas);

	estado=lista_borrar(lista);
	assert(estado==EXITO,"Borrar de la lista un NULL",contador_pruebas_pasadas);

	estado=lista_borrar_de_posicion(lista,0);
	assert(estado==EXITO,"Borrar de posicion otro NULL",contador_pruebas_pasadas);

	assert(lista_elementos(lista)==1,"La lista devuelve que tiene 1 elemento",contador_pruebas_pasadas);

	assert(!lista_vacia(lista),"La lista no esta vacia",contador_pruebas_pasadas);

	void* estado_null=lista_elemento_en_posicion(lista,3);
	assert(estado_null==NULL,"Obtener elemento en posicion devuelve NULL",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	lista_destruir(lista);
	return resultado;
}

/* Inserto diferentes tipos de datos. En la prueba se ve que guarde correctamente enteros, flotantes (double), y caracteres.
 * Luego los voy sacando y verifico que salgan en el orden esperado.
 */
bool inserto_diferentes_tipos_de_elementos_y_los_voy_sacando(){
	printf("\n-----------PRUEBA DE INSERTAR DIFERENTES ELEMENTOS-----------\n");
	int estado,contador_pruebas_pasadas=0;
	int  pruebas_a_pasar=12;
	bool resultado=false;

	int enteros[MAX]={10,20,30};
	double constantes[MAX]={PI,EULER,GAS_IDEAL};
	char letras[MAX]="ASD";

	lista_t* lista=lista_crear();

	insertar_enteros(lista,enteros,MAX);
	insertar_flotantes(lista,constantes,MAX);
	insertar_caracteres(lista,letras,MAX);

	assert(lista_elementos(lista)==(3*MAX),"La lista devuelve que tiene 9 elementos",contador_pruebas_pasadas);

	assert(*(char*)lista_ultimo(lista)=='D',"Devuelve el caracter esperado si quiero el ultimo elemento",contador_pruebas_pasadas);

 	estado=lista_insertar_en_posicion(lista,&constantes[1],1);
 	assert(estado==EXITO,"Insertar en posicion determinada una constante",contador_pruebas_pasadas);

 	estado=lista_insertar_en_posicion(lista,&letras[2],4);
 	assert(estado==EXITO,"Insertar en posicion determinada una letra",contador_pruebas_pasadas);

	char letra=*(char*)lista_elemento_en_posicion(lista,4);
	assert(letra==letras[2],"Obtener en posicion devuelve la letra insertada",contador_pruebas_pasadas);

 	assert(lista_elementos(lista)==11,"La lista devuelve que tiene 11 elementos",contador_pruebas_pasadas);

	estado=lista_borrar(lista);
	assert(estado==EXITO,"Borrar de la lista el ultimo elemento",contador_pruebas_pasadas);

	estado=lista_borrar_de_posicion(lista,0);
	assert(estado==EXITO,"Borrar de posicion otro elemento",contador_pruebas_pasadas);

	assert(!lista_vacia(lista),"La lista no esta vacia",contador_pruebas_pasadas);

	int elemento=*(int*)lista_elemento_en_posicion(lista,2);
	assert(elemento==enteros[2],"Obtener elemento en posicion devuelve el entero esperado",contador_pruebas_pasadas);

	double constante=*(double*)lista_elemento_en_posicion(lista,4);
	assert(constante==constantes[0],"Obtener elemento en posicion devuelve la constante esperada",contador_pruebas_pasadas);

	assert(*(char*)lista_ultimo(lista)==letras[1],"Obtengo el ultimo elemento y es el esperado",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	lista_destruir(lista);
	return resultado;
}

/* Se prueba que se guarden correctamente 800 elementos. Estos elementos son numeros generados de forma random.
 * Una vez insertados, se borra hasta la mitad y se verifica que lo haya hecho hecho de forma correcta. Luego,
 * se vacia la lista y se prueba que quede vacia.
 */
bool inserto_en_cantidad_800_elementos(){
	printf("\n-----------PRUEBA DE INSERTAR EN CANTIDAD-----------\n");
	int estado,contador_pruebas_pasadas=0;
	int pruebas_a_pasar=11;
	int enteros[MAXIMO];
	bool resultado=false;
	cargar_enteros(enteros,MAXIMO);

	lista_t* lista=lista_crear();

	insertar_enteros(lista,enteros,MAXIMO);
	
	assert(lista_elementos(lista)==MAXIMO,"La lista devuelve que tiene 800 elementos",contador_pruebas_pasadas);

 	estado=lista_insertar_en_posicion(lista,&enteros[10],42);
 	assert(estado==EXITO,"Insertar en posicion determinada",contador_pruebas_pasadas);

	assert(lista_elementos(lista)==(MAXIMO+1),"La lista devuelve que tiene 801 elementos",contador_pruebas_pasadas);

 	estado=lista_insertar_en_posicion(lista,&enteros[60],103);
 	assert(estado==EXITO,"Insertar en posicion determinada otro elemento",contador_pruebas_pasadas);

	assert(lista_elementos(lista)==(MAXIMO+2),"La lista devuelve que tiene 802 elementos",contador_pruebas_pasadas);

	estado=lista_borrar(lista);
	assert(estado==EXITO,"Borrar de la lista el ultimo elemento",contador_pruebas_pasadas);

	estado=lista_borrar_de_posicion(lista,2);
	assert(estado==EXITO,"Borrar de posicion otro elemento",contador_pruebas_pasadas);

	assert(lista_elementos(lista)==MAXIMO,"La lista devuelve que tiene 800 elementos",contador_pruebas_pasadas);

	borrar_varias_veces(lista,MAXIMO/2);

	assert(!lista_vacia(lista),"La lista no esta vacia",contador_pruebas_pasadas);

	assert(lista_elementos(lista)==(MAXIMO/2),"La lista devuelve que tiene 400 elementos",contador_pruebas_pasadas);

	borrar_varias_veces(lista,MAXIMO/2);

	assert(lista_vacia(lista),"La lista esta vacia",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	lista_destruir(lista);
	return resultado;
}

/* Inserta 3 elementos y luego borra 4. De esta forma, se verifica que devuelva NULL y error para cada caso.
 */
bool intentar_borrar_mas_elementos_de_los_que_hay(){
	printf("\n-----------PRUEBA DE BORRAR MAS DE LO GUARDADO-----------\n");
	int estado,contador_pruebas_pasadas=0;
	int enteros[MAX];
	int pruebas_a_pasar=6;
	cargar_enteros(enteros,MAX);
	bool resultado=false;
	
	lista_t* lista=lista_crear();

	insertar_enteros(lista,enteros,MAX);
	
	assert(lista_elementos(lista)==MAX,"La lista devuelve que tiene 3 elementos",contador_pruebas_pasadas);

	estado=lista_borrar(lista);
	assert(estado==EXITO,"Borrar de la lista el ultimo elemento",contador_pruebas_pasadas);

	estado=lista_borrar_de_posicion(lista,0);
	assert(estado==EXITO,"Borrar de posicion otro elemento",contador_pruebas_pasadas);

	assert(!lista_vacia(lista),"La lista no esta vacia",contador_pruebas_pasadas);

	estado=lista_borrar(lista);
	estado=lista_borrar(lista);

	assert(estado==ERROR,"La lista no puede borrar mas de lo que tiene",contador_pruebas_pasadas);

	assert(lista_vacia(lista),"La lista esta vacia",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	lista_destruir(lista);
	return resultado;
}


/* Intenta realizar las diferentes acciones que tiene el iterador cuando este no esta creado
 */
bool intentar_realizar_acciones_con_iterador_nulo(){
	printf("\n-----------PRUEBA DE ITERADOR NULO-----------\n");
	int contador_pruebas_pasadas=0;
	int enteros[MAX];
	int pruebas_a_pasar=7;
	cargar_enteros(enteros,MAX);
	bool resultado=false;

	lista_t* lista=NULL;
	lista_iterador_t* iterador=lista_iterador_crear(lista);;
	
	printf("Verifico primero con la lista sin crear.\n");

	assert(iterador==NULL,"El iterador es NULL cuando no existe la lista",contador_pruebas_pasadas);

	assert(!lista_iterador_tiene_siguiente(iterador),"Devuelve que no tiene siguiente",contador_pruebas_pasadas);

	assert(lista_iterador_siguiente(iterador)==NULL,"Devuelve NULL si quiere avanzar al siguiente",contador_pruebas_pasadas);

	printf("\nCreo la lista.\n");
	lista=lista_crear();

	assert(!lista_iterador_tiene_siguiente(iterador),"Devuelve que no tiene siguiente sin cargar elementos",contador_pruebas_pasadas);

	assert(lista_iterador_siguiente(iterador)==NULL,"Devuelve NULL si quiere avanzar al siguiente sin cargar elementos",contador_pruebas_pasadas);

	insertar_enteros(lista,enteros,MAX);

	assert(!lista_iterador_tiene_siguiente(iterador),"Devuelve que no tiene siguiente con elementos cargados",contador_pruebas_pasadas);

	assert(lista_iterador_siguiente(iterador)==NULL,"Devuelve NULL si quiere avanzar al siguiente si tiene elementos",contador_pruebas_pasadas);

	lista_destruir(lista);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	return resultado;
}

/* Se prueba el funcionamiento del iterador interno. Se manda una frase a una funcion y se libera memoria almancenada en el heap.
 */
bool utilizar_iterador_interno_aplicando_diferentes_funciones(){
	printf("\n-----------PRUEBA DE ITERADOR INTERNO-----------\n");
	int contador_pruebas_pasadas=0;
	char* frase_de_prueba="algoritmos2";
	int pruebas_a_pasar=3;
	bool resultado=false;
	
	lista_t* lista=lista_crear();
	lista_insertar(lista,frase_de_prueba);

	lista_con_cada_elemento(lista,funcion_de_prueba_mostrar_string);
	char* frase_devuelta=(char*)lista_ultimo(lista);

	assert(strcmp(frase_devuelta,"algoritmos2")==0,"La frase insertada sigue sin modificarse",contador_pruebas_pasadas);

	lista_borrar(lista);

	printf("\nCreo elementos en memoria dinamica y mando para que la libere.\n");

	int* entero=malloc(sizeof(int*));
	float* constante=malloc(sizeof(float*));

	lista_insertar(lista,entero);
	lista_insertar(lista,constante);

	assert(lista_elementos(lista)==2,"Hay dos elementos en memoria dinamica",contador_pruebas_pasadas);
	lista_con_cada_elemento(lista,free);

	lista_borrar(lista);
	lista_borrar(lista);

	assert(lista_vacia(lista),"La lista quedo vacia",contador_pruebas_pasadas);

	lista_destruir(lista);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	return resultado;
}

/* Verifica la utilizacion del iterador externo
 */
bool probar_iterador_externo(){
	printf("\n-----------PRUEBA DE ITERADOR EXTERNO-----------\n");
	int contador_pruebas_pasadas=0;
	char* frase_de_prueba="algoritmos2";
	int enteros[MAX]={10,20,30};
	int pruebas_a_pasar=4;
	bool resultado=false;
	
	lista_t* lista=lista_crear();
	lista_insertar(lista,frase_de_prueba);
	insertar_enteros(lista,enteros,MAX);

	lista_iterador_t* iterador=lista_iterador_crear(lista);

	assert(lista_iterador_tiene_siguiente(iterador),"El iterador tiene siguiente",contador_pruebas_pasadas);
	lista_iterador_siguiente(iterador);
	lista_iterador_siguiente(iterador);

	assert(*(int*)lista_iterador_siguiente(iterador)==enteros[1],"El iterador devuelve el elemento esperado",contador_pruebas_pasadas);
	lista_iterador_siguiente(iterador);

	assert(!lista_iterador_tiene_siguiente(iterador),"El iterador no tiene siguiente",contador_pruebas_pasadas);

	assert(lista_iterador_siguiente(iterador)==NULL,"Intento avanzar cuando el iterador no tiene siguiente, devuelve NULL",contador_pruebas_pasadas);
	
	lista_iterador_destruir(iterador);
	lista_destruir(lista);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);
	return resultado;
}

/* Realiza las pruebas
 */
void realizar_pruebas(){
	int pruebas_pasadas=0;
	bool estado;

	printf("\n////--------------------PRUEBAS DE CASOS NULOS--------------------////\n");

	estado=intentar_realizar_acciones_con_lista_nula();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=insertar_elemento_nulo_y_realizar_acciones_con_el();
	mostrar_resultado(estado,&pruebas_pasadas);

	printf("\n////---------------------PRUEBAS DE INSERTAR---------------------////\n");

	estado=inserto_diferentes_tipos_de_elementos_y_los_voy_sacando();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=inserto_en_cantidad_800_elementos();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=intentar_borrar_mas_elementos_de_los_que_hay();
	mostrar_resultado(estado,&pruebas_pasadas);

	printf("\n////---------------------PRUEBAS CON ITERADORES---------------------////\n");

	estado=intentar_realizar_acciones_con_iterador_nulo();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=utilizar_iterador_interno_aplicando_diferentes_funciones();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=probar_iterador_externo();
	mostrar_resultado(estado,&pruebas_pasadas);
	
	printf("\n////-------------------------------------------------------------////\n");

	printf("Paso %i pruebas de 8\n",pruebas_pasadas);
}

/* Realiza las pruebas
 */
int main(){
	printf("----------------PRUEBAS DE LA LISTA----------------\n");
	realizar_pruebas();

	return 0;
}
