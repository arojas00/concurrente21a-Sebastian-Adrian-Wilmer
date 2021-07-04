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
 * @brief La clase mago lee el el nombre del archivo job y el path para
 * leer los mapas, crear los arboles y crear los archivos de salida
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
     * @brief Constructor, inicializa la cantidad de noches en 0
     */
    Mago();

    /**
     * @brief Destructor
     */
    ~Mago();

    /**
     * @brief Lee el job y el path
     * @details Lee el job y se lo pasa a read_job
     * @param argc Cantidad de argumentos, argumento 1 es el nombre
     * del job y argumento 2 es el path
     * @return Codigo de error
     */
    int start(int argc, char* argv[]);
    
    /**
     * @brief Llena un arreglo con los mapas del job y otro con la
     * cantidad de noches de cada mapa
     * @details Despues de llenar los arreglos se cierra el job y
     * se llama a run_job
     * @param job es el archivo job que continene los mapas y las
     * noches
     * @return void 
     */
    void read_job(FILE* job);

    /**
     * @brief Se leen los mapas y se llama a run nights
     * @details Para cada mapa del job se crea un nuevo objeto mapa
     * en el que se guarda el mapa que se leyo del archivo de texto
     * y se llama a run nights para procesar cada mapa la cantidad
     * de noches que se necesita
     * @param 
     * @return void
     */
    void run_job();

    /**
     * @brief Procesa los mapas las noches necesarias y crea los
     * archivos de salida
     * @details Si la cantidad de noches es mayor que cero para el 
     * mapa que se esta leyendo se hace para cada noche que se
     * procesa un archivo de texto con el resultado y si es menor
     * que cero se hace solo un archivo de texto con el resultado
     * final de todas las noches, para cambiar el bosque se llama
     * a la funcion changeforest
     * @param map_index es el indice del mapa guardado en el
     * arreglo de mapas
     * @return void
     */
    void run_nights(int map_index);

    /**
     * @brief Se crea un archivo de texto
     * @details Se crea un archivo el cual contiene el cambio del mapa en cada medianoche
     * @param filename el nombre del archivo que se va crear
     */
    void createTextFile(std::string filename, char** map);

};
#endif  // MAGO_HPP
