// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef GOLDBACHCALCULATOR_HPP
#define GOLDBACHCALCULATOR_HPP
#include <stdint.h>
#include <queue>
#include <string>
#include "DataValues.hpp"

#include "Assembler.hpp"


  class GoldbachCalculator : public Assembler<DataValues,DataValues*> {

    private:

      int64_t value;
      int cant_sumas;
      std::queue<int> cola_sumas;

    public:

    /// Constructor
    GoldbachCalculator();

    /// Destructor
    ~GoldbachCalculator();

    /// Consume the number in its own execution thread
    int run() override;

    /// Consume el numero al cual le calcula las sumas de goldbach
    void consume(const DataValues& numbers);

    private:

      /**
       * @brief Evalua si el numero ingresado es par o no
       * @details Si el resto de la division del numero entre 2 
       *          es igual a 0 significa que el numero es par
       * @param Numero a ser evaluado
       * @return Retorna true si el numero es par,
       *         de lo contrario retorna false
       */
      bool esPar(int64_t value);

      /**
       * @brief Evalua si el numero ingresado es primo o no
       * @details Si la division del numero ingresado da entero
       *          solo cuando se divide por si mismo y 1 significa que es primo.
       * @param Numero a ser evaluado
       * @return Retorna true si el numero es primo,
       *         de lo contrario retorna false
       */
      bool esPrimo(int64_t value);

      /**
       * @brief Calcula la cantidad de sumas goldbach que tiene cada numero
       * @details Se evaluan todas las posibles combinaciones de numeros primos
       *          mediante ciclos for, si el numero es par guarda los dos
       *          numeros que conforman la suma en el arreglo, si es impar guarda 
       *          los tres numeros que conforman la suma.
       * @param Numero a ser evaluado y el arreglo en el cual se guardan los numeros
       *        que conforman la suma.
       * @return Retorna la cantidad de sumas de goldbach
       */
      int conjetura_debil(int64_t value, bool signo);

      int conjetura_fuerte(int64_t value, bool signo);

      std::string construir_resultado();

  };
#endif // GOLDBACHCALCULATOR_HPP
