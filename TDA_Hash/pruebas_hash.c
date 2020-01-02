#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mi_assert.h"
#include "hash.h"
#include "hash_iterador.h"
#define EXITO 0
#define ERROR -1
#define NO_EXISTE 0
#define MAX 10
#define ES_MAYOR 1
#define SON_IGUALES 0
#define ES_MENOR -1
const int MAXIMO_PRUEBA_CANT=800,MAX_CLAVE=10,MAX_LETRAS=36;
const int SIN_ELEMENTOS=0,FACTOR_CARGA_PRUEBA=7;
const double PI=3.14159,EULER=2.71828;


//------------------------FUNCIONES AUXILIARES-------------------------//

	/* Inserta en el hash enteros. Necesita del tope positivo.
	 */
	void insertar_enteros(hash_t* hash,int elementos[MAXIMO_PRUEBA_CANT],char claves[MAXIMO_PRUEBA_CANT][MAX_CLAVE],int tope){
		for(int i=0;i<tope;i++){
			hash_insertar(hash,claves[i],&elementos[i]);
		}
	}

	/* Borra del hash varios elementos. Necesita del tope positivo.
	 */
	void borrar_varias_veces(hash_t* hash,char claves[MAXIMO_PRUEBA_CANT][MAX_CLAVE],int tope){
		for(int i=0;i<tope;i++){
			hash_quitar(hash,claves[i]);
		}
	}

	/* Carga un vector con numeros enteros. La funcion necesita un tope que sea positivo.
	 */
	void cargar_enteros(int enteros[MAXIMO_PRUEBA_CANT],int tope){
		for(int i=0;i<tope;i++){
			enteros[i]=i*tope/FACTOR_CARGA_PRUEBA;
		}
	}

	/* Carga una matriz de claves, necesita del tope de claves.
	 * Las claves tendran un tamanio de 10 y los caracteres que podran tener son elegidos de un string con 36 caracteres distintos.
	 */
	void crear_claves(char claves[MAXIMO_PRUEBA_CANT][MAX_CLAVE],int tope){
		const char* letras_validas="ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
		int k=0;
		for (int i = 0; i < tope; i++) {
			for (int j = 0; j < MAX_CLAVE-1; j++) {
				claves[i][j]=letras_validas[k];
				k++;
				if(k==MAX_CLAVE){
					k=0;
				}
			}
			claves[i][MAX_CLAVE/2]=(char)i;
			claves[i][MAX_CLAVE-1]='\0';
		}
	}

//--------------------------------PRUEBAS----------------------------//

/* Se manda un hash que no fue creado, y se intenta realizar cada accion que puede hacer. En cada una
 * se verifica que devuelva el estado esperado.
 */
bool intentar_realizar_acciones_con_hash_nulo(){
	printf("\n-----------PRUEBA DE HASH SIN CREAR-----------\n");
	int elemento_de_prueba=MAX;
	int contador_pruebas_pasadas=0,pruebas_a_pasar=6;
	const char* clave_prueba="103AJC";

	hash_t* hash=NULL;
	assert(hash_insertar(hash,clave_prueba,&elemento_de_prueba),"Si quiero insertar, devuelve error",contador_pruebas_pasadas);

	assert(hash_quitar(hash,clave_prueba),"Si quiero quitar un elemento, devuelve error",contador_pruebas_pasadas);

	assert(hash_obtener(hash,clave_prueba)==NULL,"Si pido un elemento, devuelve NULL",contador_pruebas_pasadas);

	assert(!hash_contiene(hash,clave_prueba),"Si pregunto si contiene un elemento, devuelve false",contador_pruebas_pasadas);

	assert(hash_cantidad(hash)==0,"Si pido la cantidad, esta es 0",contador_pruebas_pasadas);

	hash_iterador_t* iterador=hash_iterador_crear(hash);
	assert(iterador==NULL,"Si pido crear un iterador, este es NULL",contador_pruebas_pasadas);

	return verificar_si_paso_las_pruebas(contador_pruebas_pasadas,pruebas_a_pasar);
}

/* Se inserta un elemento NULL, y se ve si el hash lo acepta.
 */
