/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include "HttpConnectionHandler.hpp"
#include "Log.hpp"

HttpConnectionHandler::HttpConnectionHandler(int consumerDelay)
  : consumerDelay(consumerDelay) {
}

int HttpConnectionHandler::run() {
  // Start the forever loop to consume all the Sockets that arrive
  this->consumeForever();

  // If the forever loop finished, no more sockets will arrive
  
  return EXIT_SUCCESS;
}

void HttpConnectionHandler::consume(const Socket& data) {
  (void)data;
  ++this->receivedMessages;
}