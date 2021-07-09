#include <ESP8266WiFi.h>

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>

enum class STATE : int { OPEN = 1, CLOSED = 0 };
enum class RELAY : int { D6_OPEN = 12, D7_CLOSE = 13 };

STATE CONTROLLER_STATE = STATE::CLOSED;

struct NETWORK_CONFIG {
  const char*  ssid       = "locky";
  // network ssid
  const char*  password   = "supersecretpassword2000";
  //  network password
  const char*  authtoken = "supersecretappauthtoken3000";
  // security password for interact with server.
  // Password at this moment is hardcoded, You can change it only in source code.

  const int channel = 12;
  const int ssid_hidden = 1; // the network name is not broadcasting.
  const int max_connection = 4; // max connections for ap server, default 4.

} NETWORK_CONFIG;

AsyncWebServer server(5000);

bool isValidAuthToken( const String token );
void setRelaysState( const RELAY relay_pin, const int o_state = 0 );
template < std::size_t Size >
bool in_array( const String& value, const String( &array )[ Size ] );


void initHTTPServer() {
  Serial.print("[HTTP] start listening on: ");
  Serial.println(WiFi.softAPIP());

  server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", "/");
    return;
  });

  // deprecated
  // server.on("/doors/open", HTTP_GET, [] (AsyncWebServerRequest *request) {

  //   if(CONTROLLER_STATE == STATE::OPEN) {
  //     request -> send_P(200, "text/plain", "{\"message\": \"already open\"}");
  //     return;
  //   }

  //   if(request -> hasParam("authtoken")) {
  //     const String authtoken = request -> getParam("authtoken") -> value();

  //     if (isValidAuthToken(authtoken)) {

  //         // setRelaysState(RELAY::D6_OPEN, HIGH);
  //         request -> send_P(200, "text/plain", "{\"message\": \"opened\"}");
  //         return;

  //       } else {
  //         request -> send_P(4001, "text/plain", "{\"message\": \"you dont have permissions to this site\"}");
  //         return;
  //       }

  //       request -> send_P(401, "text/plain", "{\"message\": \"incorrect password\"}");
  //       return;

  //     } else {
  //       request -> send_P(4001, "text/plain", "{\"message\": \"bad auth token\"}");
  //       return;
  //     }

  //     request -> send_P(500, "text/plain", "{\"message\": \"unexpected error, contact with software developer\"}");
  // });

  // deprecated
  // server.on("/doors/close", HTTP_GET, [] (AsyncWebServerRequest *request) {

  //   if(CONTROLLER_STATE == STATE::CLOSED) {
  //     request -> send_P(200, "text/plain", "{\"message\": \"already closed\"}");
  //     return;
  //   }

  //   if(request -> hasParam("authtoken")) {
  //     const String authtoken = request -> getParam("authtoken") -> value();

  //     if (isValidAuthToken(authtoken)) {

  //         // setRelaysState(RELAY::D6_CLOSE, HIGH);
  //         request -> send_P(200, "text/plain", "{\"message\": \"closed\"}");
  //         return;

  //       } else {
  //         request -> send_P(4001, "text/plain", "{\"message\": \"you dont have permissions to this site\"}");
  //         return;
  //       }

  //       request -> send_P(401, "text/plain", "{\"message\": \"incorrect password\"}");
  //       return;

  //     } else {
  //       request -> send_P(4001, "text/plain", "{\"message\": \"bad auth token\"}");
  //       return;
  //     }

  //     request -> send_P(500, "text/plain", "{\"message\": \"unexpected error, contact with software developer\"}");
  // });

  server.on( "/doors/interact", HTTP_GET, [] ( AsyncWebServerRequest *request ) {

    if( request -> hasParam( "authtoken" ) ) {
      const String authtoken = request -> getParam( "authtoken" ) -> value();

      if( !isValidAuthToken( authtoken ) ) {
        request -> send_P(422, "text/plain", "{\"detail\": \"auth parameter is required\"}");
        return;
      }

      if( request -> hasParam( "action" ) ) {
        const String action_param = request -> getParam( "action" ) -> value();
        const String acceptableActions[] = { "open", "close" };

        if( in_array( action_param, acceptableActions ) ) {

          if( action_param == acceptableActions[0] ) {

            setRelaysState( RELAY::D6_OPEN, HIGH );
            request -> send_P( 200, "text/plain", "{\"detail\": \"closed\"}" );
            return;

          } else if( action_param == acceptableActions[1] ) {

            setRelaysState( RELAY::D7_CLOSE, HIGH );
            request -> send_P(200, "text/plain", "{\"detail\": \"opened\"}");
            return;

          }


        } else {
          request -> send_P( 422, "text/plain", "{\"detail\": \"unexpected parameters\"}" );
          return;
        }

      } else {
        request -> send_P( 401, "text/plain", "{\"detail\": \"incorrect password\"}" );
        return;
      }


    } else {
      request -> send_P( 401, "text/plain", "{\"detail\": \"you don't have permissions to this site\"}" );
      return;
     }
  });

  
  server.begin();
  
}
 

void setup() {
  // setup pin for open and close
  pinMode( LED_BUILTIN, OUTPUT );
  pinMode( static_cast<int>( RELAY::D6_OPEN ), OUTPUT );
  pinMode( static_cast<int>( RELAY::D7_CLOSE ), OUTPUT );
  Serial.begin( 9600 );

  digitalWrite( LED_BUILTIN, HIGH) ;

  // run access point
  WiFi.mode( WIFI_STA );
  WiFi.disconnect();
  delay( 100 );

  WiFi.softAP(
              NETWORK_CONFIG.ssid, 
              NETWORK_CONFIG.password, 
              NETWORK_CONFIG.channel,
              NETWORK_CONFIG.ssid_hidden, 
              NETWORK_CONFIG.max_connection
              );

  // start webserver
  initHTTPServer();
}


void loop() {

}

template < std::size_t Size >
bool in_array( const String& value, const String( &array )[ Size ] ) {
  for( const auto& arr : array ) {
    if( arr == value ) {
      return true;
    }
  }
  return false;
}

bool isValidAuthToken( const String token ) {
  return ( token == NETWORK_CONFIG.authtoken );
}


void setRelaysState( const RELAY relay_pin, const int o_state )  {
    RELAY opposite = RELAY::D6_OPEN;
    CONTROLLER_STATE = STATE::CLOSED;

    if( relay_pin != RELAY::D7_CLOSE ) {
      opposite = RELAY::D7_CLOSE;
      CONTROLLER_STATE = STATE::OPEN;
    }
    
    digitalWrite( static_cast<int>( relay_pin ), o_state );
    digitalWrite( static_cast<int>( opposite ), !o_state );
    delay(1000);
    digitalWrite( static_cast<int>( relay_pin ), !o_state );
}