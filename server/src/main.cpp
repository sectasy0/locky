#include <ESP8266WiFi.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

#include "http/http.hpp"

void setup() {
  pinMode( static_cast<int>( RELAY::D6_OPEN ), OUTPUT );
  pinMode( static_cast<int>( RELAY::D7_CLOSE ), OUTPUT );
  Serial.begin( 9600 );

  digitalWrite( static_cast<int>( RELAY::D6_OPEN ), HIGH );
  digitalWrite( static_cast<int>( RELAY::D7_CLOSE ), HIGH );

  WiFi.mode( WIFI_STA );
  WiFi.disconnect();
  delay( 100 );

  WiFi.softAP(NETWORK_CONFIG.ssid, 
              NETWORK_CONFIG.password, 
              NETWORK_CONFIG.channel,
              NETWORK_CONFIG.ssid_hidden, 
              NETWORK_CONFIG.max_connection
              );

  initHTTPServer();
}

void loop() {

}