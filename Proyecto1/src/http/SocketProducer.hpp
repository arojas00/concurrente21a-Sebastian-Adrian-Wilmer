/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef SOCKETPRODUCER_HPP
#define SOCKETPRODUCER_HPP

#include "Socket.hpp"
#include "Producer.hpp"

/**
 * @brief A productor class example
 * Produces network messages and push them to the queue
 */
class SocketProducer : public Producer<Socket> {
  DISABLE_COPY(SocketProducer);

 protected:
  /// Number of packages to be produced
  size_t max_connections = 0;
  /// Delay of producer to create a package, negative for max random
  size_t consumerCount = 0;

 private:
   Queue<Socket>* consumingQueue;

 public:
  /// Constructor
  SocketProducer();
  /// Do the message production in its own execution thread
  int run() override;
  /// Creates a simulation message to be sent by the network
  void setProducerQueue();
};

#endif  // SOCKETPRODUCER_HPP
