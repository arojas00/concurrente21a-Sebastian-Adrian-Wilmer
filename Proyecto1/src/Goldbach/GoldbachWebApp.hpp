// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <stdio.h>
#include "Queue.hpp"
#include "GoldbachCalculator.hpp"
#include <iostream>
#include <string>
#include <stdint.h>
#include "DataValues.hpp"
using namespace std;

class GoldbachWebApp {
  
  public:
    Queue<DataValues>* URI_queue;
    Queue<DataValues>* results_queue;
    GoldbachCalculator** goldbachCalculators;
    DataValues dataValue;

    /**
   * @brief Constructor
   */ 
    GoldbachWebApp();
    /**
   * @brief Destructor
   */
    ~GoldbachWebApp();

    /**
   * @brief Inicia las calculadoras
   */
    void start_Calculators();

    /**
   * @brief Procesa el request del cliente
   * @param uri El Uri que contiene los numeros a trabajar
   */
    void process_Request(std::string uri);

    /**
   * @brief Recibe e inserta el valor a la cola de consumir de la calculadora
   * @param value El objeto DataValues donde se almacena el numero
   */
    void handleDataValue(DataValues& value);

    /**
   * @brief Ensambla los resultados
   * @details Saca los objetos de la cola de resultados y segun el 
   * identificador de cada objeto DataValues los ensambla en orden en un
   * arreglo.
   * @param value El objeto DataValues donde se almacena el numero
   */
    void assembleResponse();

    /**
   * @return Retorna el resultado de las sumas de cada request
   */
    DataValues* getResponseData();

    /**
   * @return Retorna la cantidad de datos de cada request
   */
    int64_t getDataCount();
    
    void sendSignal();

  private:
    DataValues* responseData;
    int64_t dataCount;
    Semaphore* can_access_queue;
};

#endif // GOLDBACHCALCULATOR_HPP