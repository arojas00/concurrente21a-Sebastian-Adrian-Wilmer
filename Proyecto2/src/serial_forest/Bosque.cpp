/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#include "Bosque.hpp"
#include "matrix.hpp"

/*
/Funciones seriales del bosque:
/Recibir como parametro al crear un nuevo bosque las filas y columnas para guardar en una matriz
/Tener un metodo para cada regla que modifique una celda de la matriz leyendo el arbol original y guardando la nueva celda en una nueva matriz
/Tener un metodo que actualice todo el bosque
/
/Funciones concurrentes del bosque:
/
*/

Bosque::Bosque(int filas,int columnas,int noches) {
  this->columnas = columnas;
  this->filas = filas;
  this->noches = noches;
  this->matriz_bosque = create_matrix(filas, columnas);
}

Bosque::~Bosque() {
}

void Bosque::changeForest(int numero_filas, int numero_columnas, char **matrix, char **newMatrix) {
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