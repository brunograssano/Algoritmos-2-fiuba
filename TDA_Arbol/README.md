# TDA Arbol
Este TDA es un árbol de búsqueda binario, en el que se pueden guardar diferentes tipos de elementos, incluyendo elementos en memoria dinámica.
 
El árbol requiere para su correcto funcionamiento que se le pase un destructor de elementos y un comparador de estos, ya que sin el no podría saber donde guardar cada uno.

Si se insertan correctamente los elementos en el árbol, su complejidad será O(logn). En caso de que se inserten o eliminen elementos que causen que se deforme, su complejidad tiende a O(n). 

## COMPILACION:
* Para realizar la compilación se recomienda utilizar el makefile.

* La línea completa seria (junta todo en el mismo .o):
Separar antes el mini_pruebas.c, así no hay conflictos, ya que habría 2 main
gcc *.c -o pruebas_arbol -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0

### MAKEFILE:
* ```make lista```
	Compila solamente el arbol.c y arbol.h, juntandolos en arbol.o, este utiliza todos los flags ya puestos en COMPILACION.

* ```make pruebas```
	Agarra el arbol.o, crea el mi_assert.o y compila también las pruebas. De este modo queda el archivo pruebas_arbol

* ```make minipruebas```
	Agarra el arbol.o y compila las mini pruebas que entrego la cátedra para probar un caso feliz.

* ```make all```
	Realiza make pruebas

* ```make valgrind```
	Ejecuta las pruebas

* ```make valgrind_minipruebas```
	Ejecuta las mini pruebas provistas por la cátedra

* ```make clean```
	Limpia el directorio, sacando los -o y pruebas_arbol

## EJECUCION:
* Se pueden ejecutar las pruebas mediante las siguientes opciones:
	1) ./pruebas_arbol (No mostraría información detallada sobre el uso de la memoria)
	2) valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas_arbol
	3) make valgrind

## PRUEBAS:
Se incluye para facilitar la visualización del árbol una función que se llama mostrar_arbol_entero(). Esta función imprime un árbol de enteros de forma acostada. Para usarle simplemente agregarla donde se quiera ver el árbol actual.
Pruebas realizadas
* Se verifica que no se puedan realizar acciones cuando el árbol no está creado.
* Se prueba que se inserte un elemento NULL. No se realizan acciones de búsqueda y borrado con el ya que no tiene comparador.
* Se insertan diferentes tipos de elementos y se prueba que el árbol realice diferentes acciones.
* Se insertan 800 elementos en cantidad y se ve que se haga un buen manejo de memoria.
* Se intentan borrar más elementos de los que hay guardados en el árbol.
* Se verifica el funcionamiento del iterador interno, a este se le pasan funciones probando diferentes situaciones.
* Se agregan unas mini pruebas en el archivo aparte que prueban un 'caso feliz' en el que se verifica que se guarden elementos en el heap.	

**Como crear una nueva prueba**
Para agregar una nueva prueba, dirigirse a la función realizar_pruebas(){...}.

Agregar en la categoría que considere conveniente la función que pertenece a su prueba.

Esta función tiene que devolver un bool (true significa que paso la prueba)
Este estado es enviado a la función mostrar_resultado(){...} que dira si se paso la prueba.

Se puede utilizar la función assert() para verificar si la prueba es exitosa, para eso, esta necesita una comparación booleana,
y un mensaje a ser mostrado. Este mensaje aparecerá con un OK o ERROR dependiendo el caso. Si fallo, también se mostrara el archivo y la línea
del código.
Además se incluye un assert_vectores(), que recibe 2 vectores e indica si son iguales.

![arbol](https://www.tutorialspoint.com/data_structures_algorithms/images/binary_tree.jpg "arbol")
