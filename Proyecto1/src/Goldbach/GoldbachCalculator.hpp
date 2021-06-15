// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef GOLDBACHCALCULATOR_HPP
#define GOLDBACHCALCULATOR_HPP
#include <stdint.h>
#include <queue>

typedef struct goldbach goldbach_t;
typedef struct values values_t;

goldbach_t* goldbach_create();
values_t* goldbach_run(goldbach_t* goldbach, std::queue<int64_t> queue_values);
void goldbach_destroy(goldbach_t* goldbach);

#endif // GOLDBACHCALCULATOR_HPP
