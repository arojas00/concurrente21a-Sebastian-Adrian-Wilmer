// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "HttpServer.hpp"
#include "GoldbachWebApp.hpp"
#include "HttpConnectionHandler.hpp"

#define DEFAULT_PORT "8080"

class HttpConnectionHandler;

class WebServer : public HttpServer {
  DISABLE_COPY(WebServer);

 private:
  GoldbachWebApp* webApp;
  /// TCP port where this web server will listen for connections
  const char* port = DEFAULT_PORT;
  /// Consumers of the simulated network messages
  //HttpConnectionHandler* consumers;
 public:
  /// Constructor
  WebServer();
  /// Destructor
  ~WebServer();

 //public:
  
  /// Start the simulation
  int start(int argc, char* argv[]);
  /// Get access to the unique instance of this Singleton class
  static WebServer& getInstance();

 //protected:
  /// Analyze the command line arguments
  /// @return true if program can continue execution, false otherwise
  bool analyzeArguments(int argc, char* argv[]);
  /// Handle HTTP requests. @see HttpServer::handleHttpRequest()
  bool handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) override;

 protected:
  /// Route, that provide an answer according to the URI value
  /// For example, home page is handled different than a number
  bool route(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// sets the headers for the server response
  void setHeaders(HttpResponse& httpResponse, std::string title);
  /// Sends the homepage as HTTP response
  bool serveHomepage(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Sends a page for a non found resouce in this server
  bool serveNotFound(HttpRequest& httpRequest, HttpResponse& httpResponse);
  /// Calculate the prime factorization of a number asked by the client, and
  /// sends the response in HTML format as HTTP response
  bool serveGoldbachSums(HttpRequest& httpRequest
    , HttpResponse& httpResponse, int64_t number, bool inQuery);
  void signalHandler();
};

#endif  // WEBSERVER_H
