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
  clientQueue = new Queue<Socket>();
}

HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket& client) {
  // TODO(you): Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop
  //clientQueue = new Queue<Socket>;
  std::cout << "1" << std::endl;
  Socket socketRef = client;
  clientQueue->push(socketRef);
  std::cout << "2" << std::endl;

  //crear httpConnectionHandler
  //consumers = new HttpConnectionHandler();
  //consumers->consume(clientQueue->pop());

  //this->consumers.resize(this->clientConnections);
  //for ( size_t index = 0; index < this->clientConnections; ++index ) {
  this->consumers = new HttpConnectionHandler();
  std::cout << "3" << std::endl;
    //assert(this->consumers[index]);
    //this->consumers[index]->createOwnQueue();
  //}
  this->consumers->setConsumingQueue(clientQueue);
  std::cout << "4" << std::endl;
  //for ( size_t index = 0; index < this->clientConnections; ++index ) {
    this->consumers->startThread();
  std::cout << "5" << std::endl;

  //}
  //for ( size_t index = 0; index < this->clientConnections; ++index ) {
    //this->consumers->waitToFinish();
  std::cout << "salio" << std::endl;

  //}
}
