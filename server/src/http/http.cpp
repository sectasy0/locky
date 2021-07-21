#include "http.hpp"

namespace webserver {

  AsyncWebServer server(5000);

  void initHTTPServer() {
    Serial.print("[HTTP] start listening on: ");
    Serial.println(WiFi.softAPIP());

    server.on("/", HTTP_GET, routes::handleHome );
    server.on( "/doors/interact", HTTP_GET, routes::interact );

    server.begin();
  }
  
}

