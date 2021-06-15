/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include "SocketProducer.hpp"
#include "Log.hpp"
#include "UtilityTest.hpp"

SocketProducer::SocketProducer() {
  setProducerQueue();
}

int SocketProducer::run() {

  return EXIT_SUCCESS;
}

void SocketProducer::setProducerQueue() {
  consumingQueue = new Queue<Socket>();
  this->setProducingQueue(consumingQueue);
}
