/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef MAGO_HPP
#define MAGO_HPP

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>

#include "Bosque.hpp"
#include "Map.hpp"


/**
 * @brief 
 */
class Mago{
  
 protected:
  
 private:
 int nights;
 Bosque* bosqueDelMago;
 Map* map;
 Map* newForest;
 std::vector<std::string> maps_array;
 std::vector<int> nights_array;
 std::string path;

 public:
 Mago();
 ~Mago();
 int start(int argc, char* argv[]);
 void run_job();
 void run_nights(int map_index);
 void readJob(FILE* job);


};

#endif  // MAGO_HPP
