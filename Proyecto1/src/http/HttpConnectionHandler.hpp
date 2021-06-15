/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef HTTPCONNECTIONHANDLER_HPP
#define HTTPCONNECTIONHANDLER_HPP

#include <cassert>

#include "Queue.hpp"
#include "Thread.hpp"
#include "Socket.hpp"
#include "Consumer.hpp"

/**
 * @brief A consumer class to handle http connections
 */
class HttpConnectionHandler : public Consumer<Socket> {
  DISABLE_COPY(HttpConnectionHandler);

 protected:
  /// Delay of consumer to consume a package, negative for max random
  int consumerDelay = 0;
  /// Number of messages received
  size_t receivedMessages = 0;

 public:
  /// Constructor
  explicit HttpConnectionHandler(int consumerDelay);
  /// Consume the messages in its own execution thread
  int run() override;
  /// Override this method to process any data extracted from the queue
  void consume(const Socket& data) override;
};

#endif  // HTTPCONNECTIONHANDLER_HPP
