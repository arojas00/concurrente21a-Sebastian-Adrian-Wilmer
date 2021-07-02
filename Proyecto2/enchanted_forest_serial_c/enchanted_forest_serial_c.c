#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

char **create_matrix(int height, int width);
void fillMatrix(int rows, int cols, char **matrix);
void printMatrix(int rows, int cols, char **matrix);
void copyMatrix(int rows, int cols, char **matrix, char **newMatrix);
void changeForest(int rows, int cols, char **matrix, char **newMatrix);
bool checkInundation(int row, int col, char **matrix, int rows, int cols);
bool checkOvercrowding(int row, int col, char **matrix, int rows, int cols);
bool checkDrought(int row, int col, char **matrix, int rows, int cols);
bool checkReforestation(int row, int col, char **matrix, int rows, int cols);
bool checkCell(int row, int col, int rows, int cols);

int main()
{
  int rows, cols, days, num = 0;
  scanf("%i %i %i\n", &rows, &cols, &days);
  char **forest = create_matrix(rows, cols);
  fillMatrix(rows, cols, forest);
  char **newForest = create_matrix(rows, cols);
  copyMatrix(rows, cols, forest, newForest);
  if (0 < days)
  {
    for (int i = 0; i <= days; i++)
    {
      printf("%i:\n", i);
      printMatrix(rows, cols, forest);
      changeForest(rows, cols, forest, newForest);
      copyMatrix(rows, cols, newForest, forest);
      printf("\n");
    }
  }
  else
  {
    num = 0;
    printf("%i:\n", num);
    printMatrix(rows, cols, forest);
    for (int i = 0; i > days; i--)
    {
      changeForest(rows, cols, forest, newForest);
      copyMatrix(rows, cols, newForest, forest);
      num++;
    }
    printf("\n%i:\n", num);
    printMatrix(rows, cols, forest);
  }
  return 0;
}
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
void changeForest(int rows, int cols, char **matrix, char **newMatrix)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
    {
      if (matrix[i][j] == 'a')
      {
        if (checkInundation(i, j, matrix, rows, cols) == true)
        {
          newMatrix[i][j] = 'l';
        }
        else
        {
          if (checkOvercrowding(i, j, matrix, rows, cols) == true)
          {
            newMatrix[i][j] = '-';
          }
        }
      }
      else
      {
        if (matrix[i][j] == 'l')
        {
          if (checkDrought(i, j, matrix, rows, cols) == true)
          {
            newMatrix[i][j] = '-';
          }
        }
        else
        {
          if (matrix[i][j] == '-')
          {
            if (checkReforestation(i, j, matrix, rows, cols) == true)
            {
              newMatrix[i][j] = 'a';
            }
          }
        }
      }
    }
  }
}
bool checkInundation(int row, int col, char **matrix, int rows, int cols)
{
  int lakes = 0;
  for (int i = row - 1; i <= row + 1; i++)
  {
    for (int j = col - 1; j <= col + 1; j++)
    {
      if (checkCell(i, j, rows, cols) == true)
      {
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
bool checkOvercrowding(int row, int col, char **matrix, int rows, int cols)
{
  int trees = 0;
  for (int i = row - 1; i <= row + 1; i++)
  {
    for (int j = col - 1; j <= col + 1; j++)
    {
      if (checkCell(i, j, rows, cols) == true)
      {
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
bool checkDrought(int row, int col, char **matrix, int rows, int cols)
{
  int lakes = 0;
  for (int i = row - 1; i <= row + 1; i++)
  {
    for (int j = col - 1; j <= col + 1; j++)
    {
      if (checkCell(i, j, rows, cols) == true)
      {
        if (matrix[i][j] == 'l')
          lakes++;
      }
    }
  }
  if (lakes <= 3)
  {
    return true;
  }
  else
    return false;
}
bool checkReforestation(int row, int col, char **matrix, int rows, int cols)
{
  int trees = 0;
  for (int i = row - 1; i <= row + 1; i++)
  {
    for (int j = col - 1; j <= col + 1; j++)
    {
      if (checkCell(i, j, rows, cols) == true)
      {
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
bool checkCell(int row, int col, int rows, int cols)
{
  if (row < rows && 0 <= row && col < cols && 0 <= col)
    return true;
  else
    return false;
}