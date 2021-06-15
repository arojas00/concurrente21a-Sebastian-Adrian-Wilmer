/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include "SocketProducer.hpp"
#include "Log.hpp"
#include "UtilityTest.hpp"

SocketProducer::SocketProducer(size_t packageCount, int productorDelay
  , size_t consumerCount)
  : packageCount(packageCount)
  , productorDelay(productorDelay)
  , consumerCount(consumerCount) {
}

int SocketProducer::run() {

  return EXIT_SUCCESS;
}

int SocketProducer::createMessage(size_t index) const {

  return 0;
}
