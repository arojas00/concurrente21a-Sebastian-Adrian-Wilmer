// Copyright 2021 Jeisson Hidalgo-Cespedes. Universidad de Costa Rica. CC BY 4.0

#include <cassert>
#include <iostream>
#include <regex>
#include <stdexcept>
#include <string>
#include <stdint.h>
#include <signal.h>

#include "NetworkAddress.hpp"
#include "Socket.hpp"
#include "WebServer.hpp"
#include "GoldbachWebApp.hpp"
#include "QueueSums.hpp"
#include "Queue.hpp"

const char* const usage =
  "Usage: webserv [port] [max_connections]\n"
  "\n"
  "  port             Network port to listen incoming HTTP requests, default "
    DEFAULT_PORT "\n"
  "  max_connections  Maximum number of allowed client connections\n";

typedef struct values{
  int64_t value; // valor
  queue_t* cola_sumas; // cola para guardar las sumas de cada valor
  bool signo; // Para guardar el signo del numero
  int cant_sumas; // La cantidad de sumas
} values_t;


// TODO(Wil) Make WebServer a singleton class. See the Log class
WebServer::WebServer() {
}

WebServer::~WebServer() {
}

WebServer& WebServer::getInstance() {
  static WebServer webServer;
  return webServer;
}
// namespace {
//   volatile sig_atomic_t quitok = false;
//   void handle_break(int a) {
//     if (a == SIGINT){
//       quitok = true;
//       std::cout << "wait to finish " << std::endl;
//     }
//   }
// }
void WebServer::signalHandler(){
  stopHttpServer();
}
int WebServer::start(int argc, char* argv[]) {
  try {
    if (this->analyzeArguments(argc, argv)) {
      // TODO(Wil) Handle signal 2 (SIGINT) and 15 (SIGTERM), see man signal
      // Signal handler should call WebServer::stopListening(), send stop
      // conditions and wait for all secondary threads that it created
      // void (*prev_handler)(int);
      // prev_handler = signal (SIGINT, signalHandler);

      // struct sigaction sigbreak;
      // sigbreak.sa_handler = &handle_break;
      // sigemptyset(&sigbreak.sa_mask);
      // sigbreak.sa_flags = 0;
      // if (sigaction(SIGINT, &sigbreak, NULL) != 0){
      //   std::perror("sigaction");
      // }
      this->listenForConnections(this->port);
      const NetworkAddress& address = this->getNetworkAddress();
      std::cout << "web server listening on " << address.getIP()
        << " port " << address.getPort() << "...\n";
      startHttpServer();
      webApp = new GoldbachWebApp();
      webApp->start_Calculators();
      this->acceptAllConnections();
    }
  } catch (const std::runtime_error& error) {
    std::cerr << "error: " << error.what() << std::endl;
  }
  return EXIT_SUCCESS;
}

bool WebServer::analyzeArguments(int argc, char* argv[]) {
  // Traverse all arguments
  for (int index = 1; index < argc; ++index) {
    const std::string argument = argv[index];
    if (argument.find("help") != std::string::npos) {
      std::cout << usage;
      return false;
    }
  }

  if (argc >= 2) {
    // arg 1 must be port number (8080)
    this->port = argv[1];
    if (sscanf(argv[2], "%zu", &max_connections) != 1 || errno) {
      fprintf(stderr, "error: invalid thread count\n");
    }
  }

  return true;
}

bool WebServer::handleHttpRequest(HttpRequest& httpRequest,
    HttpResponse& httpResponse) {
  // Print IP and port from client
  const NetworkAddress& address = httpRequest.getNetworkAddress();
  std::cout << "connection established with client " << address.getIP()
    << " port " << address.getPort() << std::endl;

  // Print HTTP request
  std::cout << "  " << httpRequest.getMethod()
    << ' ' << httpRequest.getURI()
    << ' ' << httpRequest.getHttpVersion() << std::endl;

  return this->route(httpRequest, httpResponse);
}

bool WebServer::route(HttpRequest& httpRequest, HttpResponse& httpResponse) {
  // If the home page was asked
  if (httpRequest.getMethod() == "GET" && httpRequest.getURI() == "/") {
    return this->serveHomepage(httpRequest, httpResponse);
  }

  // TODO(Sebas): URI can be a multi-value list, e.g: 100,2784,-53,200771728
  
  // TODO(Sebas): change for sendGoldbachSums() if you prefer it
  std::smatch matches;
  bool flag = false;

  // TODO(Sebas): Numbers given by user may be larger than int64_t, reject them

  // If a number was asked in the form "/goldbach/1223"
  // or "/goldbach?number=1223"
  std::cout<<httpRequest.getURI()<< " URI" << std::endl;
  std::regex inQuery("^/goldbach(/|\\?number=)(-?\\d+)$");
  //std::regex inQuery("^/goldbach\\?number=(-?\\d+)$");
  if (std::regex_search(httpRequest.getURI(), matches, inQuery)) {
    flag = true;
    assert(matches.length() >= 3);
    const int64_t number = std::stoll(matches[2]);
    return this->serveGoldbachSums(httpRequest, httpResponse, number,flag);
  }

  std::regex inPath("^/(-?\\d+)$");
  if (std::regex_search(httpRequest.getURI(), matches, inPath)) {
    //assert(matches.length() >= 3);
    const int64_t number = std::stoll(matches[1]);
    return this->serveGoldbachSums(httpRequest, httpResponse, number,flag);
  }

  std::regex multiPath("^/(-?\\d+)((,-?\\d+)*)$");
  if (std::regex_search(httpRequest.getURI(), matches, multiPath)) {
    // assert(matches.length() >= 3);
    const int64_t number = std::stoll(matches[1]);
    std::string s = matches.suffix();
    //std::cout<< s << " suffix" << std::endl;
    //s = matches.prefix();
    //std::cout<< s << " prefix" << std::endl;
    return this->serveGoldbachSums(httpRequest, httpResponse, number,flag);
  }
  // Unrecognized request
  return this->serveNotFound(httpRequest, httpResponse);
}

