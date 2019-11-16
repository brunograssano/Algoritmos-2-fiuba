#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mi_assert.h"
#include "abb.h"
#define EXITO 0
#define ERROR -1
#define NO_EXISTE 0
#define MAX 10
#define ES_MAYOR 1
#define SON_IGUALES 0
#define ES_MENOR -1
const int MAXIMO=800;
const int SIN_ELEMENTOS=0;
const double PI=3.14159,EULER=2.71828,GAS_IDEAL=0.082,PHI=1.618;


//------------------------FUNCIONES AUXILIARES-------------------------//

	/* Inserta en el arbol caracteres. Necesita del tope positivo.
	 */
	void insertar_caracteres(abb_t* arbol,char* elementos,int tope){
		for(int i=0;i<tope;i++){
			arbol_insertar(arbol,&elementos[i]);
		}
	}

	/* Inserta en el arbol flotantes(Recibe douuble). Necesita del tope positivo.
	 */
	void insertar_flotantes(abb_t* arbol,double elementos[MAX],int tope){
		for(int i=0;i<tope;i++){
			arbol_insertar(arbol,&elementos[i]);
		}
	}

	/* Inserta en el arbol enteros. Necesita del tope positivo.
	 */
	void insertar_enteros(abb_t* arbol,int elementos[MAXIMO],int tope){
		for(int i=0;i<tope;i++){
			arbol_insertar(arbol,&elementos[i]);
		}
	}

	/* Borra del arbol varios elementos. Necesita del tope positivo.
	 */
	void borrar_varias_veces(abb_t* arbol,int tope,int enteros[MAXIMO]){
		for(int i=0;i<tope;i++){
			arbol_borrar(arbol,&enteros[i]);
		}
	}

	/* Carga un vector con numeros enteros generados de forma semirandom. La funcion necesita un tope que sea positivo.
	 */
	void cargar_enteros(int enteros[MAXIMO],int tope){
		for(int i=0;i<tope;i++){
			enteros[i]=rand()%MAXIMO;
		}
	}

	/* Funcion que se utiliza para comparar enteros. Si el primero es mayor devuelve 1, si es menor -1,
	 * si son iguales devuelve 0.
	 */
	int comparador_de_enteros(void* entero1,void* entero2){
		if(*(int*)entero1>*(int*)entero2){
			return ES_MAYOR;
		}
		else if(*(int*)entero1<*(int*)entero2){
			return ES_MENOR;
		}
		else{
			return SON_IGUALES;
		}
	}

	/* Funcion que se utiliza para comparar flotantes (double). Si el primero es mayor devuelve 1, si es menor -1,
	 * si son iguales devuelve 0.
	 */
	int comparador_de_float(void* flotante1,void* flotante2){
		if(*(double*)flotante1>*(double*)flotante2){
			return ES_MAYOR;
		}
		else if(*(double*)flotante1<*(double*)flotante2){
			return ES_MENOR;
		}
		else{
			return SON_IGUALES;
		}
	}

	/* Funcion que se utiliza para comparar letras. Si el primero es mayor devuelve 1, si es menor -1,
	 * si son iguales devuelve 0.
	 */
	int comparador_de_letras(void* letra1,void* letra2){
		if(*(char*)letra1>*(char*)letra2){
			return ES_MAYOR;
		}
		else if(*(char*)letra1<*(char*)letra2){
			return ES_MENOR;
		}
		else{
			return SON_IGUALES;
		}
	}

	/* Funcion de prueba para los recorridos del iterador. Si llega a 5 el contador devuelve que termino el mensaje guardado.
	 */
	bool imprimir_mensaje(void* elemento, void* contador){
		if(*(int*)contador==5){
			return true;
		}
		(*(int*)contador)++;
		printf("%c",*(char*)elemento);
		return false;
	}

	/* Va multiplicando un acumulador hasta pasar un limite impuesto de 100
	 */
	bool multiplicar_hasta_pasar_limite(void* elemento, void* acumulador){
		(*(int*)acumulador) *=  (*(int*)elemento);
		return (*(int*)acumulador)>=100;
	}

	/* Imprime el arbol de forma acostada, si apunta a NULL, lo representa con una N
 	*/
	void mostrar_arbol(abb_t* arbol,nodo_abb_t* nodo_arbol,int contador){
	    if(nodo_arbol==NULL){
	        for(int i=0;i<contador;i++){
	            printf("      ");
	        }
	        printf("N\n");
	        return;
	    }
	    mostrar_arbol(arbol,nodo_arbol->derecha,contador+1);
	    for(int i=0;i<contador;i++){
	            printf("      ");
	    }
	    printf("%i\n", (*(int*)nodo_arbol->elemento));
	    mostrar_arbol(arbol,nodo_arbol->izquierda,contador+1);
	}

	/*Muestra el arbol
	*/
	void mostrar_arbol_entero(abb_t* arbol){
	    printf("\n------------ARBOL GUARDADO------------\n");
	    mostrar_arbol(arbol,arbol->nodo_raiz,0);
	    printf("--------------------------------------\n\n");
	}

