/// @copyright 2021 ECCI, Universidad de Costa Rica. All rights reserved
/// @author Sebastian-Adrian-Wilmer

#ifndef MAGO_HPP
#define MAGO_HPP

#include "Bosque.hpp"


/**
 * @brief 
 */
class Mago{
  
 protected:
  
 private:
 Bosque* bosqueDelMago = new Bosque(1,2,3);

 public:
 Mago();
 ~Mago();
 int start(int argc, char* argv[]);


};

#endif  // MAGO_HPP
