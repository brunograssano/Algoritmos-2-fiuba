
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "cuervo_tres_ojos.h"
#define FORMATO_TEXTO "%[^;];%[^;];%[^;];%c\n"
#define LECTURA "r"
#define PASADO 'P'
#define FUTURO 'F'
#define ERROR -1 
#define EXITO 0
#define SALIR 0
#define ID_PASADO 1
#define ID_FUTURO 2
#define JON_SNOW 3 
#define TARGARYEN 4
#define STARK 5
#define LANNISTER 6
#define LARGO 7
const char NOMBRE_ARCHIVO[]="visiones.txt";
const int MINIMO_LARGO=30;


/* Llamara a la funcion que se encarga de crear el cuervo de tres ojos despues de que se le ingrese un nombre.
 */
cuervo_tres_ojos_t* crear_cuervo_viejo(){
	//char nombre_cuervo[MAX_NOMBRE];
	printf(" Ingrese el nombre del cuervo de tres ojos. \n");
	//scanf(" %[^\n]", nombre_cuervo);
	return invocar_cuervo("Brynden");
}

/* Llamara a la funcion que se encarga de crear al aprendiz despues de que se le ingrese un nombre.
 */
cuervo_aprendiz_t* crear_cuervo_nuevo(){
	//char nombre_cuervo[MAX_NOMBRE];
	printf(" Ingrese el nombre del cuervo aprendiz. \n");
	//scanf(" %[^\n]", nombre_cuervo);
	return invocar_aprendiz("Bran Stark");
}

/* precondiciones: El archivo es de texto y se encuentra abierto.
 * postcondiciones: Lee el contenido del archivo y devuelve la cantidad que leyo.
 */
int leer_vision(FILE* file_visiones,vision_t* vision){
	return fscanf(file_visiones,FORMATO_TEXTO,vision->protagonista,vision->casa_protagonista,vision->descripcion,&(vision->epoca));
}

/* Se fija si la vision pertenece al pasado.
 */
bool es_pasado(vision_t vision){
	return vision.epoca==PASADO;
}

/* Se fija si la vision pertenece al futuro.
 */
bool es_futuro(vision_t vision){
	return vision.epoca==FUTURO;
}

/* Se fija si la vision pertenece a Jon Snow.
 */
bool es_jon_snow(vision_t vision){
	return strcmp(vision.protagonista,"Jon Snow")==0;
}

/* Se fija si la vision pertenece a la casa Targaryen.
 */
bool es_targaryen(vision_t vision){
	return strcmp(vision.casa_protagonista,"Targaryen")==0;
}

/* Se fija si la vision pertenece a la casa Stark.
 */
bool es_stark(vision_t vision){
	return strcmp(vision.casa_protagonista,"Stark")==0;
}

/* Se fija si la vision pertenece a la casa Lannister.
 */
bool es_lannister(vision_t vision){
	return strcmp(vision.casa_protagonista,"Lannister")==0;
}

/* Se fija si la vision tiene una descripcion larga.
 */
bool es_larga(vision_t vision){
	return strlen(vision.descripcion)>=MINIMO_LARGO;
}

/* Indica el resultado de la liberacion de memoria, en caso de que se halla mandado un puntero a NULL a destruir cuervo.
 */
void mostrar_estado(int estado){
	if(estado==ERROR){
		printf("Hubo un error.\n");
	}
	else{
		printf("Se realizo exitosamente.\n");
	}
}

/* Informa al usuario sobre las opciones transmisibles/listables y le pregunta cual quiere hacer
 */
void preguntar_transmisibles_listables(int* respuesta,char* situacion){
	printf("\n\nLas opciones son las siguientes (Ingrese el numero de la que quiere):\n");
	printf(" 0 - Salir \n 1 - %s las del pasado \n 2 - %s las del futuro \n 3 - %s las de Jon Snow\n",situacion,situacion,situacion);
	printf(" 4 - %s las de la casa Targaryen \n 5 - %s las de la casa Stark \n 6 - %s las de la casa Lannister \n 7 - %s las mas largas\n",situacion,situacion,situacion,situacion);
	scanf("%i",respuesta);
	

}

/* Transmitir visiones del cuervo al aprendiz
 * Puede ser invocada varias veces con diferentes funciones , 
 * esto hará que el cuervo aprendiz tenga distintas visiones de distintos rubros */
