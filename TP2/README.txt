TP2
*El trabajo consistio en realizar una simulacion de Game of Thrones.
 Se simularan una cantidad de anios ingresada por el usuario, y luego de transcurridos, se le mostrara por pantalla la casa que se ha quedado con el trono.
*Se pedian las opciones de:
	Simular
	Agregar una casa
	Listar casas por miembros
	Mostrar casas extintas
	Finalizar el programa

*Se agrego como extra la opcion (M) para mostrar los miembros de una determinada casa.

*Para compilar el trabajo se puede utilizar:
	make juego
		Esta opcion agarra todos los archivos y los compila, dejando el programa listo para ejecutarse.

*Para ejecutarlo, esto se puede hacer con:
	make valgrind
		Correra el trabajo y mostrara el uso de la memoria

*El juego viene programado para abrir el archivo con el nombre "casas_juego.txt", este es un archivo de texto al que se le pueden escribir a mano mas casas e integrantes.
 Si se quiere que se cargue otro archivo, habra que cambiarle el nombre al especificado, o cambiarlo en el codigo.

*El juego necesita para funcionar correctamente del archivo "nombres_nacimientos.txt". En este archivo se encuentran las diferentes opciones para cuando nace una persona
 Si se quieren agregar mas personas, se le deben agregar el nombre y la edad.

*Se incluye una carpeta con varios .txt para probar diferentes situaciones en el juego, ya sea, agregar casas o probar casos puntuales.

*Dependiendo de la cantidad de anios que se simulen y de los factores(muerte/nacimiento), la cantidad de uso de memoria puede aumentar considerablemente.
 Esto sucede debido a la cantidad de nacimientos que pueden llegar a tener algunas casas.
