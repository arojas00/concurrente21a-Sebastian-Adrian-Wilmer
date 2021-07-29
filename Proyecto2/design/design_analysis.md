# Análisis del diseño
 
#### 1. Tipo de descomposición y mapeo utilizado en la parte distribuida MPI
 
Para la parte distribuida utilizamos como **unidad de descomposicion el mapa**,  utilizando un **mapeo por bloque**,  El bloque de un proceso **i** (indice del proceso) está dado por el rango de índices enteros **[start, finish[**, donde start y finish son funciones dadas por

`start(i, D, w) = i(D / w) + min(i, mod(D, w))`
`finish(i, D, w) = start(i + 1, D, w)`

La funcion **min** calcula el numero menor entre dos numeros, **i** es el numero del proceso, **D** es la cantidad de mapas y **w** la cantidad total de procesos.

---
 
#### 2. Tipo de descomposición y mapeo utilizado en la parte concurrente OpenMP

Para la parte concurrente utilizamos como unidad de descomposicion las filas de cada mapa y utilizando un mapeo cíclico para tener el mayor incremento de velocidad posible, basándonos en los resultados de la etapa anterior.
Este mapeo ciciclo consiste en asignar a cada hilo ***i*** (indice del hilo) todas las filas con indice ***{i, i + w, i + 2w}*** y asi consecutivamente, donde ***w*** es la cantidad total de hilos. 

---
 
 
#### 3. Ventajas y desventajas

##### a) Ventaja del mapeo por bloque utilizado en la parte distribuida:

- Es el mapeo que potencialmente puede disminuir más fallos de caché o false sharing si se trabaja con memoria continua, debido a esto en algunos casos muy escasos el mapeo por bloque podria ser el mas eficiente, por ejemplo el caso en que todos los mapas sean del mismo tamaño y a todos los procesos se les asigne la misma cantidad de mapas.

##### b) Desventaja del mapeo por bloque utilizado en la parte distribuida:

- Si a un solo proceso le tocan datos a procesar muy grandes en comparación con otros procesos este proceso va a tardar mucho más tiempo en terminar, mientras los otros estaran sin realizar trabajo.

##### c) Ventaja del mapeo ciclico utilizado en la parte concurrente:

- Este mapeo es apto para cuando los datos tienen un patron predecible, como es el caso de las filas del mapa, por esta razon en las mediciones que se realizaron en la etapa anterior este mapeo fue el mas eficiente.

##### d) Desventaja del mapeo ciclico utilizado en la parte concurrente:

- Al igual que su ventaja, su desventaja tambien depende del patron ya que si las unidades de trabajo en este caso las filas fueran unas mas grandes que otras y siguieran un determinado patron en el cual a un solo hilo se le asignan las mas grandes, este mapeo no seria el mas adecuado.

---

#### 4. Separacion de asuntos

Este programa no utiliza separacion de asuntos ya que todos los procesos tienen la misma funcion.

---

 
#### 5. Manejo de la entrada y salida

Cada proceso lee el archivo **job.txt** y almacena en un arreglo todos los nombres de los archivos que contienen los mapas, luego mediante el mapeo por bloques los procesos se reparten un bloque de los mapas que se encuentran en el arreglo, cada proceso se encarga de leer los archivos **map.txt** que le fueron asignados, de realizarles los cambios y de guardar estos mapas con los cambios realizados en los archivos **map.txt** de salida que seran creados en la carpeta **output.**
 

