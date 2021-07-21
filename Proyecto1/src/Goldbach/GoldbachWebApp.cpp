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
  //this->calculator = goldbach_create();
  URI_queue = new Queue<int64_t[]>;
  result_queue = new Queue<std::string>;
  this->numberCount = 0;
}

GoldbachWebApp ::~GoldbachWebApp() {
  //goldbach_destroy(this->calculator);
}

void GoldbachWebApp::startCalculators(){
  //crear lista de consumers
  goldbachCalculators = new GoldbachCalculator*[8];
  std::cout << "max connections " << 8 << std::endl;
  for(size_t i = 0; i < 8; i++){
    goldbachCalculators[i] = new GoldbachCalculator();
    goldbachCalculators[i]->setConsumingQueue(URI_queue);
    goldbachCalculators[i]->startThread();
  }
}

/*values_t* GoldbachWebApp:: calculate_sums(string texto) {
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
  numberCount = cola.size();
  //valores = goldbach_run(calculator, cola);

  return valores;
}*/
int64_t GoldbachWebApp ::getNumberCount(){
  return this->numberCount;
}
