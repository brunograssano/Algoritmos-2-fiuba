#include "cuervo_tres_ojos.h"
const char PASADO ='P', FUTURO ='F';
const int ERROR = -1,EXITO=0;

/*
 * Recibe el nombre del cuervo a invocar.
 * Creará la estructura cuervo_tres_ojos, reservando la memoria necesaria.
 * Devolverá la estructura con los topes de las visiones inicializados en 0.
 * En caso de no poder invocar al cuervo, devolverá NULL.
 */
cuervo_tres_ojos_t* invocar_cuervo(char* nombre){

    cuervo_tres_ojos_t* cuervo_viejo = malloc(sizeof(cuervo_tres_ojos_t));

    if(cuervo_viejo==NULL){
        return NULL;
    }
    
    strcpy(cuervo_viejo->nombre,nombre);
    cuervo_viejo->visiones_del_pasado=NULL;
    cuervo_viejo->visiones_del_futuro=NULL;
    cuervo_viejo->cantidad_visiones_pasado=0;
    cuervo_viejo->cantidad_visiones_futuro=0;

    return cuervo_viejo;
}

/*
 * Recibe el nombre del aprendiz a invocar.
 * Creará la estructura cuervo_aprendiz, reservando la memoria necesaria.
 * Devolverá la estructura con el tope de las visiones inicializado en 0.
 * En caso de no poder invocar al aprendiz, devolverá NULL.
 */
cuervo_aprendiz_t* invocar_aprendiz(char* nombre){
    
    cuervo_aprendiz_t* cuervo_nuevo = malloc(sizeof(cuervo_aprendiz_t));

    if(cuervo_nuevo==NULL){
        return NULL;
    }
    
    strcpy(cuervo_nuevo->nombre,nombre);
    cuervo_nuevo->visiones_adquiridas=NULL;
    cuervo_nuevo->cantidad_visiones=0;

    return cuervo_nuevo;
}

/* Se hara el realloc en el auxiliar, en caso de que haya un error devuelve que fallo.
 * Caso contrario, queda agregada la vision y se hace el intercambio en los punteros
 */
int agregar_vision_en_cuervo(vision_t** visiones,vision_t vision,int* cantidad){
    (*cantidad)++;
    vision_t* visiones_auxiliares=realloc(*visiones,(long unsigned int)(*cantidad) * sizeof(vision_t));
       
    if(visiones_auxiliares==NULL){
        (*cantidad)--;
        return ERROR;
    }

    visiones_auxiliares[(*cantidad)-1]=vision;
    (*visiones)=visiones_auxiliares;

    return EXITO;
}

/*
 * Agrega una vision al vector de visiones correspondiente.
 * Reservando la memoria necesaria para ella.
 * Devolverá 0 si pudo agregarla o -1 si no pudo.
 */
int agregar_vision(cuervo_tres_ojos_t* cuervo, vision_t vision){
    if(vision.epoca==PASADO){ 
        return agregar_vision_en_cuervo(&(cuervo->visiones_del_pasado),vision,&(cuervo->cantidad_visiones_pasado));
    }
    else if(vision.epoca==FUTURO){
        return agregar_vision_en_cuervo(&(cuervo->visiones_del_futuro),vision,&(cuervo->cantidad_visiones_futuro));
    }
    else{
        return ERROR;
    }
}

/* precondiciones: Ambas visiones tienen en cada campo algo ya puesto, de forma tal de que no compare basura con basura.
 * postcondiciones: Devuelve si son exactamente las mismas visiones.
 */
bool son_iguales(vision_t vision,vision_t vision_adquirida){
    return strcmp(vision.protagonista,vision_adquirida.protagonista)==0 && strcmp(vision.casa_protagonista,vision_adquirida.casa_protagonista)==0 &&
        strcmp(vision.descripcion,vision_adquirida.descripcion)==0 && vision.epoca==vision_adquirida.epoca;
}

/* precondiciones: Recibe una vision valida que es la que se quiere agregar, y el puntero a todas las visiones ya cargadas, junto con el total.
 *                 Este total no puede ser negativo.
 * postcondiciones: Al final de recorrer todas las visiones indicara si ya fue cargada la vision
 */
