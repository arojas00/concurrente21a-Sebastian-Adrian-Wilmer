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
 Bosque* bosqueDelMago;
 Map* map;

 public:
 Mago();
 ~Mago();
 int start(int argc, char* argv[]);
 void readJob(FILE* job, std::vector<std::string> &maps_array, std::vector<int> &nights_array);


};

#endif  // MAGO_HPP
