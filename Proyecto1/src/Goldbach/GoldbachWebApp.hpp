// Copyright 2021 Wilmer Araya <wilmer.araya@ucr.ac.cr> CC-BY-4
#ifndef GOLDBACHWEBAPP_HPP
#define GOLDBACHWEBAPP_HPP

#include <stdio.h>
#include "Queue.hpp"
#include "GoldbachCalculator.hpp"
#include <iostream>
#include <string>
#include <stdint.h>
#include "DataValues.hpp"
using namespace std;

class GoldbachWebApp {
  
  public:
    Queue<DataValues>* URI_queue;
    Queue<DataValues*>* results_queue;
    GoldbachCalculator** goldbachCalculators;
    DataValues dataValue;
    /// Constructor 
    GoldbachWebApp();
    /// Destructor
    ~GoldbachWebApp();

    void start_Calculators();

    void process_Request(std::string uri);

    void handleDataValue(DataValues& value);

    void printProducingQueue();
    
};

#endif // GOLDBACHCALCULATOR_HPP