bool insertar_elemento_nulo_y_realizar_acciones_con_el(){
	printf("\n-----------PRUEBA DE INSERTAR NULL-----------\n");
	int estado,contador_pruebas_pasadas=0;
	int pruebas_a_pasar=6;

	void* elemento_nulo=NULL;
	const char* clave_null="NULL000";

	hash_t* hash=hash_crear(NULL,1);
	assert(hash!=NULL,"Se creo el hash",contador_pruebas_pasadas);

	estado=hash_insertar(hash,clave_null,elemento_nulo);
	assert(estado==EXITO,"Se inserto NULL",contador_pruebas_pasadas);

	assert(hash_insertar(hash,NULL,elemento_nulo)==ERROR,"No se puede insertar con una clave NULL",contador_pruebas_pasadas);

	assert(hash_cantidad(hash)==1,"Devuelve que tiene un elemento guardado",contador_pruebas_pasadas);

	assert(hash_obtener(hash,clave_null)==NULL,"Si pido que lo devuelva, lo devuelve",contador_pruebas_pasadas);

	assert(hash_quitar(hash,clave_null)==EXITO,"Quito el elemento nulo",contador_pruebas_pasadas);

	hash_destruir(hash);

	return verificar_si_paso_las_pruebas(contador_pruebas_pasadas,pruebas_a_pasar);
}


/* Inserto diferentes tipos de datos. En la prueba se ve que guarde correctamente enteros, flotantes (double), y caracteres.
 */
bool inserto_diferentes_tipos_de_elementos_y_los_voy_sacando(){
	printf("\n-----------PRUEBA DE INSERTAR DIFERENTES ELEMENTOS-----------\n");
	int contador_pruebas_pasadas=0;
	int  pruebas_a_pasar=21;

	int elemento_entero=42;
	char* frase_prueba="Algoritmos 2 - Hash";
	char caracter_prueba='Z';
	double numero_irracional=PI;
	const char* clave_entero="000042";
	const char* clave_frase="ALGO2";
	const char* clave_caracter="00000Z";
	const char* clave_irracional="314159";

	hash_t* hash=hash_crear(NULL,MAX);
	assert(hash_insertar(hash,clave_frase,frase_prueba)==EXITO,"Inserto una frase en el hash",contador_pruebas_pasadas);
	assert(hash_insertar(hash,clave_caracter,&caracter_prueba)==EXITO,"Inserto un caracter en el hash",contador_pruebas_pasadas);
	assert(hash_insertar(hash,clave_entero,&elemento_entero)==EXITO,"Inserto un numero entero en el hash",contador_pruebas_pasadas);
	assert(hash_insertar(hash,clave_irracional,&numero_irracional)==EXITO,"Inserto un numero irracional en el hash",contador_pruebas_pasadas);

	assert(hash_cantidad(hash)==4,"El hash tiene 4 elementos guardados",contador_pruebas_pasadas);

	assert((*(int*)hash_obtener(hash,clave_entero))==elemento_entero,"Pido el entero y me lo da",contador_pruebas_pasadas);
	assert(strcmp(hash_obtener(hash,clave_frase),frase_prueba)==0,"Pido la frase y me la da",contador_pruebas_pasadas);
	assert(*(char*)hash_obtener(hash,clave_caracter)==caracter_prueba,"Pido el caracter y me lo devuelve",contador_pruebas_pasadas);
	assert((*(double*)hash_obtener(hash,clave_irracional))==numero_irracional,"Pido el numero irracional y me lo da",contador_pruebas_pasadas);

	printf("\nCambio el numero irracional y utilizo la misma clave\n");
	double numero_irracional2=EULER;
	assert(hash_insertar(hash,clave_irracional,&numero_irracional2)==EXITO,"Cambio el elemento con la misma clave",contador_pruebas_pasadas);
	assert((*(double*)hash_obtener(hash,clave_irracional))==numero_irracional2,"Si lo pido, me da el numero nuevo",contador_pruebas_pasadas);

	assert(hash_cantidad(hash)==4,"El hash sigue teniendo 4 elementos guardados",contador_pruebas_pasadas);

	assert(hash_quitar(hash,clave_entero)==EXITO,"Quito el entero del hash",contador_pruebas_pasadas);
	assert(hash_cantidad(hash)==3,"El hash tiene 3 elementos ahora",contador_pruebas_pasadas);
	assert(!hash_contiene(hash,clave_entero),"El hash dice que no contiene la clave",contador_pruebas_pasadas);
	assert(hash_obtener(hash,clave_entero)==NULL,"Si pido el elemento cuando no esta, devuelve NULL",contador_pruebas_pasadas);

	printf("\nQuito los elementos que quedan\n");
	assert(hash_quitar(hash,clave_caracter)==EXITO,"Quito el caracter del hash",contador_pruebas_pasadas);
	assert(hash_quitar(hash,clave_frase)==EXITO,"Quito la frase del hash",contador_pruebas_pasadas);
	assert(hash_quitar(hash,clave_irracional)==EXITO,"Quito el irracional del hash",contador_pruebas_pasadas);
	assert(!hash_contiene(hash,clave_frase),"Mando la clave de la frase y dice que no la tiene",contador_pruebas_pasadas);
	assert(hash_cantidad(hash)==0,"La cantidad es 0",contador_pruebas_pasadas);

	hash_destruir(hash);

	return verificar_si_paso_las_pruebas(contador_pruebas_pasadas,pruebas_a_pasar);
}

