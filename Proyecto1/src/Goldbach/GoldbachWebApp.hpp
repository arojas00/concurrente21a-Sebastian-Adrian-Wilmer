// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <stdio.h>
#include "Queue.hpp"
#include "GoldbachCalculator.hpp"
#include <iostream>
#include <string>
#include <stdint.h>
using namespace std;

class GoldbachWebApp {
  
  private:
    //goldbach_t* calculator;
    values_t* valores;
    int64_t numberCount;

  public:
    Queue<int>* URI_queue;
    GoldbachCalculator** goldbachCalculators;
    /// Constructor 
    GoldbachWebApp();
    /// Destructor
    ~GoldbachWebApp();

    void GoldbachWebApp::startCalculators();
    
    /// Calculates sums
    values_t* calculate_sums(string texto);

    int64_t getNumberCount();
  
};

#endif // GOLDBACHCALCULATOR_HPP