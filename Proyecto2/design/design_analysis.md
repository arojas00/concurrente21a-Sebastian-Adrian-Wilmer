### Análisis del diseño
 
1. Diseño de parte distribuida
 
Para la parte distribuida vamos a utilizar mapeo por bloque, el programa calcula cuantos mapas le tocan a cada proceso y luego cada proceso toma el nombre del mapa o de los mapas que le tocaron para poder abrir el mapa y procesarlo.
 
2. Diseño de parte concurrente
 
Para la parte concurrente vamos a utilizar el mapeo cíclico para tener el mayor incremento de velocidad posible basándonos en los resultados de la etapa anterior, mapeando el procesamiento de las filas de la matriz de cada mapa de manera cíclica.
 
3. Diseño de parte híbrida
 
La parte híbrida busca utilizar ambos openMP y MPI para mejorar el rendimiento total del programa, utilizando MPI para separar los datos en procesos y openMP para que en cada proceso los datos que le tocan se procesen lo más rápido posible, para esto vamos a usar un proceso por nodo disponible en el cluster y crear hilos igual a la cantidad de núcleos disponibles en cada nodo en un intento por mejorar el tiempo de ejecución del programa.
 
4. Ventajas y desventajas
 
El mapeo por MPI es rápido si todos los procesos se están utilizando sin embargo si la cantidad de procesos es más grande que la cantidad de datos a procesar muchos procesos se van a quedar sin hacer nada y se desperdicia potencia, para los casos grandes de prueba esto no es un problema porque todos los procesos van a estar trabajando, otra desventaja puede ser si a un solo proceso le tocan datos a procesar muy grandes en comparación con otros procesos pues ese proceso va a tardar mucho más tiempo en terminar, por esto entonces vamos a utilizar menos procesos en total para la version hibrida y nos vamos a quedar con un proceso por nodo disponible, el mapeo por openMP mejora la velocidad de ejecución del programa si utilizamos el mapeo que nos da un mejor rendimiento que en este caso sería el mapeo cíclico, usar openMP sin muchos procesos debería resultar eficaz para la ejecución del programa pero usar openMP con muchos procesos podría hacer que el programa se vuelva más lento, para este caso escogimos usar un hilo por cada núcleo disponible en cada nodo del cluster para correr el programa con openMP.
 
Si combinamos ambos métodos de mapeo deberíamos terminar con un programa más eficiente y eficaz para resolver el problema, esto lo veremos en los resultados de rendimiento.
 
5. Manejo de entrada y salida
 
El manejo de la entrada y la salida lo vamos a manejar de manera similar a cuando el programa utilizaba solo openMP, vamos a leer una hoja de trabajo con los nombres de todos los mapas a procesar y guardar el nombre de cada mapa en una estructura de datos, luego cuando iniciemos el MPI vamos a darle a cada proceso el nombre del mapa o los mapas que le tocan para que cuando cada proceso inicie no tenga problemas de lectura y dos procesos no intenten leer del mismo mapa, para la salida cada proceso va a crear los archivos de texto que le tocan de acuerdo al nombre del mapa que le tocaba de manera que dos procesos no intenten crear un archivo para un mismo mapa, los mapas se van a organizar en orden en la carpeta `output`.
