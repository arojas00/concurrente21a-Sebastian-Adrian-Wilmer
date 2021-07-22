// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#include <assert.h>
#include <errno.h>
#include <pthread.h>
#include <queue>
#include <semaphore.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <math.h>

#include "GoldbachCalculator.hpp"
#include "Log.hpp"

GoldbachCalculator :: GoldbachCalculator() {
  this->cant_sumas = 0;
  this->value = 0;
}

GoldbachCalculator :: ~GoldbachCalculator() {}

int GoldbachCalculator :: run() {
  // Start the forever loop to consume all the Sockets that arrive
  this->consumeForever();

  // If the forever loop finished, no more sockets will arrive
  Log::append(Log::INFO, "Consumer", "ended");
  return EXIT_SUCCESS;
}

void GoldbachCalculator :: consume(const DataValues& numbers) {

  //Separamos el string en partes
  bool signo;
  //Parte del valor
  this->value = numbers.get_number();

  int64_t value_positive = 0;
  if (value >= 0)
    signo = true;
  else {
    signo = false;
    value_positive = value*-1;
  }

  //string para guardar el resultado
  std::string sumas;

  if (value_positive > 5) {
    if (esPar(value_positive)) {
      cant_sumas = conjetura_debil(value_positive, signo);
    } else {
      cant_sumas = conjetura_fuerte(value_positive, signo);
    }
    sumas = construir_resultado();
  } else {
    sumas = std::to_string(value) + ": NA";
  }
  DataValues* resultado = new DataValues(value, numbers.get_position(), numbers.get_ID());
  resultado->set_sumas(sumas);
  this->produce(resultado);
}


bool GoldbachCalculator :: esPar(int64_t value) {
  return (value%2) == 0;
}

bool GoldbachCalculator :: esPrimo(int64_t value) {
  bool primo = true;
  // Si el numero mayor que dos y es par, no es primo
  if (value > 2) {
    if (value % 2 == 0) {
      return false;
    }
    // Si el numero mayor que 3 y es multiplo de 3, no es primo
    if (value > 3) {
      if (value % 3 == 0) {
        return false;
      }

      if (value > 5) {

        long long limite = ((long long)sqrtl(value)) + 1;
        //indice para saltar los numeros pares y multiplos de 3
        long long skip_index = 0;

        for (long long i = 5; i < limite; i += 2) {
          if (skip_index != 2) {
            if (value % i == 0) {
              return false;
            }
            ++skip_index; 
          } else {
              skip_index = 0;
          }
        }
      }
    }
  }
  return primo;
}

int GoldbachCalculator :: conjetura_debil(int64_t value, bool signo) {

  int cantSumas = 0;
  for (int64_t i = 2; i < (value/2)+1; i++) { 
    if (esPrimo(i)) { // Busca el primer numero primo
      int64_t j = value - i;
      if (esPrimo(j)) { // Busca el segundo numero primo
        if ((i + j) == value && j >= i) { // Si ambos primos sumados son iguales al valor
          cantSumas += 1; // Se incrementa la cantidad de sumas
          if (signo == false) { // Si el numero es negativo se agregan a la cola de sumas
            this->cola_sumas.push(i);
            this->cola_sumas.push(j);
          }
        }
      }
    }
  }

  return cantSumas; // retorna la cantidad de sumas
}

int GoldbachCalculator :: conjetura_fuerte(int64_t value, bool signo) {

  int cantSumas = 0;
  for (int64_t i = 2; i < (value/2)+1; i++) { 
    if (esPrimo(i)) { // Busca el primer numero primo
      for (int64_t j = i; j < value; j++) {
        if (esPrimo(j)) { // Busca el segundo numero primo
          int64_t k = value - (i+j);
          if (esPrimo(k)) { // Busca el tercer numero primo
            if ((i + j + k) == value && k >= j) { // Si los tres primos sumados son igual al valor
              cantSumas += 1; // Se incrementa la cantidad de sumas
              if (signo == false) { // Si el numero es negativo se agregan a la cola de sumas
                this->cola_sumas.push(i);
                this->cola_sumas.push(j);
                this->cola_sumas.push(k);
              }
            }
          }
        }
      }
    }
  }

  return cantSumas; // retorna la cantidad de sumas
}

std::string GoldbachCalculator :: construir_resultado() {
  std::string resultado = "";
  if (value < 5) {
    resultado.append("-" + value);
    resultado.append(": " + std::to_string(cant_sumas) + "sums: ");
    std::string num_1, num_2, num_3;
    num_1 = ""; num_2 = ""; num_3 = "";
    for (int i = 0; i < cant_sumas; i++) { // Se recorre el arreglo de sumas para imprimir los numeros
      if (esPar(value)) { // Si es par se imprimen dos numeros
        num_1 = std::to_string(cola_sumas.front());
        cola_sumas.pop();
        num_2 = std::to_string(cola_sumas.front());
        cola_sumas.pop();
        resultado.append(num_1 + " + " + num_2);
      } else { // Si es impar se imprimen tres numeros
        num_1 = std::to_string(cola_sumas.front());
        cola_sumas.pop();
        num_2 = std::to_string(cola_sumas.front());
        cola_sumas.pop();
        num_3 = std::to_string(cola_sumas.front());
        cola_sumas.pop();
        resultado.append(num_1 + " + " + num_2 + " + " + num_3);
      }
      if (i != (cant_sumas-1)) { // Si no es la ultima suma se imprime ','
        resultado.append(", ");
      }
    }
  } else {
    resultado.append(std::to_string(value) + ": " + std::to_string(cant_sumas) + " sums");
  }
  return resultado;
}


