/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef MAGO_HPP
#define MAGO_HPP

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <vector>

#include "Bosque.hpp"
#include "Map.hpp"


/**
 * @brief La clase mago lee el el nombre del archivo job y el path para
 * leer los mapas, crear los arboles y crear los archivos de salida
 */
class Mago{
 private:
    ///  Cantidad de noches
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
    /// Numero de hilos a ejecutar
    int thread_count;

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
     * @param argv Argumento 1 es el nombre
     * del job y argumento 2 es el path
     * @param argc Cantidad de argumentos
     * @return Codigo de error
     */
    int start(int argc, char* argv[]);

 private:
    /**
     * @brief Llena un arreglo con los mapas del job y otro con la
     * cantidad de noches de cada mapa
     * @details Despues de llenar los arreglos se cierra el job y
     * se llama a run_job
     * @param job es el archivo job que continene los mapas y las
     * noches
     * @param argc numero de argumentos del programa
     * @param argv valor de los argumentos del programa
     * @return void 
     */
    void create_processes(FILE* job, int argc, char* argv[]);

    /**
     * @brief Se leen los mapas y se llama a run nights
     * @details Para cada mapa del job se crea un nuevo objeto mapa
     * en el que se guarda el mapa que se leyo del archivo de texto
     * y se llama a run nights para procesar cada mapa la cantidad
     * de noches que se necesita
     * @return void
     */
    void run_job(int index, int rank);

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
     * @param map el mapa que se va a escribir en el archivo
     */
    void createTextFile(std::string filename, char** map);

    /**
     * @brief Calcula en cual mapa empezara cada a proceso a trabajar
     * @param rank el numero del proceso
     * @param end el numero total de mapas en el job
     * @param workers la cantidad de procesos
     * @param begin el primer mapa
     */
    int calculate_start(int rank, int end, int workers, int begin);

    /**
     * @brief Calcula en cual mapa terminara cada proceso de trabajar
     * @param rank el numero del proceso
     * @param end el numero total de mapas en el job
     * @param workers la cantidad de procesos
     * @param begin el primer mapa
     */
    inline int calculate_finish(int rank, int end, int workers, int begin);
};
#endif  // MAGO_HPP
