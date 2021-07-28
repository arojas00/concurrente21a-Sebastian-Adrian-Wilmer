# Concurrente21a-Prohibido abandonar

Este es el repositorio grupal del equipo Prohibido abandonar para el curso de Programación paralela y concurrente del I Ciclo 2021

# Proyecto 1 Servidor web concurrente - Sumas de Goldbach: 

#### Equipo: Prohibido abandonar  
Integrantes:  
- Alfredo Sebastian Chaves Vargas - B52067
- Wilmer Araya Rivas - B80538
- Adrián Rojas Arias - B96789

### Descripción del problema
En el avance 1 se construyó un servidor web concurrente que podía atender una cantidad arbitraria de clientes de forma simultánea, los cuales solicitan obtener sumas de Goldbach calculadas por una aplicación web serial. Sin embargo, este diseño no es óptimo. Por ejemplo, si en una máquina con 8 núcleos de procesador se levanta un servidor web capaz de atender 1000 conexiones concurrentes, y en efecto se conectan 1000 usuarios que solicitan una cantidad considerable de trabajo cada uno, el servidor tendrá 1000 hilos (ó "1000 calculadoras") compitiendo por los 8 núcleos, lo que crea una gran competencia y cambio de contexto por ellos, además de mayor consumo de memoria principal. En este avance se creará una solución que haga mejor uso de los recursos de la máquina.

#### Objetivo del Proyecto
El objetivo del proyecto es desarrollar un servidor web concurrente y distribuido que permita a sus visitantes obtener las sumas de Goldbach de números en los que están interesados. 

### Build
Se debe descargar la carpeta Proyecto1 o clonar el repositorio

Para compilar correr `make/make all`

Para correr el programa se debe llamar de esta forma:

bin/ejecutable Numero del puerto Numero máximo de conexiones

Ej:

`bin/Proyecto1 8080 8`

### Manual de usuario
Una vez compilado, se puede generar un cliente ingresando a http://localhost:XXXX/ , donde XXXX es el numero de puerto asignado. En el ejemplo anterior se utilizaba el puerto 8080, por lo que el URL sería http://localhost:8080/ . Al haber generado el cliente, se pueden realizar solicitudes por medio tanto de la caja de consulta ubicada en la página principal, como por el URI. Para realizar una consulta de múltiples numeros se deben escribir en el URI separados por comas. (ej: http://localhost:8080/5,-67,9,-7)

### Diseño
Diagrama de petri:
<br/>
![design](Proyecto1/design/Design.jpg)
Diagrama de clases:
<br/>
![design](Proyecto1/design/UML_class.jpeg)

### Ejecución
Consulta de un solo número:
<br/>
![design](Proyecto1/design/Request.png)
Consulta de múltiples números por medio del URI:
<br/>
![design](Proyecto1/design/Request_URI.png)
