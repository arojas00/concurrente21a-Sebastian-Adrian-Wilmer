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

/**
 * @brief A consumer class to handle http connections
 */
//template <typename DataType>

class HttpConnectionHandler : public Consumer<Socket> {
  /// Objects of this class cannot be copied
  DISABLE_COPY(HttpConnectionHandler);

 protected:
  /// This thread will consume from its queue
  Queue<Socket>* consumingQueue;
  /// This data will be used to represent that the Consumer must stop the
  /// consumption, and finish its work. It is used for cleaning purposes.
  const Socket stopCondition;
  /// True if this consumer owns the queue and it must be deleted in destructor
  bool ownsQueue;

 public:
  /// Creates a HttpConnectionHandler that uses an existing queue or creates its own
  /// @see stopCondition
  HttpConnectionHandler(Queue<Socket>* consumingQueue = nullptr
    , const Socket& stopCondition = Socket()
    , bool createOwnQueue = false)
    : consumingQueue(consumingQueue)
    , stopCondition(stopCondition)
    , ownsQueue(createOwnQueue) {
    // Error if asked to create own queue and provided an existing one to use
    assert(!(createOwnQueue && consumingQueue));
    if (createOwnQueue) {
      this->createOwnQueue();
    }
  }

  /// Destructor
  ~HttpConnectionHandler() {
    if (this->ownsQueue) {
      delete this->consumingQueue;
    }
  }

  /// Get access to the queue where this thread will consume
  inline Queue<Socket>* getConsumingQueue() {
    return this->consumingQueue;
  }

  /// Set the queue where this thread will consume elements
  inline void setConsumingQueue(Queue<Socket>* consumingQueue) {
    this->consumingQueue = consumingQueue;
  }

  /// Creates a new empty queue owned by this consumer
  void createOwnQueue() {
    assert(this->consumingQueue == nullptr);
    this->consumingQueue = new Queue<Socket>();
    this->ownsQueue = true;
  }
  /// Consumes from its queue, util the stop condition is popped
  /// For each data consumed, the @a consume method will be called
  void consumeForever() {
    assert(this->consumingQueue);
    while (true) {
      // Get the next data to consume, or block while queue is empty
      const Socket& data = this->consumingQueue->pop();
      // If data is the stop condition, stop the loop
      if ( data == this->stopCondition ) {
        break;
      }
      // Process this data
      this->consume(data);
    }
  }
  /// Consume the socket in its own execution thread
  int run() override;
  /// Override this method to process any data extracted from the queue
  void consume(const Socket& client);
};

#endif  // HTTPCONNECTIONHANDLER_HPP