void pasar_visiones(cuervo_tres_ojos_t* cuervo_viejo,cuervo_aprendiz_t* cuervo_nuevo,int* estado){
	int transmisible=-1;
	while(transmisible!=SALIR && (*estado)!=ERROR){
		preguntar_transmisibles_listables(&transmisible,"Transmitir");
		switch(transmisible){
			case SALIR: 
				break;
			case ID_PASADO:
				(*estado)=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_pasado);
				break;
			case ID_FUTURO:
				(*estado)=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_futuro);
				break;
			case JON_SNOW:
				(*estado)=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_jon_snow);
				break;
			case TARGARYEN:
				(*estado)=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_targaryen);
				break;
			case STARK:
				(*estado)=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_stark);
				break;
			case LANNISTER:
				(*estado)=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_lannister);
				break;
			case LARGO:
				(*estado)=transmitir_visiones(cuervo_viejo,cuervo_nuevo,es_larga);
				break;
			default:
				printf("No es una opcion.\n");
				break;
		}
		if(transmisible!=SALIR){
			mostrar_estado(*estado);
		}
	}
}

/* Mostrar las visiones adquiridas por el aprendiz 
 */
void listar_visiones(cuervo_aprendiz_t* cuervo_nuevo){
	int listables=-1;
	while(listables!=SALIR){
		preguntar_transmisibles_listables(&listables,"Listar");
		switch(listables){
			case SALIR: 
				break;
			case ID_PASADO:
				listar_visiones_transmitidas(*cuervo_nuevo,es_pasado);
				break;
			case ID_FUTURO:
				listar_visiones_transmitidas(*cuervo_nuevo,es_futuro);
				break;
			case JON_SNOW:
				listar_visiones_transmitidas(*cuervo_nuevo,es_jon_snow);
				break;
			case TARGARYEN:
				listar_visiones_transmitidas(*cuervo_nuevo,es_targaryen);
				break;
			case STARK:
				listar_visiones_transmitidas(*cuervo_nuevo,es_stark);
				break;
			case LANNISTER:
				listar_visiones_transmitidas(*cuervo_nuevo,es_lannister);
				break;
			case LARGO:
				listar_visiones_transmitidas(*cuervo_nuevo,es_larga);
				break;
			default:
				printf("No es una opcion.\n");
				break;
		}

	}
}

/*  Carga las visiones en el cuervo de tres ojos. El archivo tiene que estar abierto.
 *  En caso de error devolvera -1.
 */
int carga_de_visiones(FILE* file_visiones,cuervo_tres_ojos_t* cuervo_viejo){
	vision_t vision;
	int estado = EXITO;
	int leidos = leer_vision(file_visiones,&vision);

	while(0<leidos && estado == EXITO){
		estado = agregar_vision(cuervo_viejo,vision);
		leidos = leer_vision(file_visiones,&vision);
	}
	return estado;
}

/*  Llama a las funciones que se encargan de liberar la memoria correctamente. Despues le dice el estado al usuario.
 */
void liberar_memoria(cuervo_tres_ojos_t* cuervo_viejo,cuervo_aprendiz_t* cuervo_nuevo){
	int estado_mem=destruir_cuervo(cuervo_viejo);
	mostrar_estado(estado_mem);
	estado_mem=destruir_aprendiz(cuervo_nuevo);
	mostrar_estado(estado_mem);
}

/* Ejecutara el programa correctamente en caso de que haya memoria suficiente y este el archivo de forma correcta, caso contrario devolvera que fallo.
 */
int main(){

	FILE* file_visiones = fopen(NOMBRE_ARCHIVO,LECTURA);
	if(file_visiones==NULL){
		printf("Fallo al intentar abrir el archivo. \n");
		return ERROR;
	}

	cuervo_tres_ojos_t* cuervo_viejo = crear_cuervo_viejo(invocar_cuervo);
	if(cuervo_viejo==NULL){
		printf("Fallo creando al cuervo.\n");
		fclose(file_visiones);
		return ERROR;
	}

	cuervo_aprendiz_t* cuervo_nuevo = crear_cuervo_nuevo(invocar_aprendiz);
	if(cuervo_nuevo==NULL){
		printf("Fallo creando al cuervo aprendiz.\n");
		fclose(file_visiones);
		free(cuervo_viejo);
		return ERROR;
	}


	int estado_carga=carga_de_visiones(file_visiones,cuervo_viejo);
	fclose(file_visiones);
	
	if(estado_carga==ERROR){
		printf("Hubo un error en la carga de las visiones\n");
		liberar_memoria(cuervo_viejo,cuervo_nuevo);
		return ERROR;
	}

	pasar_visiones(cuervo_viejo,cuervo_nuevo,&estado_carga);

	if(estado_carga==ERROR){
		printf("Hubo un error en el pase de las visiones\n");
		liberar_memoria(cuervo_viejo,cuervo_nuevo);
		return ERROR;
	}
	
	system("clear");

	listar_visiones(cuervo_nuevo);
	liberar_memoria(cuervo_viejo,cuervo_nuevo);

	return 0;
}