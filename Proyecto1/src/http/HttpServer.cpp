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
  consumer = new HttpConnectionHandler();
  clientQueue->push(socketRef);
  consumer->setConsumingQueue(clientQueue);
  consumer->startThread();
}
void HttpServer::startHttpServer(){
  //crear lista de consumers
  // for(size_t i = 0; i < max_connections; i++){
  //   consumer[i] = new HttpConnectionHandler(this);
  //   consumer[i]->setConsumingQueue(clientQueue);
  //   consumer[i]->startThread();
  // }
}
void HttpServer::stopHttpServer(){
//   //push empty sockets in consumingQueue
//   Socket emptySocket;
//   for(size_t i = 0; i < max_connections; i++){
//***
//     consumer[i]->getConsumingQueue()->push(emptySocket);
//   }
//   //for max_connection
//   //clientQueue->push(emptySocket)
}