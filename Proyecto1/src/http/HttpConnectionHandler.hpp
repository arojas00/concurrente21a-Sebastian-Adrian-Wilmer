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
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "HttpServer.hpp"

/**
 * @brief A consumer class to handle http connections
 */
//template <typename DataType>

class HttpConnectionHandler : public Consumer<Socket> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(HttpConnectionHandler);
  //stopCondition = Socket(NULL);
 private:
  //WebServer webServer;

 public:
  /// Constructor
  explicit HttpConnectionHandler();
  /// Consume the socket in its own execution thread
  int run() override;
  /// Override this method to process any data extracted from the queue
  void consume(const Socket& client);

};

#endif  // HTTPCONNECTIONHANDLER_HPP
