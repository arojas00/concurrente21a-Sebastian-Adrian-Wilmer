/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef BOSQUE_HPP
#define BOSQUE_HPP

#include "Map.hpp"

/**
 * @brief Aplica los cambios respectivos en el mapa despues de cada noche
 */
class Bosque{
  
  protected:
  
  private:
    int numero_filas;
    int numero_columnas;

  private:
    /**
     * @brief Revisa las casillas aledañas en busca de una inundacion. 
     * @details Si alrededor de la casilla hay al menos 4 lagos, 
     * la casilla se vuelve lago.
     * @param fila la fila de la matriz a ser revisada.
     * @param columna la columna de la matriz a ser revisada.
     * @param matriz_bosque la matriz con el bosque por revisar.
     * @return retorna true si se debe aplicar el cambio.
     */
    bool checkInundation(int fila, int columna, char **matriz_bosque);
    /**
     * @brief Revisa las casillas aledañas en busca de hacinamiento. 
     * @details Si alrededor de la casilla hay al menos 4 arboles, 
     * la casilla se vuelve pradera.
     * @param fila la fila de la matriz a ser revisada.
     * @param columna la columna de la matriz a ser revisada.
     * @param matriz_bosque la matriz con el bosque por revisar
     * @return retorna true si se debe aplicar el cambio.
     */
    bool checkOvercrowding(int fila, int columna, char **matriz_bosque);
    /**
     * @brief Revisa las casillas aledañas en busca de una sequia. 
     * @details Si alrededor de la casilla hay menos de 3 lagos, 
     * la casilla se vuelve pradera.
     * @param fila la fila de la matriz a ser revisada.
     * @param columna la columna de la matriz a ser revisada.
     * @param matriz_bosque la matriz con el bosque por revisar.
     * @return retorna true si se debe aplicar el cambio.
     */
    bool checkDrought(int fila, int columna, char **matriz_bosque);
    /**
     * @brief Revisa las casillas aledañas en busca de una reforestacion. 
     * @details Si alrededor de la casilla hay al menos 3 arboles, 
     * la casilla se vuelve arbol.
     * @param fila la fila de la matriz a ser revisada.
     * @param columna la columna de la matriz a ser revisada.
     * @param matriz_bosque la matriz con el bosque por revisar.
     * @return retorna true si se debe aplicar el cambio.
     */
    bool checkReforestation(int fila, int columna, char **matriz_bosque);
    /**
     * @brief Revisa si la casilla es valida dentro de la matriz. 
     * @details Evita salir de los limites de la matriz.
     * @param fila la fila de la matriz a ser revisada.
     * @param columna la columna de la matriz a ser revisada.
     * @return retorna true si se debe aplicar el cambio.
     */
    bool checkCell(int fila, int columna);

  public:
    /**
     * @brief Constructor
     */
    Bosque(int filas,int columnas);
    /**
     * @brief Destructor
     */
    ~Bosque();
    /**
     * @brief Revisa las casillas en busca de cambios.
     * @details Recorre la matriz y revisa si las casillas requieren
     * cambios, este es el metodo paralelo.
     * @param matrix objeto Map que contiene la matriz original
     * @param newMatrix objeto Map que contiene la matriz a actualizar
     * @param numero_hilos La cantidad de hilos a ser ejecutados
     */
    void changeForest(Map* matrix, Map* newMatrix, int numero_hilos);

};

#endif  // BOSQUE_HPP
