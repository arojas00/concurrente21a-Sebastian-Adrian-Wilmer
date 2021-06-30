/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#include <stdlib.h>
#include <stdio.h>
#include "Mago.hpp"
#include "matrix.hpp"

/*
/Funciones seriales del mago:
/(Wil)Leer mapa de entrada estandar y guardarlo en el arbol de memoria compartida y en la variable para serial y leer
/ la cantidad de noches(ciclos) y el tamano desde el txt
/(Adrian)Hacer funcionar las funciones del bosque con una matriz de ejemplo para generar un nuevo bosque(Mientras se completan las cosas de arriba)
/(Sebas)Despues de que se completa el nuevo bosque generar un archivo txt con el numero de noche(ciclo) en la carpeta bosques

/Guardar el nuevo bosque donde estaba el primero para recibirlo como parametro en el siguiente ciclo
/
/Funciones concurrentes del mago:
/Leer la cantidad de hilos que se quieren usar o usar la cantidad que tenga la maquina
/Guardar los arboles en memoria compartida
/Es posible que sea al mago que crea los hilos
*/
typedef struct
{
   size_t thread_count;
    Bosque bosque_original;
    Bosque bosque_nuevo;
} shared_data_t;

typedef struct
{
    size_t thread_number;
    shared_data_t *shared_data;
} private_data_t;

Mago::Mago() {
}

Mago::~Mago() {
}

int Mago::start(int argc, char* argv[]) {
  int rows, cols, nights, num = 0;
  scanf("%i %i %i\n", &rows, &cols, &nights);
  bosqueDelMago = new Bosque(rows,cols,nights);
  fillMatrix(rows, cols, bosqueDelMago->matriz_bosque);
  char **newForest = create_matrix(rows, cols);
  copyMatrix(rows, cols, bosqueDelMago->matriz_bosque, newForest);
  if (0 < nights) {
    for (int i = 0; i <= nights; i++) {
      printf("%i:\n", i);
      printMatrix(rows, cols, bosqueDelMago->matriz_bosque);
      bosqueDelMago->changeForest(rows, cols, bosqueDelMago->matriz_bosque, newForest);
      copyMatrix(rows, cols, newForest, bosqueDelMago->matriz_bosque);
      printf("\n");
    }
  }
  else {
    num = 0;
    printf("%i:\n", num);
    printMatrix(rows, cols, bosqueDelMago->matriz_bosque);
    for (int i = 0; i > nights; i--) {
      bosqueDelMago->changeForest(rows, cols, bosqueDelMago->matriz_bosque, newForest);
      copyMatrix(rows, cols, newForest, bosqueDelMago->matriz_bosque);
      num++;
    }
    printf("\n%i:\n", num);
    printMatrix(rows, cols, bosqueDelMago->matriz_bosque);
  }
  return EXIT_SUCCESS;
}