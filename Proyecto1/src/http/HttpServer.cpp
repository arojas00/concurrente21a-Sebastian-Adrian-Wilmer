// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <stdexcept>
#include <string>
#include <iostream>

#include "HttpServer.hpp"
#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Socket.hpp"
#include "SocketProducer.hpp"

HttpServer::HttpServer() {
  clientQueue = new Queue<Socket>;
}

HttpServer::~HttpServer() {
  delete clientQueue;
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket& client) {
  // TODO(you): Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop
  Socket socketRef = client;
  clientQueue->push(socketRef);
  this->consumers = new HttpConnectionHandler();
  this->consumers->setConsumingQueue(clientQueue);
  this->consumers->startThread();
}
void HttpServer::waitConsumers() {
  this->consumers->waitToFinish();
}