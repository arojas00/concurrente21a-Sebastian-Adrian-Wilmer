// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4

#include <stdint.h>
#include <queue>
#include <sstream>
#include <string>

#include "GoldbachWebApp.hpp"
#include "QueueSums.hpp"
#include "Semaphore.hpp"

GoldbachWebApp ::GoldbachWebApp() {
  //this->calculator = goldbach_create();
  URI_queue = new Queue<DataValues>;
  results_queue = new Queue<DataValues>;
  dataCount = 0;
  can_access_queue = new Semaphore(0);
}

GoldbachWebApp ::~GoldbachWebApp() {
  delete URI_queue;
  delete results_queue;
  delete can_access_queue;
  delete goldbachCalculators;
}

void GoldbachWebApp::process_Request(std::string uri){
  // Partir el uri en numeros separados, obtener la posicion en el string y meter el uri entero como ID en un objeto DataValues
  // Meter el nuevo objeto DataValues en la cola para cada posicion
  string valor = "";
  stringstream input_stringstream(uri);
  std::string::size_type sz;
  int64_t num = 0;
  int64_t posicion = 0;
  std::string ID = uri;
  input_stringstream.get();
  while(getline(input_stringstream, valor, ',')) {
    num = std::stol(valor, &sz);
    dataValue.setData(num, posicion, uri);
    handleDataValue(dataValue);
    dataCount++;
    posicion++;
  }
  for(int i = 0; i < 8; i++){
    dataValue.setData(0, 0, "");
    handleDataValue(dataValue);
  }
}

void GoldbachWebApp::handleDataValue(DataValues& value) {
  // TODO(you): Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop
  DataValues dataValuesRef = value;
  URI_queue->push(dataValuesRef);
}

void GoldbachWebApp::printProducingQueue(){
  responseData = new DataValues[dataCount];
  for(int esperarHilos = 0; esperarHilos < 8; esperarHilos++){
    can_access_queue->wait();
  }
  while(results_queue->empty() != true){
    DataValues dt = results_queue->pop();
    responseData[dt.getPosition()] = dt;
  }
}

DataValues* GoldbachWebApp::getResponseData(){
  // std::cout << this->responseData[0].getNumber() << " " 
  //   << this->responseData[0].getSumas() << std::endl;
  return responseData;
}

int64_t GoldbachWebApp::getDataCount(){
  return dataCount;
}

void GoldbachWebApp::start_Calculators(){
  //crear lista de consumers
  goldbachCalculators = new GoldbachCalculator*[8];
  std::cout << "max connections " << 8 << std::endl;
  for(size_t i = 0; i < 8; i++){
    goldbachCalculators[i] = new GoldbachCalculator();
    goldbachCalculators[i]->setConsumingQueue(URI_queue);
    goldbachCalculators[i]->setProducingQueue(results_queue);
    goldbachCalculators[i]->setSemaphore(can_access_queue);
    goldbachCalculators[i]->startThread();
  }
}