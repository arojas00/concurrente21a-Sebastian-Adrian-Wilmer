#include <stdlib.h>
#include <iostream>
#include "Map.hpp"


Map :: Map(int rows, int cols) {
  this->rows = rows;
  this->cols = cols;
  this->map_matrix = create_matrix();
}

Map :: ~Map() {
  for (int i = 0; i < rows; i++) {
    delete[] map_matrix[i];
  }
  delete[] map_matrix;
}

char** Map :: create_matrix() {
  char **matrix = new char*[rows];
  for (int i = 0; i < rows; ++i)
    matrix[i] = new char[cols];
  return matrix;
}

void Map :: fillMatrix(FILE* file) {
  char cell;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      fscanf(file, "%c", &cell);
      map_matrix[i][j] = cell;
    }
    fscanf(file, "\n");
  }
}

void Map :: copyMatrix(char **newMatrix) {
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      newMatrix[i][j] = map_matrix[i][j];
    }
  }
}

char** Map :: getMatrix() {
  return this->map_matrix;
}

int Map :: getRows() {
  return this->rows;
}

int Map :: getCols() {
  return this->cols;
}