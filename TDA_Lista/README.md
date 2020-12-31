# TDA Lista
* Esta implementación de una lista está hecha con nodos enlazados. En ella, se pueden guardar diferentes tipos de datos. 
* Su estructura incluye una referencia al primer y último nodo. De esta forma, se obtienen mejores tiempos de ejecución O(1) para los casos de borrar e insertar.
* Viene con un iterador externo y otro interno, de forma tal de mantener tiempos aceptables de ejecución.

## COMPILACION:
* Para realizar la compilación se recomienda utilizar el makefile.

* La línea completa seria (junta todo en el mismo .o):
Separar antes el mini_pruebas.c, asi no hay conflictos, ya que habria 2 main
gcc *.c -o pruebas_lista -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0

### MAKEFILE:
* ```make lista```
	Compila solamente el lista.c y lista.h, juntandolos en lista.o, este utiliza todos los flags ya puestos en COMPILACION.

* ```make pruebas```
	Agarra el lista.o, crea el mi_assert.o y compila tambien las pruebas. De este modo queda el archivo pruebas_lista

* ```make minipruebas```
	Agarra el lista.o y compila las mini pruebas que entrego la catedra para probar un caso feliz.

* ```make all```
	Realiza make pruebas

* ```make valgrind```
	Ejecuta las pruebas

* ```make valgrind_minipruebas```
	Ejecuta las mini pruebas provistas por la catedra

* ```make clean```
	Limpia el directorio, sacando los -o y pruebas_lista

## EJECUCION:
* Se pueden ejecutar las pruebas mediante las siguientes opciones:
	1) ./pruebas_lista (No mostraría información detallada sobre el uso de la memoria)
	2) valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebas_lista
	3) make valgrind

## PRUEBAS:
Pruebas realizadas
* Se prueba que no se puedan realizar acciones cuando la lista no esta creada
* Se guarda NULL en la lista y se verifica que realice las diferentes acciones
* Se guardan diferentes tipos de datos, se cambia el orden, y se ve son devueltos como se esperan
* Se insertan 800 elementos, y se verifica su correcto uso de memoria al ir disminuyendolos
* Se prueba borrar mas elementos que los insertados
* Se verifica que no se puedan realizar acciones si el iterador externo no está creado
* Se utiliza el iterador interno, con este se evalua que se puedan guardar y liberar elementos en el heap
* Se evalua el funcionamiento del iterador externo.

**Como crear una nueva prueba**  
Para agregar una nueva prueba, dirigirse a la función realizar_pruebas(){...}.

Agregar en la categoría que considere conveniente la función que pertenece a su prueba.

Esta función tiene que devolver un bool (true significa que paso la prueba)
Este estado es enviado a la función mostrar_resultado(){...} que dira si se paso la prueba.

Se puede utilizar la función assert() para verificar si la prueba es exitosa, para eso, esta necesita una comparación booleana,
y un mensaje a ser mostrado. Este mensaje aparecerá con un OK o ERROR dependiendo el caso. Si fallo, también se mostrara el archivo y la línea
del código.

![lista](https://www.cs.usfca.edu/~srollins/courses/cs112-f07/web/notes/linkedlists/ll2.gif)