#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include "matrix.hpp"

char **create_matrix(int rows, int cols)
{
  char **matrix = (char **)calloc(rows, sizeof(char *));
  for (int row = 0; row < rows; ++row)
    matrix[row] = (char *)calloc(cols, sizeof(char));
  return matrix;
}
void fillMatrix(FILE* file, int rows, int cols, char **matrix)
{
  char cell;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      fscanf(file, "%c", &cell);
      matrix[i][j] = cell;
    }
    fscanf(file, "\n");
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

void createTextFile(int rows, int cols, char **matrix, std::string filename)
{
  std::ofstream fw(filename, std::ofstream::out);
   //check if file was successfully opened for writing
    if (fw.is_open())
    {
      //store array contents to text file
      for(int x = 0; x < rows; x++){
        for (int y = 0; y < cols; y++) {
        fw << matrix[x][y];
        }
         fw << "\n";
      }
      fw.close();
    }
    else std::cout << "Problem with opening file";

}
