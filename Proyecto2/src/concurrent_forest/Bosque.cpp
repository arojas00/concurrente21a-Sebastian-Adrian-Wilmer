/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#include <omp.h>
#include <vector>

#include "Bosque.hpp"
#include "Map.hpp"

Bosque::Bosque() {
}

Bosque::~Bosque() {
}

void Bosque::changeForest(Map* map, Map* new_map, int numero_hilos) {
  int thread_count = omp_get_max_threads();
  if (numero_hilos != 0) {
    thread_count = numero_hilos;
  }
  char** matrix = map->getMatrix();
  char** newMatrix = new_map->getMatrix();
  int numero_filas = map->getRows();
  int numero_columnas = map->getCols();
  std::vector<int> mapping(numero_filas);
  #pragma omp parallel for num_threads(thread_count) default(none) \
    shared(numero_filas) shared(mapping) shared(numero_columnas) \
    shared(matrix) shared(newMatrix) schedule(runtime)
  for (int i = 0; i < numero_filas; i++) {
    for (int j = 0; j < numero_columnas; j++) {
      changeCell(matrix, newMatrix, numero_filas, numero_columnas, i, j);
    }
  }
}

void Bosque :: changeCell(char** matrix, char** newMatrix
  , int numero_filas, int numero_columnas, int i, int j) {
  if (matrix[i][j] == '-') {
    if (checkReforestation(i, j, matrix, numero_filas
      , numero_columnas) == true) {
      newMatrix[i][j] = 'a';
    } else {
      newMatrix[i][j] = matrix[i][j];
    }
  } else {
    if (matrix[i][j] == 'l') {
      if (checkDrought(i, j, matrix, numero_filas
        , numero_columnas) == true) {
        newMatrix[i][j] = '-';
      } else {
        newMatrix[i][j] = matrix[i][j];
      }
    } else {
      if (matrix[i][j] == 'a') {
        int change = checkTrees(i, j, matrix, numero_filas
          , numero_columnas);
        if (change == 1) {
          newMatrix[i][j] = 'l';
        } else {
          if (change == 2) {
            newMatrix[i][j] = '-';
          } else {
            newMatrix[i][j] = matrix[i][j];
          }
        }
      }
    }
  }
}

int Bosque::checkTrees(int fila, int columna, char **matrix
  , int numero_filas, int numero_columnas) {
  int lakes = 0;
  int trees = 0;
  int change = 0;
  for (int i = fila - 1; i <= fila + 1; i++) {
    for (int j = columna - 1; j <= columna + 1; j++) {
      if (checkCell(i, j, numero_filas, numero_columnas) == true) {
        if (matrix[i][j] == 'l') {
          lakes++;
        } else {
          if (matrix[i][j] == 'a') {
            trees++;
          }
        }
      }
    }
  }
  if (lakes >= 4) {
    change = 1;
  } else {
    if (trees > 5) {
      change = 2;
    }
  }
  return change;
}
bool Bosque::checkDrought(int fila, int columna, char **matrix
  , int numero_filas, int numero_columnas) {
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
  } else {
    return false;
  }
}
bool Bosque::checkReforestation(int fila, int columna, char **matrix
  , int numero_filas, int numero_columnas) {
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
bool Bosque::checkCell(int fila, int columna, int numero_filas
  , int numero_columnas) {
  if ((unsigned int)fila < (unsigned int)numero_filas
    && (unsigned int)columna < (unsigned int)numero_columnas)
    return true;
  else
    return false;
}
