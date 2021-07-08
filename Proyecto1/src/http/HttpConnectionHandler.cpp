/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#include "HttpConnectionHandler.hpp"
#include "WebServer.hpp"
#include "Log.hpp"

HttpConnectionHandler::HttpConnectionHandler(){
  // webServer = thisHttpServer;
}

int HttpConnectionHandler::run() {
  // Start the forever loop to consume all the Sockets that arrive
  this->consumeForever();

  // If the forever loop finished, no more sockets will arrive
  Log::append(Log::INFO, "Consumer", "ended");
  return EXIT_SUCCESS;
}
void HttpConnectionHandler::consume(const Socket& client) {
  Socket socketRef = client;

  // TODO(Ardi) Move the following loop to a consumer thread class
  // While the same client asks for HTTP requests in the same connection
  while (true) {

    // Create an object that parses the HTTP request from the socket
    HttpRequest httpRequest(client);

    // If the request is not valid or an error happened
    if (!httpRequest.parse()) {
      // Non-valid requests are normal after a previous valid request. Do not
      // close the connection yet, because the valid request may take time to
      // be processed. Just stop waiting for more requests
      break;
    }

    // A complete HTTP client request was received. Create an object for the
    // server responds to that client's request
    HttpResponse httpResponse(client);

    // Give subclass a chance to respond the HTTP request
    //bool handled = handleHttpRequest(httpRequest, httpResponse);
    const bool handled = WebServer::getInstance().handleHttpRequest(httpRequest, httpResponse);

    // If subclass did not handle the request or the client used HTTP/1.0
    if (!handled || httpRequest.getHttpVersion() == "HTTP/1.0") {
      // The socket will not be more used, close the connection
      socketRef.close();
      break;
    }

    // This version handles just one client request per connection
    // TODO(Ardi): Remove this break after parallelizing this method
    break;
  }
}