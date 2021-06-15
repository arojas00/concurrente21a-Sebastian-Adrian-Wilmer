// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4

#include <stdint.h>
#include <queue>

#include "GoldbachWebApp.hpp"
#include "QueueSums.hpp"
#include <sstream>
#include <string>

typedef struct values{
  int64_t value; // valor
  queue_t* cola_sumas; // cola para guardar las sumas de cada valor
  bool signo; // Para guardar el signo del numero
  int cant_sumas; // La cantidad de sumas
} values_t;

GoldbachWebApp ::GoldbachWebApp() {
  this->calculator = goldbach_create();
}

GoldbachWebApp ::~GoldbachWebApp() {
  goldbach_destroy(this->calculator);
}

values_t* GoldbachWebApp:: calculate_sums(string texto) {
  std::queue<int64_t> cola;
  string valor = "";
  stringstream input_stringstream(texto);
  std::string::size_type sz;
  int64_t num = 0;
  
  input_stringstream.get();
  while(getline(input_stringstream, valor, ',')) {
    num = std::stol(valor, &sz);
    cola.push(num);
  }
  
  valores = goldbach_run(calculator, cola);
  /*int64_t x = 0;
  queue_dequeue(valores[6].cola_sumas, &x);
  //x = valores[6].value;
  std::cout << x << endl;*/
  return valores;
}