/* Se prueba que se guarden correctamente 800 elementos. Estos elementos son enteros creados por un generador.
 * Una vez insertados, se prueban las diferenetes funciones del hash, mandando un elemento con clave unica.
 */
bool inserto_en_cantidad_800_elementos(){
	printf("\n-----------PRUEBA DE INSERTAR EN CANTIDAD-----------\n");
	int contador_pruebas_pasadas=0;
	int pruebas_a_pasar=14;

	int enteros[MAXIMO_PRUEBA_CANT],numero_unico=50000;
	const char* clave_unica="###@@@";
	char claves[MAXIMO_PRUEBA_CANT][MAX_CLAVE];
	cargar_enteros(enteros,MAXIMO_PRUEBA_CANT);
	crear_claves(claves,MAXIMO_PRUEBA_CANT);

	hash_t* hash=hash_crear(NULL,50);
	assert(hash!=NULL,"Se creo el hash",contador_pruebas_pasadas);

	insertar_enteros(hash,enteros,claves,MAXIMO_PRUEBA_CANT);
	assert(hash_cantidad(hash)==MAXIMO_PRUEBA_CANT,"Se insertaron 800 elementos en el hash",contador_pruebas_pasadas);

	printf("\nInserto un numero unico con una clave unica\n");
	assert(!hash_contiene(hash,clave_unica),"El hash todavia no contiene el elemento unico",contador_pruebas_pasadas);
	assert(hash_insertar(hash,clave_unica,&numero_unico)==EXITO,"Se inserto un elemento con clave unica",contador_pruebas_pasadas);
	assert(hash_cantidad(hash)==(MAXIMO_PRUEBA_CANT+1),"Hay 801 elementos en el hash",contador_pruebas_pasadas);
	assert(hash_contiene(hash,clave_unica),"El hash dice que contiene el elemento con la clave",contador_pruebas_pasadas);
	assert(*(int*)hash_obtener(hash,clave_unica)==numero_unico,"Si pido el numero unico me lo devuelve",contador_pruebas_pasadas);
	assert(hash_quitar(hash,clave_unica)==EXITO,"Se quito el elemento unico",contador_pruebas_pasadas);
	assert(hash_cantidad(hash)==MAXIMO_PRUEBA_CANT,"Hay 800 elementos en el hash",contador_pruebas_pasadas);
	assert(!hash_contiene(hash,clave_unica),"Si busco denuevo la clave unica me dice que no esta",contador_pruebas_pasadas);
	assert(hash_obtener(hash,clave_unica)==NULL,"Si lo busco me devuelve NULL",contador_pruebas_pasadas);

	printf("\nVacio el hash ahora\n");
	borrar_varias_veces(hash,claves,MAXIMO_PRUEBA_CANT);
	assert(hash_cantidad(hash)==0,"El hash esta vacio",contador_pruebas_pasadas);
	assert(!hash_contiene(hash,claves[4]),"Si pregunto por un elemento devuelve que no lo tiene",contador_pruebas_pasadas);
	assert(!hash_obtener(hash,claves[2]),"Si pido otro elemento devuele NULL",contador_pruebas_pasadas);

 	hash_destruir(hash);
	return verificar_si_paso_las_pruebas(contador_pruebas_pasadas,pruebas_a_pasar);
}

/* Se inserta una cantidad de elementos y se van borrando, viendo que el hash devuelva lo esperado.
 */
bool intentar_borrar_mas_elementos_de_los_que_hay(){
	printf("\n-----------PRUEBA DE BORRAR MAS DE LO GUARDADO-----------\n");
	int contador_pruebas_pasadas=0;
	int pruebas_a_pasar=8;
	int enteros[MAX];
	cargar_enteros(enteros,MAX);
	char claves[MAX][MAX_CLAVE];
	crear_claves(claves,MAX);

	hash_t* hash=hash_crear(NULL,MAX);
	insertar_enteros(hash,enteros,claves,MAX);
	assert(hash_cantidad(hash)==MAX,"La cantidad guardada es la esperada",contador_pruebas_pasadas);
	assert(hash_contiene(hash,claves[3]),"Pruebo que contenga una de las claves",contador_pruebas_pasadas);

	borrar_varias_veces(hash,claves,MAX-1);

	assert(hash_cantidad(hash)==1,"Guarda un solo elemento",contador_pruebas_pasadas);
	assert(hash_quitar(hash,claves[4])==ERROR,"No puede quitar un elemento que no esta",contador_pruebas_pasadas);
	assert(hash_quitar(hash,claves[9])==EXITO,"Quito el ultimo elemento",contador_pruebas_pasadas);
	assert(hash_quitar(hash,claves[9])==ERROR,"No puede quitar un elemento ya borrado",contador_pruebas_pasadas);
	assert(hash_quitar(hash,claves[7])==ERROR,"No puede quitar otro elemento que no esta",contador_pruebas_pasadas);
	assert(hash_cantidad(hash)==0,"El hash esta vacio",contador_pruebas_pasadas);

	hash_destruir(hash);

	return verificar_si_paso_las_pruebas(contador_pruebas_pasadas,pruebas_a_pasar);
}

