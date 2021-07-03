/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef MAP_HPP
#define MAP_HPP

#include <stdio.h>
#include <string>

class Map {

  private:
    /// Cantidad de filas
    int rows;
    /// Cantidad de columnas
    int cols;
    /// Matriz para el mapa
    char** map_matrix;

  public:
    /**
     * @brief
     */
    Map(int rows, int cols);

    /**
     * @brief
     */
    ~Map();

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    char **create_matrix();

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    void fillMatrix(FILE* file);

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    void printMatrix();

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    void copyMatrix(char **newMatrix);

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    void createTextFile(std::string filename);

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    char** getMatrix();

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    int getRows();

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    int getCols();
};
#endif  // MAP_HPP