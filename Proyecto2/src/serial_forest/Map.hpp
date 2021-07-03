/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef MAP_HPP
#define MAP_HPP

#include <stdio.h>
#include <string>

class Map {

  private:
    int rows;
    int cols;
    char** map_matrix;

  public:
    Map(int rows, int cols);
    ~Map();
    char **create_matrix();
    void fillMatrix(FILE* file);
    void printMatrix();
    void copyMatrix(char **newMatrix);
    void createTextFile(std::string filename);
    char** getMatrix();
    int getRows();
    int getCols();
};

/*
char **create_matrix(int height, int width);
void fillMatrix(FILE* file, int rows, int cols, char **matrix);
void printMatrix(int rows, int cols, char **matrix);
void copyMatrix(int rows, int cols, char **matrix, char **newMatrix);
void createTextFile(int rows, int cols, char **matrix, std::string filename);
*/
#endif  // MAP_HPP