/* Verifica que no se puedan realizar acciones cuando se tiene un iterador NULL
 */
bool probar_acciones_con_iterador_null(){
	printf("\n-----------PRUEBAS CON ITERADOR NULL-----------\n");
	int contador_pruebas_pasadas=0,pruebas_a_pasar=3;
	hash_t* hash=NULL;
	hash_iterador_t* iterador=hash_iterador_crear(hash);
	assert(iterador==NULL,"El iterador es NULL con un hash sin crear",contador_pruebas_pasadas);

	assert(!hash_iterador_tiene_siguiente(iterador),"Si pido el siguiente, devuelve que no tiene",contador_pruebas_pasadas);

	assert(hash_iterador_siguiente(iterador)==NULL,"Si avanzo, devuelve NULL",contador_pruebas_pasadas);

	return verificar_si_paso_las_pruebas(contador_pruebas_pasadas,pruebas_a_pasar);
}

/* Se prueba el correcto funcionamiento del iterador
 */
bool realizar_acciones_con_iterador(){
	printf("\n-----------PRUEBAS CON EL ITERADOR-----------\n");
	int contador_pruebas_pasadas=0,pruebas_a_pasar=7;
	int cantidad_elementos=0;
	int enteros[MAX];

	hash_t* hash=hash_crear(NULL,5);
	cargar_enteros(enteros,MAX);
	char claves[MAX][MAX_CLAVE];
	crear_claves(claves,MAX);
	insertar_enteros(hash,enteros,claves,MAX);

	hash_iterador_t* iterador=hash_iterador_crear(hash);
	assert(hash_iterador_tiene_siguiente(iterador),"El iterador tiene siguiente",contador_pruebas_pasadas);

	for(int i=0;i<MAX;i++){
		if(hash_iterador_tiene_siguiente(iterador)){
			hash_iterador_siguiente(iterador);
			cantidad_elementos++;
		}
	}

	assert(cantidad_elementos==MAX,"Se recorrieron los 10 elementos guardados",contador_pruebas_pasadas);
	borrar_varias_veces(hash,claves,MAX);

	hash_iterador_destruir(iterador);

	const char* clave_prueba="AAAAAA";
	char* frase_prueba="ALGO2";
	hash_insertar(hash,clave_prueba,frase_prueba);
	assert(hash_cantidad(hash)==1,"Esta el elemento guardado",contador_pruebas_pasadas);

	iterador=hash_iterador_crear(hash);
	assert(hash_iterador_tiene_siguiente(iterador),"El iterador tiene un elemento",contador_pruebas_pasadas);
	assert(strcmp((const char*)hash_iterador_siguiente(iterador),clave_prueba)==0,"Devolvio la clave esperada",contador_pruebas_pasadas);
	assert(!hash_iterador_tiene_siguiente(iterador),"El iterador no tiene siguiente ahora",contador_pruebas_pasadas);
	assert(hash_iterador_siguiente(iterador)==NULL,"Devuelve NULL",contador_pruebas_pasadas);

	hash_iterador_destruir(iterador);
	hash_destruir(hash);

	return verificar_si_paso_las_pruebas(contador_pruebas_pasadas,pruebas_a_pasar);
}


/* Realiza las pruebas
 */
void realizar_pruebas(){
	int pruebas_pasadas=0;
	bool estado;

	printf("\n////--------------------PRUEBAS DE CASOS NULOS--------------------////\n");

	estado=intentar_realizar_acciones_con_hash_nulo();
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

	estado=probar_acciones_con_iterador_null();
	mostrar_resultado(estado,&pruebas_pasadas);

	estado=realizar_acciones_con_iterador();
	mostrar_resultado(estado,&pruebas_pasadas);

	printf("\n////-------------------------------------------------------------////\n");

	printf("			Paso %i pruebas generales de 7\n",pruebas_pasadas);
}

/* Realiza las pruebas
 */
int main(){
	printf("--------------------------PRUEBAS DEL HASH------------------------\n");
	realizar_pruebas();
	printf("----------------------------------------------------------------\n");
	return 0;
}
