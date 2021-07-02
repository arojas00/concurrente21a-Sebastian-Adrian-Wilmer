/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer
#include <string>

#ifndef MATRIX_HPP
#define MATRIX_HPP

char **create_matrix(int height, int width);
void fillMatrix(FILE* file, int rows, int cols, char **matrix);
void printMatrix(int rows, int cols, char **matrix);
void copyMatrix(int rows, int cols, char **matrix, char **newMatrix);
void createTextFile(int rows, int cols, char **matrix, std::string filename);

#endif  // MATRIX_HPP