![gameofthroneslogo](https://1000marcas.net/wp-content/uploads/2020/11/Game-of-Thrones-logo.png)
# TP2
* El trabajo consistió en realizar una simulación de Game of Thrones.
 Se simularan una cantidad de años ingresada por el usuario, y luego de transcurridos, se le mostrara por pantalla la casa que se ha quedado con el trono.
* Se pedían las opciones de:  
	- Simular (S)
	- Agregar una casa (A)
	- Listar casas por miembros (L)
	- Mostrar casas extintas (E)
	- Finalizar el programa (Q)

* Se agrego como extra la opción (M) para mostrar los miembros de una determinada casa.

### Compilación y ejecución

* Para compilar el trabajo se puede utilizar:  
	- ```make juego```
		Esta opción agarra todos los archivos y los compila, dejando el programa listo para ejecutarse.

* Para ejecutarlo, esto se puede hacer con:
	- ```make valgrind```
		Correra el trabajo y mostrara el uso de la memoria

### Implementación

* El juego viene programado para abrir el archivo con el nombre *"casas_juego.txt"*, este es un archivo de texto al que se le pueden escribir a mano más casas e integrantes.
 Si se quiere que se cargue otro archivo, habrá que cambiarle el nombre al especificado, o cambiarlo en el código.

* El juego necesita para funcionar correctamente del archivo *"nombres_nacimientos.txt"*. En este archivo se encuentran las diferentes opciones para cuando nace una persona
 Si se quieren agregar más personas, se le deben agregar el nombre y la edad.

* Se incluye una carpeta con varios .txt para probar diferentes situaciones en el juego, ya sea, agregar casas o probar casos puntuales.

* Dependiendo de la cantidad de años que se simulen y de los factores(muerte/nacimiento), la cantidad de uso de memoria puede aumentar considerablemente.
 Esto sucede debido a la cantidad de nacimientos que pueden llegar a tener algunas casas.

* El programa esta hecho utilizando los TDAs realizados durante la cursada. Se tiene un árbol que maneja a todas las casas, cuyo nodo tiene una lista que viene a guardar a los integrantes de cada casa.
Si una casa se extingue, esta se agrega a una cola de casas extintas.

El enunciado se puede encontrar [aqui](https://github.com/brunograssano/Algoritmos-2-fiuba/blob/master/TP2/TP2-2C2019.pdf "Enunciado en github")