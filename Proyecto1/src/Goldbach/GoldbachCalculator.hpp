/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include <cassert>

#include "Queue.hpp"
#include "Thread.hpp"
#include "Assembler.hpp"


/**
 * @brief A consumer class to handle http connections
 */
//template <typename DataType>

class GoldbachCalculator : public Assembler<int,int> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(GoldbachCalculator);
  //stopCondition = Socket(NULL);
 private:
  // WebServer* webServer;

 public:
  /// Constructor
  GoldbachCalculator();
  /// Consume the socket in its own execution thread
  int run() override;
  /// Override this method to process any data extracted from the queue
  void consume(const int& x) override;

};

#endif  // HTTPCONNECTIONHANDLER_HPP
