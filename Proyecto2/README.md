# Concurrente21a-Prohibido abandonar

Este es el repositorio grupal del equipo Prohibido abandonar para el curso de Programación paralela y concurrente del I Ciclo 2021

# Proyecto 2 El bosque encantado: 

#### Equipo: Prohibido abandonar  
Integrantes:  
- Alfredo Sebastian Chaves Vargas- B52067
- Wilmer Araya Rivas - B80538
- Adrián Rojas Arias - B96789

### Descripción del problema

Un rey generoso de una isla muy lejana, estaba preocupado porque sus ciudadanos estaban aburridos de la monotonía de la pequeña isla. Tuvo la idea de encantar el bosque que está alrededor de su castillo, de tal forma que cada medianoche el bosque cambie y al día siguiente los ciudadanos encuentren un lugar diferente para recrearse. A su mago le pareció genial la idea, pero no sabe qué reglas incluir en el hechizo para que el bosque se mantenga en equilibrio y no llegue a convertirse en un desierto o una selva impenetrable. Si tuvieran alguna forma de ver el efecto de las reglas a futuro, podrían decidir el hechizo con mayor seguridad.

El rey tiene un mapa del bosque como el extracto que puede verse más adelante en el ejemplo de entrada (map001.txt). El mapa ilustra lo que hay en cada metro cuadrado de la isla, a los que les llaman celdas. Una celda puede contener un árbol mágico ('a'), un trozo de lago encantado ('l'), o pradera donde pueden transitar los ciudadanos ('-'). Las dimensiones del mapa se encuentran en la primera línea de entrada, indicadas como el número de filas y columnas.

### Objetivo del Proyecto

El objetivo del proyecto es lograr procesar desde un archivo de texto que contiene ubicaciones de mapas en otros archivos de texto el resultado de cambiar la cantidad de noches utilizando reglas para cambiar el bosque encantado noche por noche por cierta cantidad N de noches y guardarlos en archivos de texto con los resultados de cada noche o el resultado final despues de procesar todas las noches

### Build
Se debe descargar la carpeta Proyecto2 o clonar el repositorio

Para compilar correr `make/make all`

Los casos de prueba se encuentran en la carpeta `tests/test_set_X/input/`

Para correr el programa se debe llamar de esta forma

Ubicacion Nombre del archivo a leer Nombre de la ubicacion del archivo

Ej:

`bin/Proyecto2 job001.txt tests/test_set_1/input/`

### Manual de usuario
Correr el programa de esta manera crea los archivos de salida en la carpeta output

Para eliminar los archivos de la carpeta output es necesario llamar a make clean

### Diseño

![design](design/Design.jpg)

### Analisis de rendimiento

#### Avance 1

En la siguiente tabla se muestran los resultados tras ejecutar los diferentes tipos de mapeo en un nodo esclavo del cluster arenal:

![design](design/Analisis.jpeg)

Adicionalmente se calcula el speedup y eficiencia de los tipos de mapeo con respecto a la versión serial del programa. Al realizar las optimizaciones se conjeturó sobre el rendimiento de los tipos de mapeos, siendo el mapeo dinámico el del mejor rendimiento esperado. Tras realizar las mediciones, todos los mapeos tuvieron un comportamiento similar, siendo el cíclico el de mejor rendimeinto, con un speedup de 3.57 y eficiencia de 0.45. Una posible causa de este resultado sería el tamaño de las unidades a descomponer, ya que procesaba una fila del arreglo en cada iteración. Ante esto se experimentó reduciendo el tamaño de las unidades a casillas, pero los resultados fueron mas altos que en el mapeo anterior.

`Gráfico de eficiencia y speedup:`

![design](design/Graph.jpeg)

`Gráfico de duración:`

![design](design/Duracion1.jpg)

En el gráfico anterior se presenta el speedup de cada tipo de mapeo en el eje y izquierdo, asi como la eficiencia de los mismos en el eje y derecho. Gracias a esto se puede apreciar el comportamiento de los diferentes tipos de mapeo, los cuales son muy similares entre si, con una ligera mejora en el mapeo cíclico.

#### Avance 2

![design](design/Table.png)

Se realizó una optimización a la hora de copiar los mapas entre cada noche, ya que se podía cumplir este objetivo con un swap de punteros, el cual es menos costoso en términos de tiempo. Esta optimización se incluyó en las mediciones, con lo que se tuvo un speedup de 1.21 segundos con respecto a la versión cíclica anterior. Posteriormente se realizaron las implementaciones de mpi e híbrida entre mpi y openMP. Para el caso de mpi se utilizó el número de procesos como la cantidad de trabajadores, mientras que en la hibrida se utilizaron el número de hilos multiplicado por los tres procesos, dando ambos 24 como resultado. Los procesos generados por mpi se encargan de generar los cambios de un mapa a la vez, por lo que se espera que la versión híbrida sea la de mejor rendimiento, al también realizar la descomposición de mapas por filas.

`Gráfico de eficiencia y speedup:`

![design](design/Graph2.png)

`Gráfico de duración:`

![design](design/Duracion2.jpg)

Los resultados mostraron una mejora en la duración de cada implementación, siendo la híbrida la que obtuvo el mayor speedup. Debido al alto número de trabajadores, el gráfico muestra una eficiencia menor a las versiones de openMP, a pesar de que se utilizan todos los recursos del clúster arenal. Los resultados corresponden a los esperados tras realizar la implementación, debido a las mejoras antes mencionadas. La eficiencia del programa se podría mejorar con un mapeo de hilos condicionado a la cantidad de filas y columnas en la matriz, ya que de ser una mayor que la otra, se podría utilizar la unidad de mapeo adecuada para cada situación.
