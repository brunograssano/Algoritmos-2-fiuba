# TDA Cola
* Esta implementación de una cola está hecha con nodos enlazados. En ella, se pueden guardar diferentes datos. 

* En caso de que se guarde algo que está en la memoria dinámica, el usuario debe liberar su memoria antes, ya que la cola no lo realizaría.

## COMPILACION:
* Para realizar la compilación se recomienda utilizar el makefile.

* La línea completa seria (junta todo en el mismo .o):
Separar antes el mini_pruebas.c, asi no hay conflictos, ya que habria 2 main
gcc *.c -o pruebas_cola -g -std=c99 -Wall -Wconversion -Wtype-limits-pedantic -Werror -o0

###MAKEFILE:
* ```make cola```
	Compila solamente el cola.c y cola.h, juntandolos en cola.o, este utiliza todos los flags ya puestos en COMPILACION.

* ```make pruebas```
	Agarra el cola.o y compila también las pruebas. De este modo queda el archivo pruebas_cola

* ```make minipruebas```
	Agarra el cola.o y compila las mini pruebas que entrego la cátedra para probar un caso feliz.

* ```make all```
	Realiza make pruebas

* ```make valgrind```
	Ejecuta las pruebas

* ```make valgrind_minipruebas```
	Ejecuta las mini pruebas provistas por la cátedra

* ```make clean```
	Limpia el directorio, sacando los -o y pruebas_cola

## EJECUCION:
* Se pueden ejecutar las pruebas mediante las siguientes opciones:
	1) ./pruebas_cola (No mostraría información detallada sobre el uso de la memoria)
	2) valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas_cola
	3) make valgrind

## PRUEBAS:
Una prueba es la forma más rápida generalmente de poder ver si lo implementado cumple con lo esperado, en este caso, se verifican que se cumplan los casos bordes y casos de uso normales.
Pruebas realizadas
* Se prueba que las acciones que se le pueden a hacer a la cola cuando no este creada, devuelvan lo esperado.
* Se encola un elemento NULL, y se realizan acciones con el.
* Se encolan diferentes tipos de dato, en este caso int,double y char.
* Se encolan 400 elementos, en esta prueba se verifica que los guarde y desencole correctamente.
* Se intenta desencolar más elementos de los que están guardados en la cola.

**Como crear una nueva prueba**  
Para agregar una nueva prueba, dirigirse a la función realizar_pruebas(){...}.

Agregar en la categoría que considere conveniente la función que pertenece a su prueba.

Esta función tiene que devolver un bool (true significa que paso la prueba)
Este estado es enviado a la función mostrar_resultado(){...} que dira si se paso la prueba.

![cola](https://upload.wikimedia.org/wikipedia/commons/thumb/5/52/Data_Queue.svg/1200px-Data_Queue.svg.png "cola")