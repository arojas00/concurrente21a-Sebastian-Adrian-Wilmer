/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef MAGO_HPP
#define MAGO_HPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "Bosque.hpp"
#include "Map.hpp"


/**
 * @brief 
 */
class Mago{
  
  private:
    /// Cantidad de noches
    int nights;
    /// Objeto Bosque
    Bosque* bosqueDelMago;
    /// Mapa original
    Map* map_original;
    /// Copia de mapa original
    Map* map_copy;
    /// Arreglo de nombres de mapas
    std::vector<std::string> maps_array;
    /// Arreglo de cantidades de noches
    std::vector<int> nights_array;
    /// Ruta donde se contiene el job
    std::string path;

  public:

    /**
     * @brief Constructor
     */
    Mago();

    /**
     * @brief Destructor
     */
    ~Mago();

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    int start(int argc, char* argv[]);

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    void run_job();

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    void run_nights(int map_index);

    /**
     * @brief 
     * @details 
     * @param 
     * @return 
     */
    void readJob(FILE* job);
};
#endif  // MAGO_HPP
