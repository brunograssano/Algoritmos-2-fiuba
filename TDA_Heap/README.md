# TDA HEAP BINARIO (Tpcito)
* Se entrega la implementacion del TDA Heap junto con la primitiva heapsort. Se incluyen tambien ejemplos de uso del heap,
un makefile y la biblioteca del assert utilizado en las pruebas.
* Este TDA esta implementado con un vector dinamico. Para crearlo es necesario pasarle una cantidad minima inicial que estime el usuario que lo va a utilizar.
  Una vez alcanzada dicha cantidad, el vector se expande al doble (si puede tomar la memoria).
  En caso de ir vaciando el heap, ocurrira la contrario, el vector se achicara una vez que ocupe menos que la mitad de su tamanio maximo actual.
  En este caso tambien se le agrega un valor minimo para que no continue achicandose a partir de un momento dado, de forma que no quede un vector muy chico.
* Para la primitiva de eliminar el primer elemento se eligio no devolver el elemento guardado. Si se quiere conservar este elemento, se debe de
  usar la primitiva especifica que lo devuelve. Si este esta en memoria se le debe de realizar una copia, ya que si se le paso al heap un destructor,
  este destruira el elemento.
* Este heap puede ser utilizado tanto como maximal(1) o minimal(-1). Si se desea utilizar la primitiva de heapsort,
  tambien se le debe de indicar que tipo de orden se quiere.

## COMPILACION:
*Para realizar la compilacion se recomienda utilizar el makefile.

###MAKEFILE:
* ```make heap```
	Compila el heap.c y heap.h

* ```make pruebas```
	Compila los dos ejemplos y el assert, dejandolos listos para su ejecucion.

* ```make valgrind```
	Ejecuta los dos ejemplos

* ```make clean```
	Limpia el directorio sacando los -o

## EJECUCION:
* Se pueden ejecutar los ejemplos mediante las siguientes opciones
	1) ./ejemplo1 o ./ejemplo2 (No mostraria informacion detallada sobre el uso de la memoria)
	2) valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./ejemplo1 || ./ejemplo2
	3) make valgrind

## PRUEBAS:
  * En el ejemplo1.c se incluyen ejemplos basicos sobre el uso de las primitivas del heap.
  Se evalua el comportamiento del heap con enteros y caracteres. Ademas se incluyen pruebas sobre los casos nulos que puede
  llegar a tener el heap y de este en unas pruebas de volumen.
  * En el ejemplo2.c se guardan en un heap maximal autos. Estos autos estan en memoria y son comparados con su precio.
  Se observa que funcione correctamente el heap en este caso.

![heap](https://media.geeksforgeeks.org/wp-content/cdn-uploads/binaryheap.png "heap")