// TODO(Ardi): Fix code redundancy in the following methods
void WebServer::setHeaders(HttpResponse& httpResponse, std::string title) {
  // Set HTTP response metadata (headers)
  httpResponse.setHeader("Server", "AttoServer v1.0");
  httpResponse.setHeader("Content-type", "text/html; charset=ascii");
  httpResponse.body() << "<!DOCTYPE html>\n"
    << "<html lang=\"en\">\n"
    << "  <meta charset=\"ascii\"/>\n"
    << "  <title>" << title << "</title>\n";
}

bool WebServer::serveHomepage(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;
  // TODO(you) Move form to your view class, e.g GoldbachWebApp

  // Build the body of the response
  std::string title = "Goldbach sums";
  setHeaders(httpResponse, title);

  httpResponse.body() << "  <style>body {font-family: monospace}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <form method=\"get\" action=\"/goldbach\">\n"
    << "    <label for=\"number\">Number</label>\n"
    << "    <input type=\"number\" name=\"number\" required/>\n"
    << "    <button type=\"submit\">Calculate</button>\n"
    << "  </form>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

bool WebServer::serveNotFound(HttpRequest& httpRequest
  , HttpResponse& httpResponse) {
  (void)httpRequest;

  // Set HTTP response metadata (headers)
  httpResponse.setStatusCode(404);

  // Build the body of the response
  std::string title = "Not found";
  setHeaders(httpResponse, title);
  httpResponse.body() << "  <style>body {font-family: monospace} h1 {color: green}</style>\n"
    << "  <h1>" << title << "</h1>\n"
    << "  <p>The requested resouce was not found in this server.</p>\n"
    << "  <hr><p><a href=\"/\">Homepage</a></p>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}

// TODO(you) Move domain-logic from WebServer controller to a view class
// e.g GoldbachWebApp, and a model class e.g GoldbachCalculator
bool WebServer::serveGoldbachSums(HttpRequest& httpRequest
    , HttpResponse& httpResponse, int64_t number, bool inQuery) {
  (void)httpRequest;

  // Build the body of the response
  std::string title = "Goldbach sums for " + std::to_string(number);
  // Set HTTP response metadata (headers)
  setHeaders(httpResponse,title);
  //GoldbachWebApp* webApp;
  //webApp = new GoldbachWebApp();
  values_t* values;

  if(inQuery){
    std::string queryNumber = std::to_string(number);
    //llamar a process_request
    webApp->process_Request("/" + queryNumber);
  }
  else{
    webApp->process_Request(httpRequest.getURI());
  }    
  httpResponse.body() << "  <style>body {font-family: monospace} .err {color: red}</style>\n"
    << "  <h1>" << title << "</h1>\n";
  for(int i = 0; i < 3; i++){
    if(values[i].value>=-5 && values[i].value<=5) {
      httpResponse.body() << "  <h2 class=\"err\">"<< values[i].value <<"</h2>\n"
        << "  <p>"<< values[i].value <<": NA</p>\n";
    }
    else{
      if(values[i].value>5) {
        httpResponse.body() << "  <h2>"<< values[i].value <<"</h2>\n"
        << "  <p>"<< values[i].value <<": "<< values[i].cant_sumas <<" sums</p>\n";
      }
      else{
        int64_t sumandoUno,sumandoDos,sumandoTres = 0;
        httpResponse.body() << "  <h2>"<< values[i].value <<"</h2>\n"
          << "  <p>"<< values[i].value <<": "<< values[i].cant_sumas <<" sums</p>\n"
          << "  <ol>\n";
        if((values[i].value%2)==0){
          for(int j = 0; j < values[i].cant_sumas; j++){
            queue_dequeue(values[i].cola_sumas,&sumandoUno);
            queue_dequeue(values[i].cola_sumas,&sumandoDos);
            httpResponse.body() << "    <li>"<< sumandoUno <<" + "<< sumandoDos <<"</li>\n";
          }
          httpResponse.body()<< "  </ol>\n";
        }
        else{
          for(int j = 0; j < values[i].cant_sumas; j++){
            queue_dequeue(values[i].cola_sumas,&sumandoUno);
            queue_dequeue(values[i].cola_sumas,&sumandoDos);
            queue_dequeue(values[i].cola_sumas,&sumandoTres);
            httpResponse.body() << "    <li>"<< sumandoUno <<
            " + "<< sumandoDos <<" + "<< sumandoTres <<"</li>\n";
          }
          httpResponse.body()<< "  </ol>\n";
        }
      }
    }
  }
  httpResponse.body() << "  <hr><p><a href=\"/\">Back</a></p>\n"
    << "</html>\n";

  // Send the response to the client (user agent)
  return httpResponse.send();
}
