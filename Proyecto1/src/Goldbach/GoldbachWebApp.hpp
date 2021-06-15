// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <stdio.h>
#include "GoldbachCalculator.hpp"
#include <iostream>

class GoldbachWebApp {
  
  private:
    goldbach_t* calculator;
    values_t* valores;
    
  public:
    GoldbachWebApp();
    ~GoldbachWebApp();
    
    values_t* calculate_sums(int64_t* array, int64_t array_size);
  
};

/*
int main() {
  
  int64_t array[2];
  array[0] = -32;
  array[1] = 12; 
  GoldbachWebApp* webApp = new GoldbachWebApp();
  webApp->calculate_sums(array, 2);
}
*/
#endif // GOLDBACHCALCULATOR_HPP
