// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4

#include <stdint.h>
#include <queue>
#include "GoldbachWebApp.hpp"
#include "QueueSums.hpp"
#include <sstream>
#include <string>

GoldbachWebApp ::GoldbachWebApp() {
  //this->calculator = goldbach_create();
  URI_queue = new Queue<DataValues>;
  results_queue = new Queue<DataValues*>;
}

GoldbachWebApp ::~GoldbachWebApp() {
  //goldbach_destroy(this->calculator);
}

void GoldbachWebApp::process_Request(std::string uri){
  // Partir el uri en numeros separados, obtener la posicion en el string y meter el uri entero como ID en un objeto DataValues
  // Meter el nuevo objeto DataValues en la cola para cada posicion
}

void GoldbachWebApp::start_Calculators(){
  //crear lista de consumers
  goldbachCalculators = new GoldbachCalculator*[8];
  std::cout << "max connections " << 8 << std::endl;
  for(size_t i = 0; i < 8; i++){
    goldbachCalculators[i] = new GoldbachCalculator();
    goldbachCalculators[i]->setConsumingQueue(URI_queue);
    goldbachCalculators[i]->setProducingQueue(results_queue);
    goldbachCalculators[i]->startThread();
  }
}