bool es_repetida(vision_t vision,vision_t* visiones_adquiridas,int cantidad_visiones){
    bool es_repetida=false;
    int i=0;
    while(i<cantidad_visiones && !es_repetida){
        if(son_iguales(vision,visiones_adquiridas[i])){
           es_repetida=true;
        }
        i++;
    }
    return es_repetida;
}

/*
 * Transmitirá al aprendiz las visiones del pasado y del futuro del cuervo que sean 
 * transmisibles de acuerdo a la función recibida como parámetro.
 * En caso de que la visión a transmitir ya sea conocida por el aprendiz (repetida), 
 * no se agrega a las visiones del mismo.
 * Devolverá 0 si se transmitieron con eso, -1 en caso contrario
 */
int transmitir_visiones(cuervo_tres_ojos_t* cuervo, cuervo_aprendiz_t* aprendiz, bool (*es_transmisible)(vision_t)){
    int i=0;
    int estado=EXITO;
    while(i<cuervo->cantidad_visiones_pasado && estado!=ERROR){
        if((*es_transmisible)(cuervo->visiones_del_pasado[i]) && !es_repetida(cuervo->visiones_del_pasado[i],aprendiz->visiones_adquiridas,aprendiz->cantidad_visiones)){
            estado=agregar_vision_en_cuervo(&(aprendiz->visiones_adquiridas),cuervo->visiones_del_pasado[i],&(aprendiz->cantidad_visiones));
        }
        i++;
    }

    if(estado==ERROR){
        return ERROR;
    }

    i=0;
    while(i<cuervo->cantidad_visiones_futuro && estado!=ERROR){
        if((*es_transmisible)(cuervo->visiones_del_futuro[i]) && !es_repetida(cuervo->visiones_del_futuro[i],aprendiz->visiones_adquiridas,aprendiz->cantidad_visiones)){     
            estado=agregar_vision_en_cuervo(&(aprendiz->visiones_adquiridas),cuervo->visiones_del_futuro[i],&(aprendiz->cantidad_visiones));
        }
        i++;
    }

    return estado;
}


/*
 * Mostrará por pantalla las visiones adquiridas por el aprendiz.
 * Una visión se listará sólo si la función recibida como parámetro lo permite.
 */
void listar_visiones_transmitidas(cuervo_aprendiz_t aprendiz, bool (*es_listable)(vision_t)){
    bool hay_vision=false;
    for(int i=0;i<aprendiz.cantidad_visiones;i++){
        if((*es_listable)(aprendiz.visiones_adquiridas[i])){
            printf("---->Vision sobre %s:%s \n",aprendiz.visiones_adquiridas[i].protagonista,aprendiz.visiones_adquiridas[i].descripcion);
            hay_vision=true;
        }
    }
    if(!hay_vision){
        printf("Ninguna vision cumple con lo pedido.\n");
    }
}

/*
 * Destruirá la estructura del cuervo, liberando la memoria reservada para él y sus visiones.
 * Devolverá  si pudo liberar lamemoria o -1 si no pudo.
 */
int destruir_cuervo(cuervo_tres_ojos_t* cuervo){
    if(cuervo==NULL){
        return ERROR;
    }
    if(cuervo->cantidad_visiones_pasado>0 && cuervo->visiones_del_pasado!=NULL){
        free(cuervo->visiones_del_pasado);
    }
    if(cuervo->cantidad_visiones_futuro>0 && cuervo->visiones_del_futuro!=NULL){
        free(cuervo->visiones_del_futuro);
    }
    free(cuervo);

    return EXITO;
}

/*
 * Destruirá la estructura del aprendiz, liberando la memoria reservada para él y sus visiones.
 * Devolverá  si pudo liberar lamemoria o -1 si no pudo.
 */
int destruir_aprendiz(cuervo_aprendiz_t* aprendiz){
    if(aprendiz==NULL){
        return ERROR;
    }
    if(aprendiz->cantidad_visiones>0 && aprendiz->visiones_adquiridas!=NULL){
        free(aprendiz->visiones_adquiridas);
    }
    free(aprendiz);
    return EXITO;
}