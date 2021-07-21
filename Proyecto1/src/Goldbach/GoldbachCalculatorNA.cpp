/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>
#include "GoldbachCalculator.hpp"
#include "Log.hpp"

GoldbachCalculator::GoldbachCalculator(){
  // webServer = thisHttpServer;
}

int GoldbachCalculator::run() {
  // Start the forever loop to consume all the Sockets that arrive
  this->consumeForever();

  // If the forever loop finished, no more sockets will arrive
  Log::append(Log::INFO, "Consumer", "ended");
  return EXIT_SUCCESS;
}
void GoldbachCalculator::consume(const int& x) {
  int socketRef = x;
}