//--------------------------------PRUEBAS----------------------------//

/* Se manda un arbol que no fue creado, y se intenta realizar cada accion que puede hacer. En cada una
 * se verifica que devuelvan el estado esperado.
 */
bool intentar_realizar_acciones_con_arbol_nulo(){
	printf("\n-----------PRUEBA DE ARBOL SIN CREAR-----------\n");
	int estado,elemento_de_prueba=MAX;
	int array_de_prueba[MAX];
	int contador_pruebas_pasadas=0,pruebas_a_pasar=8;
	bool resultado=false;

	abb_t* arbol=NULL;
	estado=arbol_insertar(arbol,&elemento_de_prueba);
 	assert(estado==ERROR,"No se puede insertar en un arbol sin crear",contador_pruebas_pasadas);

	estado=arbol_borrar(arbol,&elemento_de_prueba);
	assert(estado==ERROR,"No se puede borrar de un arbol sin crear",contador_pruebas_pasadas);

	assert(arbol_vacio(arbol),"El arbol devuelve que esta vacio",contador_pruebas_pasadas);

	assert(arbol_raiz(arbol)==NULL,"Si pido la raiz devuelve NULL",contador_pruebas_pasadas);

	assert(arbol_buscar(arbol,&elemento_de_prueba)==NULL,"Si pido que busque un elemento devuelve NULL",contador_pruebas_pasadas);

	estado=arbol_recorrido_inorden(arbol,(void**)array_de_prueba,MAX);
	assert(estado==NO_EXISTE,"Si intento recorrer en inorden devuelve que no existe",contador_pruebas_pasadas);

	estado=arbol_recorrido_postorden(arbol,(void**)array_de_prueba,MAX);
	assert(estado==NO_EXISTE,"Si intento recorrer en postorden devuelve que no existe",contador_pruebas_pasadas);

	estado=arbol_recorrido_preorden(arbol,(void**)array_de_prueba,MAX);
	assert(estado==NO_EXISTE,"Si intento recorrer en preorden devuelve que no existe",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	return resultado;
}

/* Se inserta un elemento NULL, y se ve si el arbol lo puede guardar. 
 */
bool insertar_elemento_nulo_y_realizar_acciones_con_el(){
	printf("\n-----------PRUEBA DE INSERTAR NULL-----------\n");
	int estado,contador_pruebas_pasadas=0;
	int pruebas_a_pasar=2;
	void* elemento_nulo=NULL;
	bool resultado=false;

	abb_t* arbol=arbol_crear(NULL,NULL);

	estado=arbol_insertar(arbol,&elemento_nulo);
 	assert(estado==EXITO,"Insertar elemento nulo",contador_pruebas_pasadas);

	assert(!arbol_vacio(arbol),"El arbol no esta vacio",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	arbol_destruir(arbol);
	return resultado;
}

/* Se evalua el funcionamiento del arbol cuando este guarda numeros enteros
*/
int pruebas_con_arbol_de_enteros(){
	int contador_pruebas_pasadas=0;
	int auxiliar;
	int enteros[MAX]={50,30,40,20,10,70,60,90,80,100};

	printf("\nCreo un arbol en el que inserto enteros.\n");
	abb_t* arbol=arbol_crear(comparador_de_enteros,NULL);
	assert(arbol!=NULL,"El arbol fue creado",contador_pruebas_pasadas);

	insertar_enteros(arbol,enteros,MAX);

	printf("\nVeo que devuelva los elementos esperados.\n");
	assert(*(int*)arbol_raiz(arbol)==enteros[0],"El nodo raiz es 50",contador_pruebas_pasadas);

	auxiliar=enteros[5];
	assert(*(int*)arbol_buscar(arbol,&auxiliar)==enteros[5],"Si pido el 70 me lo devuelve",contador_pruebas_pasadas);

	auxiliar=enteros[9];
	assert(*(int*)arbol_buscar(arbol,&auxiliar)==enteros[9],"Si pido el 100 me lo devuelve",contador_pruebas_pasadas);

	auxiliar=enteros[2];
	assert(*(int*)arbol_buscar(arbol,&auxiliar)==enteros[2],"Si pido el 40 me lo devuelve",contador_pruebas_pasadas);

	int *recorridos[MAX];
	printf("\nPruebo que los recorridos salgan como los espero, reduciendo la cantidad del vector para cada recorrido.\n");
	int esperados_pre[MAX]={50,30,20,10,40,70,60,90,80,100};
	auxiliar=arbol_recorrido_preorden(arbol,(void**)recorridos,MAX);
	assert(auxiliar==MAX,"La cantidad guardada es la esperada",contador_pruebas_pasadas);
	assert_vectores(recorridos,esperados_pre,MAX,"La salida en preorden corresponde con la esperada",contador_pruebas_pasadas);
	
	int esperados_in[MAX]={10,20,30,40,50};
	auxiliar=arbol_recorrido_inorden(arbol,(void**)recorridos,5);
	assert(auxiliar==5,"La cantidad guardada es la esperada",contador_pruebas_pasadas);
	assert_vectores(recorridos,esperados_in,5,"La salida en inorden corresponde con la esperada",contador_pruebas_pasadas);

	int esperados_post[MAX]={10};
	auxiliar=arbol_recorrido_postorden(arbol,(void**)recorridos,1);
	assert(auxiliar==1,"La cantidad guardada es la esperada con tamanio 1",contador_pruebas_pasadas);
	assert(*recorridos[0]==esperados_post[0],"La salida postorden corresponde con la esperada",contador_pruebas_pasadas);

	auxiliar=arbol_recorrido_postorden(arbol,(void**)recorridos,0);
	assert(auxiliar==0,"Si mando de tamanio del array 0, su cantidad es 0",contador_pruebas_pasadas);

	printf("\nBorro elementos (50,30,40,20,10)\n");
	borrar_varias_veces(arbol,5,enteros);
	assert(*(int*)arbol_raiz(arbol)==enteros[6],"La raiz es el 60",contador_pruebas_pasadas);
	
	auxiliar=enteros[5];
	assert(arbol_borrar(arbol,&auxiliar)==EXITO,"Borro el 70 del arbol",contador_pruebas_pasadas);
	assert(arbol_buscar(arbol,&auxiliar)==NULL,"Si lo busco no esta en el arbol",contador_pruebas_pasadas);

	arbol_destruir(arbol);
	return contador_pruebas_pasadas;
}

/* Se evalua el funcionamiento del arbol cuando este guarda flotantes(double)
*/
int pruebas_con_arbol_de_flotantes(){
	int contador_pruebas_pasadas=0;
	double constantes[MAX]={EULER,PI,GAS_IDEAL,PHI};

	printf("\n\nCreo otro arbol con flotantes\n");
	abb_t* arbol=arbol_crear(comparador_de_float,NULL);

	insertar_flotantes(arbol,constantes,4);

	assert(*(double*)arbol_buscar(arbol,&constantes[1])==PI,"Me devuelve el numero irracional Pi",contador_pruebas_pasadas);

	assert(arbol_borrar(arbol,&constantes[3])==EXITO,"Borro un numero del arbol",contador_pruebas_pasadas);

	assert(arbol_buscar(arbol,&constantes[3])==NULL,"Si busco el numero no esta",contador_pruebas_pasadas);

	assert(*(double*)arbol_raiz(arbol)==EULER,"La raiz es el numero de Euler",contador_pruebas_pasadas);

	arbol_destruir(arbol);

	return contador_pruebas_pasadas;
}

/* Se evalua el funcionamiento del arbol cuando este guarda caracteres
*/
int pruebas_con_arbol_de_letras(){
	int contador_pruebas_pasadas=0,auxiliar;
	char letras[MAX]="ABCDEFGHIJ",*obtenido[MAX];

	printf("\n\nCreo otro arbol con letras\n");
	abb_t* arbol=arbol_crear(comparador_de_letras,NULL);

	insertar_caracteres(arbol,letras,MAX);

	char letra_unica='Z';
	assert(arbol_buscar(arbol,&letra_unica)==NULL,"Devuelve NULL con una letra que no esta",contador_pruebas_pasadas);

	auxiliar=arbol_recorrido_inorden(arbol,(void**) obtenido,MAX);
	assert(auxiliar==MAX,"Esta guardada la cantidad esperada",contador_pruebas_pasadas);

	assert(strcmp(letras,*obtenido)==0,"Recorrido inorden es el esperado",contador_pruebas_pasadas);

	assert(arbol_borrar(arbol,&letras[3])==EXITO,"Borro una letra del arbol",contador_pruebas_pasadas);

	assert(*(char*)arbol_raiz(arbol)==letras[0],"La raiz es la letra A",contador_pruebas_pasadas);

	arbol_destruir(arbol);

	return contador_pruebas_pasadas;
}


/* Inserto diferentes tipos de datos. En la prueba se ve que guarde correctamente enteros, flotantes (double), y caracteres.
 * Luego los voy sacando y verifico que salgan en el orden esperado.
 */
bool inserto_diferentes_tipos_de_elementos_y_los_voy_sacando(){
	printf("\n-----------PRUEBA DE INSERTAR DIFERENTES ELEMENTOS-----------\n");
	int contador_pruebas_pasadas=0;
	int  pruebas_a_pasar=24;
	bool resultado=false;

	contador_pruebas_pasadas=pruebas_con_arbol_de_enteros();
	contador_pruebas_pasadas+=pruebas_con_arbol_de_flotantes();
	contador_pruebas_pasadas+=pruebas_con_arbol_de_letras();

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);
	return resultado;
}

/* Se prueba que se guarden correctamente 800 elementos. Estos elementos son numeros generados de forma random.
 * Una vez insertados, se borra hasta la mitad y se verifica que lo haya hecho hecho de forma correcta. Luego,
 * se vacia la arbol y se prueba que quede vacia.
 */
bool inserto_en_cantidad_800_elementos(){
	printf("\n-----------PRUEBA DE INSERTAR EN CANTIDAD-----------\n");
	int estado,contador_pruebas_pasadas=0;
	int pruebas_a_pasar=6;
	int enteros[MAXIMO],numero_unico=50000;
	bool resultado=false;
	cargar_enteros(enteros,MAXIMO);

	abb_t* arbol=arbol_crear(comparador_de_enteros,NULL);

	insertar_enteros(arbol,enteros,MAXIMO);

	assert(!arbol_vacio(arbol),"El arbol no esta vacio",contador_pruebas_pasadas);

	printf("\nInserto un numero que no esta en el arbol\n");
	estado=arbol_insertar(arbol,&numero_unico);
	assert(estado==EXITO,"Se inserto correctamente",contador_pruebas_pasadas);

	assert(*(int*)arbol_buscar(arbol,&numero_unico)==numero_unico,"Si busco el numero me lo devuelve",contador_pruebas_pasadas);
	estado=arbol_borrar(arbol,&numero_unico);
	assert(estado==EXITO,"Borra el numero del arbol",contador_pruebas_pasadas);
	assert(arbol_buscar(arbol,&numero_unico)==NULL,"Si lo busco no esta",contador_pruebas_pasadas);

	printf("\nBorro los 800 elementos insertados\n");
	borrar_varias_veces(arbol,MAXIMO,enteros);
	assert(arbol_vacio(arbol),"El arbol esta vacio",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	arbol_destruir(arbol);
	return resultado;
}

/* Inserta 3 elementos y luego borra 4. De esta forma, se verifica que devuelva NULL y error para cada caso.
 */
bool intentar_borrar_mas_elementos_de_los_que_hay(){
	printf("\n-----------PRUEBA DE BORRAR MAS DE LO GUARDADO-----------\n");
	int auxiliar,contador_pruebas_pasadas=0;
	int enteros[MAX],recorrido[MAX];
	int pruebas_a_pasar=7;
	cargar_enteros(enteros,MAX);
	bool resultado=false;
	
	abb_t* arbol=arbol_crear(comparador_de_enteros,NULL);

	insertar_enteros(arbol,enteros,MAX);
	assert(!arbol_vacio(arbol),"El arbol no esta vacio",contador_pruebas_pasadas);

	printf("\nBorro todos los elementos y pruebo ahora.\n");
	borrar_varias_veces(arbol,MAX,enteros);

	assert(arbol_vacio(arbol),"El arbol esta vacio",contador_pruebas_pasadas);

	assert(arbol_raiz(arbol)==NULL,"La raiz es NULL",contador_pruebas_pasadas);

	auxiliar=arbol_recorrido_postorden(arbol,(void**)recorrido,MAX);
	assert(auxiliar==0,"El recorrido postorden devuelve que hay 0 elementos",contador_pruebas_pasadas);

	assert(arbol_buscar(arbol,&enteros[3])==NULL,"No encuentra un elemento borrado",contador_pruebas_pasadas);

	assert(arbol_borrar(arbol,&enteros[0])==ERROR,"No puede borrar un elemento que no esta",contador_pruebas_pasadas);

	assert(arbol_borrar(arbol,&enteros[2])==ERROR,"No puede borrar otro elemento que no esta",contador_pruebas_pasadas);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	arbol_destruir(arbol);
	return resultado;
}


/* Se prueba el correcto funcionamiento del iterador
 */
bool realizar_acciones_con_iterador(){
	printf("\n-----------PRUEBAS CON EL ITERADOR-----------\n");
	int contador_pruebas_pasadas=0,pruebas_a_pasar=3;
	int contador=0;
	bool resultado=false;

	char mensaje[MAX]="ARBOL";
	int enteros_bajos[MAX]={1,1,1,1,1,2,2,2,2,2};
	int enteros_altos[MAX]={10,50,22,66,33,9,10,30,40,32};

	abb_t* arbol=arbol_crear(comparador_de_letras,NULL);
	insertar_caracteres(arbol,mensaje,5);
	printf("Mando una funcion para que imprima un mensaje(ARBOL):");
	abb_con_cada_elemento(arbol,ABB_RECORRER_PREORDEN,imprimir_mensaje,&contador);
	printf("\n");
	assert(contador==5,"El contador mandado tiene la cantidad esperada",contador_pruebas_pasadas);

	arbol_destruir(arbol);

	arbol=arbol_crear(comparador_de_enteros,NULL);
	insertar_enteros(arbol,enteros_bajos,MAX);

	printf("\nPruebo que se respete el limite en la funcion\n");
	contador=1;
	abb_con_cada_elemento(arbol,ABB_RECORRER_POSTORDEN,multiplicar_hasta_pasar_limite,&contador);
	assert(contador<100,"Se acumulo menos que el limite",contador_pruebas_pasadas);
	borrar_varias_veces(arbol,MAX,enteros_bajos);

	contador=1;
	insertar_enteros(arbol,enteros_altos,MAX);
	abb_con_cada_elemento(arbol,ABB_RECORRER_INORDEN,multiplicar_hasta_pasar_limite,&contador);
	assert(contador>=100,"Se llego a pasar el limite",contador_pruebas_pasadas);
	
	arbol_destruir(arbol);

	verificar_si_paso_las_pruebas(&resultado,contador_pruebas_pasadas,pruebas_a_pasar);

	return resultado;
}


/* Realiza las pruebas
 */
void realizar_pruebas(){
	int pruebas_pasadas=0;
	bool estado;

	printf("\n////--------------------PRUEBAS DE CASOS NULOS--------------------////\n");

	estado=intentar_realizar_acciones_con_arbol_nulo();
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

	estado=realizar_acciones_con_iterador();
	mostrar_resultado(estado,&pruebas_pasadas);

	printf("\n////-------------------------------------------------------------////\n");

	printf("			Paso %i pruebas generales de 6\n",pruebas_pasadas);
}

/* Realiza las pruebas
 */
int main(){
	printf("--------------------------PRUEBAS DE ABB------------------------\n");
	realizar_pruebas();
	printf("----------------------------------------------------------------\n");
	return 0;
}