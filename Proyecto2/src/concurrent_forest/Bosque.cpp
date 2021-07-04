/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#include "Bosque.hpp"
#include "Map.hpp"
#include <omp.h>
#include <vector>

/*
/Funciones seriales del bosque:
/Recibir como parametro al crear un nuevo bosque las filas y columnas para guardar en una matriz
/Tener un metodo para cada regla que modifique una celda de la matriz leyendo el arbol original y guardando la nueva celda en una nueva matriz
/Tener un metodo que actualice todo el bosque
/
/Funciones concurrentes del bosque:
/
*/

Bosque::Bosque() {
}

Bosque::~Bosque() {
}

void Bosque::changeForest(Map* map, Map* new_map, int numero_hilos) {
  int thread_count = omp_get_max_threads();
  if (numero_hilos != 0) {
    thread_count = numero_hilos;
  }
  int block_size = 1;
  char** matrix = map->getMatrix();
  char** newMatrix = new_map->getMatrix();
  int numero_filas = map->getRows();
  int numero_columnas = map->getCols();
  std::vector<int> mapping(numero_filas);
  #pragma omp parallel for num_threads(thread_count) default(none) \
    shared(numero_filas) shared(mapping) shared(block_size) \
    shared(numero_columnas) shared(matrix) shared(newMatrix) \
    schedule(static, block_size)
  for (int i = 0; i < numero_filas; i++) {
    for (int j = 0; j < numero_columnas; j++) {
      if (matrix[i][j] == 'a') {
        if (checkInundation(i, j, matrix, numero_filas, numero_columnas) == true) {
          newMatrix[i][j] = 'l';
        }
        else {
          if (checkOvercrowding(i, j, matrix, numero_filas, numero_columnas) == true) {
            newMatrix[i][j] = '-';
          }
        }
      }
      else {
        if (matrix[i][j] == 'l') {
          if (checkDrought(i, j, matrix, numero_filas, numero_columnas) == true) {
            newMatrix[i][j] = '-';
          }
        }
        else {
          if (matrix[i][j] == '-') {
            if (checkReforestation(i, j, matrix, numero_filas, numero_columnas) == true) {
              newMatrix[i][j] = 'a';
            }
          }
        }
      }
    }
  }
}
bool Bosque::checkInundation(int fila, int columna, char **matrix, int numero_filas, int numero_columnas) {
  int lakes = 0;
  for (int i = fila - 1; i <= fila + 1; i++) {
    for (int j = columna - 1; j <= columna + 1; j++) {
      if (checkCell(i, j, numero_filas, numero_columnas) == true) {
        if (matrix[i][j] == 'l')
          lakes++;
      }
    }
  }
  if (lakes >= 4)
    return true;
  else
    return false;
}
bool Bosque::checkOvercrowding(int fila, int columna, char **matrix, int numero_filas, int numero_columnas) {
  int trees = 0;
  for (int i = fila - 1; i <= fila + 1; i++) {
    for (int j = columna - 1; j <= columna + 1; j++) {
      if (checkCell(i, j, numero_filas, numero_columnas) == true) {
        if (matrix[i][j] == 'a')
          trees++;
      }
    }
  }
  if (trees - 1 > 4)
    return true;
  else
    return false;
}
bool Bosque::checkDrought(int fila, int columna, char **matrix, int numero_filas, int numero_columnas) {
  int lakes = 0;
  for (int i = fila - 1; i <= fila + 1; i++) {
    for (int j = columna - 1; j <= columna + 1; j++) {
      if (checkCell(i, j, numero_filas, numero_columnas) == true) {
        if (matrix[i][j] == 'l')
          lakes++;
      }
    }
  }
  if (lakes <= 3) {
    return true;
  }
  else
    return false;
}
bool Bosque::checkReforestation(int fila, int columna, char **matrix, int numero_filas, int numero_columnas) {
  int trees = 0;
  for (int i = fila - 1; i <= fila + 1; i++) {
    for (int j = columna - 1; j <= columna + 1; j++) {
      if (checkCell(i, j, numero_filas, numero_columnas) == true) {
        if (matrix[i][j] == 'a')
          trees++;
      }
    }
  }
  if (trees >= 3)
    return true;
  else
    return false;
}
bool Bosque::checkCell(int fila, int columna, int numero_filas, int numero_columnas) {
  if ((unsigned int)fila < (unsigned int)numero_filas && (unsigned int)columna < (unsigned int)numero_columnas)
    return true;
  else
    return false;
}