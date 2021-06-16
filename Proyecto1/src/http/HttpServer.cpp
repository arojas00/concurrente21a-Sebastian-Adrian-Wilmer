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
#include "Queue.hpp"

HttpServer::HttpServer() {
}

HttpServer::~HttpServer() {
}

void HttpServer::listenForever(const char* port) {
  return TcpServer::listenForever(port);
}

void HttpServer::handleClientConnection(Socket& client) {
  producer = new SocketProducer();
  producer->produce(client);
  HttpConnectionHandler* consumer;
  consumer = new HttpConnectionHandler();
  consumer->setConsumingQueue(producer->getProducingQueue());
  // TODO(you): Make this method concurrent. Store client connections (sockets)
  // into a collection (e.g thread-safe queue) and stop
  //Socket& socketRef = socketReceived;
  //producer->produce(socketReceived);
  
}
