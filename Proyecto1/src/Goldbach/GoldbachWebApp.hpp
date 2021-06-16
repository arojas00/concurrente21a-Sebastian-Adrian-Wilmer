// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <stdio.h>
#include "GoldbachCalculator.hpp"
#include <iostream>
#include <string>
#include <stdint.h>
using namespace std;

class GoldbachWebApp {
  
  private:
    goldbach_t* calculator;
    values_t* valores;
    int64_t numberCount;

  public:
    /// Constructor 
    GoldbachWebApp();
    /// Destructor
    ~GoldbachWebApp();
    
    /// Calculates sums
    values_t* calculate_sums(string texto);

    int64_t getNumberCount();
  
};

/*
int main() {
  
  //nt64_t array[2];
  //array[0] = -32;
  //array[1] = 12; 
  string texto = "/8,5,1,55,6,55,-44";
  GoldbachWebApp* webApp = new GoldbachWebApp();
  webApp->calculate_sums(texto);
}
*/

#endif // GOLDBACHCALCULATOR_HPP
