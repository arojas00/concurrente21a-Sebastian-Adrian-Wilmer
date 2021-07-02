/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef MATRIX_HPP
#define MATRIX_HPP

char **create_matrix(int height, int width);
void fillMatrix(int rows, int cols, char **matrix);
void printMatrix(int rows, int cols, char **matrix);
void copyMatrix(int rows, int cols, char **matrix, char **newMatrix);

#endif  // MATRIX_HPP