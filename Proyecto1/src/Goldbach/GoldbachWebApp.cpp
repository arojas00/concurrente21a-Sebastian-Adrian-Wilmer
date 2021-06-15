// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4

#include <stdint.h>

#include "GoldbachWebApp.hpp"
#include "queue.hpp"

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

values_t* GoldbachWebApp:: calculate_sums(int64_t* array, int64_t array_size) {
  valores = goldbach_run(calculator, array, array_size);
  //int num = valores[0].value;
  //int64_t x = 0;
  //queue_dequeue(valores[0].cola_sumas, &x);
  //std::cout << x;
  return valores;
}
