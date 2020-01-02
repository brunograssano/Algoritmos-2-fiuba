TDA HASH
*Esta implementacion de Hash esta hecha de forma abierta utilizando un abb. La eleccion de utilizar un abb se debio a que este reduce considerablemente los casos de busqueda, y borrado de claves con sus elementos. Su tiempo de ejecucion sera O(logn) en contraste con la implementacion con lista O(n). 
*En el caso de la insercion habria un aumento en el tiempo de ejecucion, siendo devuelta O(logn) y el de la lista O(1) (mandando el elemento al final), pero este caso seria ampliamente compensado debido a lo mencionado al comienzo, ya que se realizan muchas mas busquedas que inserciones.
*Para el correcto funcionamiento del arbol, este incluye un comparador de claves, que se le pasa a cada arbol creado cuando se le indica la capacidad y un destructor de elementos.
*Esta implementacion de hash abierto tambien contiene un factor de carga mucho mayor en comparacion al resto. Una vez alcanzado el limite este, se realiza un rehash aumentando la capacidad que tiene buscando el siguiente numero primo, ya que ayuda a la dispersion. 
*Para el iterador del hash, se decidio usar una lista que guardaria todos los elementos ya insertados en los arboles. Esta lista, cuando es recorrida, actuaria como una pila enlazada, ya que estaria pidiendo y borrando siempre el primer elemento. 

COMPILACION:
*Para realizar la compilacion se recomienda utilizar el makefile.

*La linea completa seria (junta todo en el mismo .o):
Separar antes el mini_pruebas.c, asi no hay conflictos, ya que habria 2 main
gcc *.c -o pruebas_hash -g -std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -o0

MAKEFILE:
*make hash
	Compila el hash.c y hash.h, y los archivos de arbol y lista necesarios, a cada uno, lo deja con su respectivo .o, este utiliza todos los flags ya puestos en COMPILACION.

*make pruebas
	Agarra el hash.o, crea el mi_assert.o y compila tambien las pruebas. De este modo queda el archivo pruebashash

*make minipruebas
	Agarra el hash.o y compila las mini pruebas que entrego la catedra para probar un caso feliz.

*make all
	Realiza make pruebas

*make valgrind
	Ejecuta las pruebas

*make valgrind_mini
	Ejecuta las mini pruebas provistas por la catedra

*make clean
	Limpia el directorio, sacando los -o y pruebas_hash

EJECUCION:
*Se pueden ejecutar las pruebas mediante las siguientes opciones:
	1) ./pruebashash (No mostraria informacion detallada sobre el uso de la memoria)
	2) valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pruebashash
	3) make valgrind

PRUEBAS:
	Pruebas realizadas
		* Se prueba que no se puedan realizar acciones cuando el hash es NULL
		* Se inserta NULL y se ve que realice las acciones del hash
		* Se insertan distintos tipos de elementos con claves unicas (int,char,double,char*). Con ellos se hacen varias pruebas para evaluar el funcionamiento del hash
		* Se insertan 800 elementos en el hash y se ve que funcione  correctamente
		* Se intentan borrar mas elementos de los guardados
		* Se verifica que no se puedan realizar acciones cuando el iterador del hash es NULL
		* Se prueban las acciones del iterador del hash
		* Se agrega una prueba de la catedra de caso "feliz" que evalua el hash guardando elementos en el heap
	Como crear una nueva prueba
		Para agregar una nueva prueba, dirigirse a la funcion realizar_pruebas(){...}.
		Agregar en la categoria que considere conveniente la funcion que pertenece a su prueba.
		Esta funcion tiene que devolver un bool (true significa que paso la prueba)
		Este estado es enviado a la funcion mostrar_resultado(){...} que dira si se paso la prueba.
		Se puede utilizar la funcion assert() para verificar si la prueba es exitosa, para eso, esta necesita una comparacion booleana,
		y un mensaje a ser mostrado. Este mensaje aparecera con un OK o ERROR dependiendo el caso. Si fallo, tambien se mostrara el archivo y la linea
		del codigo.

