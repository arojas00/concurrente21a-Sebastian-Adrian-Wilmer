/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef MAP_HPP
#define MAP_HPP

#include <stdio.h>
#include <string>

/**
* @brief La clase lee los mapas y los almacena
*/
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
     * @brief Constructor
     */
    Map(int rows, int cols);

    /**
     * @brief Destructor
     */
    ~Map();

    /**
     * @brief Inicializa la matriz
     * @details 
     * @return una matriz de caracteres
     */
    char **create_matrix();

    /**
     * @brief Lee caracteres de un archivo y los guarda en la matriz
     * @details Se utiliza la funcion fscan para leer los caracteres
     * @param  FILE el archivo del cual se leen los caracteres 
     */
    void fillMatrix(FILE* file);

    /**
     * @brief Hace una copia de la matriz
     * @param newMatrix la matriz en la cual se guarda la copia
     */
    void copyMatrix(char **newMatrix);

    /**
     * @brief Se crea un archivo de texto
     * @details Se crea un archivo el cual contiene el cambio del mapa en cada medianoche
     * @param filename el nombre del archivo que se va crear
     */
    void createTextFile(std::string filename);

    /**
     * @return Devuelve la matriz de caracteres
     */
    char** getMatrix();

    /**
     * @return Devuelve la cantidad de filas
     */
    int getRows();

    /**
     * @return Devuelve la cantidad de columnas
     */
    int getCols();
};
#endif  // MAP_HPP