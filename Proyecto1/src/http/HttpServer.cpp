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
  this->clientQueue = new Queue<Socket>;
}

HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket& client) {
  // TODO(you): Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop
  clientQueue->push(client);
  //crear httpConnectionHandler
  //this->consumers.resize(this->clientConnections);
  //for ( size_t index = 0; index < this->clientConnections; ++index ) {
  this->consumers = new HttpConnectionHandler();
    //assert(this->consumers[index]);
    //this->consumers[index]->createOwnQueue();
  //}
  consumers->setConsumingQueue(clientQueue);
  for ( size_t index = 0; index < this->clientConnections; ++index ) {
    this->consumers->startThread();
  }
  for ( size_t index = 0; index < this->clientConnections; ++index ) {
    this->consumers->waitToFinish();
  }
}
