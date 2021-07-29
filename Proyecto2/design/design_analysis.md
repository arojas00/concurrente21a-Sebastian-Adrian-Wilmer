# Análisis del diseño
 
#### 1. Tipo de descomposición y mapeo utilizado en la parte distribuida MPI
 
Para la parte distribuida utilizamos como **unidad de descomposición el mapa**,  utilizando un **mapeo por bloque**,  El bloque de un proceso **i** (índice del proceso) está dado por el rango de índices enteros **[start, finish[**, donde start y finish son funciones dadas por

`start(i, D, w) = i(D / w) + min(i, mod(D, w))`

`finish(i, D, w) = start(i + 1, D, w)`

La función **min** devuelve el número menor entre dos números, **i** es el número del proceso, **D** es la cantidad de mapas y **w** la cantidad total de procesos.

---
 
#### 2. Tipo de descomposición y mapeo utilizado en la parte concurrente OpenMP

Para la parte concurrente utilizamos como **unidad de descomposición las filas** de cada mapa y utilizando un **mapeo cíclico** para tener el mayor incremento de velocidad posible, basándonos en los resultados de la etapa anterior.
Este mapeo cíciclo consiste en asignar a cada hilo ***i*** (índice del hilo) todas las filas con índice ***{i, i + w, i + 2w}*** y así consecutivamente, donde ***w*** es la cantidad total de hilos. 

---
 
 
#### 3. Ventajas y desventajas

##### a) Ventaja del mapeo por bloque utilizado en la parte distribuida:

- Es el mapeo que potencialmente puede disminuir más fallos de caché o false sharing si se trabaja con memoria continua, debido a esto en algunos casos muy escasos el mapeo por bloque podría ser el más eficiente, por ejemplo el caso en que todos los mapas sean del mismo tamaño y a todos los procesos se les asigne la misma cantidad de mapas.

##### b) Desventaja del mapeo por bloque utilizado en la parte distribuida:

- Si a un solo proceso le tocan datos a procesar muy grandes en comparación con otros procesos este proceso va a tardar mucho más tiempo en terminar, mientras los otros estarán sin realizar trabajo.

##### c) Ventaja del mapeo cíclico utilizado en la parte concurrente:

- Este mapeo es apto para cuando los datos tienen un patrón predecible, como es el caso de las filas del mapa, por esta razón en las mediciones que se realizaron en la etapa anterior este mapeo fue el más eficiente.

##### d) Desventaja del mapeo cíclico utilizado en la parte concurrente:

- Al igual que su ventaja, su desventaja también depende del patrón ya que si las unidades de trabajo en este caso las filas fueran unas más grandes que otras y siguieran un determinado patrón en el cual a un solo hilo se le asignan las más grandes, este mapeo no sería el más adecuado.

---

#### 4. Separación de asuntos

Este programa no utiliza separación de asuntos ya que todos los procesos tienen la misma función.

---

 
#### 5. Manejo de la entrada y salida

Cada proceso lee el archivo **job.txt** y almacena en un arreglo todos los nombres de los archivos que contienen los mapas, luego mediante el mapeo por bloques los procesos se reparten un bloque de mapas que se encuentran en el arreglo, cada proceso se encarga de leer los archivos **map.txt** que le fueron asignados, de realizarles los cambios y de guardar estos mapas con los cambios realizados en los archivos **map.txt** de salida que serán creados en la carpeta **output.**
 

