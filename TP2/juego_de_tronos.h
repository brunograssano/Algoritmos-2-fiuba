#include "abb.h"
#include "cola.h"
#include "lista.h"

typedef struct juego{
  int cantidad_casas;
  abb_t* casas;
  cola_t* casas_extintas;
  lista_t* nombres_nacimientos;
}juego_t;

/* Se encarga de crear el juego y dejarlo en un estado valido.
 * Leera todas las casas y las cargara a un ABB.
 * En caso de que ocurra un error durante su creacion liberara la memoria tomada y devolvera
 * mediante un entero -1, caso contrario sera 0.
 */
int inicializar_juego(juego_t* juego);

/* Se encargara de ejecutar la simulacion del juego.
 * Para ello, se le preguntara al usuario una cantidad de anios a transcurrir.
 * Pasados los anios mostrara por pantalla la casa que controla el trono de hierro.
 */
void iniciar_simulacion(juego_t* juego);


/* Agregara una casa al arbol. Esta va a surgir de un nombre de un archivo que da el usuario
 * Si la casa a agregar ya existe, se le suman los integrantes a la casa ya creada.
 */
void agregar_casa_al_arbol(juego_t* juego);

/* Listara las casas por cantidad de integrantes en orden descendente.
 */
void listar_casas_en_orden(juego_t juego);

/* Mostrara las casas que fueron extintas en el orden en que fueron desapareciendo.
 * Una vez mostradas son eliminadas las casas, no se mantienen.
 */
void mostrar_casas_extintas(juego_t juego);

/* Mostrara los miembros de una casa ingresada por el usuario.
 */
void mostrar_miembros_casa(juego_t juego);

/* Destruira la memoria que haya sido reservada por el juego por alguna de las estructuras creadas.
 */
void destruir_juego(juego_t juego);
