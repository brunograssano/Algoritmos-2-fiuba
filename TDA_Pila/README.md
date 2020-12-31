# TDA PILA
* Esta implementación de una pila es con un vector dinámico, empieza con una capacidad mínima para cinco elementos.

* Una vez alcanzado su tope, se duplica su capacidad.

* En caso de que al desapilar su capacidad sea menor a la mitad del tamaño alcanzado, se liberara esa parte de la memoria que ya no está en uso.

## COMPILACION
* Para realizar la compilación se recomienda utilizar el makefile.

* La línea completa seria (junta todo en el mismo .o):
Separar antes el mini_pruebas.c, asi no hay conflictos, ya que habria 2 main
gcc *.c -o pila_pruebas -g -std=c99 -Wall -Wconversion -Wtype-limits-pedantic -Werror -o0

### MAKEFILE:
* ```make pila```
	Compila solamente el pila.c y pila.h, juntandolos en pila.o, este utiliza todos los flags ya puestos en COMPILACION.

* ```make pruebas```
	Agarra el pila.o y compila tambien las pruebas. De este modo queda el archivo pruebas_pila

* ```make all```
	Realiza make pruebas

* ```make valgrind```
	Ejecuta las pruebas

* ```make clean```
	Limpia el directorio, sacando los -o y pruebas_pila

## EJECUCION:
* Se pueden ejecutar las pruebas mediante las siguientes opciones:
	1) ./pruebas_pila (No mostraria informacion detallada sobre el uso de la memoria)
	2) valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas_pila
	3) make valgrind

## PRUEBAS:
* Una prueba es la forma más rápida generalmente de poder ver si lo implementado cumple con lo esperado, en este caso, se verifican que se cumplan los casos bordes y casos de uso normales.
	
Pruebas realizadas  
- Se verifica que la pila no realice ninguna acción cuando la pila es nula, este podria ser el caso de que falle la creacion o directamente fuera creada asi.
- Se prueba que si el vector de elementos estuviese nulo, es decir no exista, la pila no realice ninguna accion. Esto puede pasar si fuese creado por el usuario.
- Se prueba si se puede apilar y desapilar el elemento NULL
- Caso de uso normal, se hacen un par de apilaciones y se desapilan otros, escribiendo un mensaje
- Caso limite, antes de volver a redimensionar, sacando y guardando elementos.
- Se prueba la pila en cantidad, de forma tal de ver el uso correcto de la memoria.
- Se prueba que no se puedan sacar más elementos que los que hay.
	
**Como crear una nueva prueba**  
Para crear una nueva prueba, hay que agregarla arriba de la función realizar_pruebas(). Esta tiene que tener el siguiente formato:
```
ej:
  bool nombre_de_la_prueba(){...}
  ```
Adentro de ella se debe de crear y destruir la pila y debe de enviar mediante un booleano si la paso(true) o no(false).
Una vez hecha, se debe de agregar la prueba en la categoría que corresponda. El booleano es recibido por la variable estado, que debera ser
enviada, junto con un nombre identificatorio de la prueba y el contador pruebas pasadas(pasaje mediante referencia), a la función mostrar_resultado
```
ej:
  estado=nombre_de_la_prueba();
  mostrar_resultado(estado,NOMBRE_IDENTIFICATORIO,&pruebas_pasadas);
```
Recordar cambiar abajo de todo en la función la cantidad total de pruebas, ya que esta puesta adentro de un printf().

![pila](https://upload.wikimedia.org/wikipedia/commons/thumb/b/b4/Lifo_stack.png/350px-Lifo_stack.png)


