#include <stdlib.h>
#include <stdio.h>
#include "matrix.hpp"

char **create_matrix(int rows, int cols)
{
  char **matrix = (char **)calloc(rows, sizeof(char *));
  for (int row = 0; row < rows; ++row)
    matrix[row] = (char *)calloc(cols, sizeof(char));
  return matrix;
}
void fillMatrix(int rows, int cols, char **matrix)
{
  char cell;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      scanf("%c", &cell);
      matrix[i][j] = cell;
    }
    scanf("\n");
  }
}
void copyMatrix(int rows, int cols, char **matrix, char **newMatrix)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      newMatrix[i][j] = matrix[i][j];
    }
  }
}
void printMatrix(int rows, int cols, char **matrix)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}