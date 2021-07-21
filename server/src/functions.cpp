#include "functions.hpp"

struct NETWORK_CONFIG NETWORK_CONFIG;

bool isValidAuthToken( const String token ) noexcept {
  return ( token == NETWORK_CONFIG.authtoken );
}


void setRelaysState( const RELAY relay_pin, const int o_state) noexcept {
    RELAY opposite = RELAY::D6_OPEN;
    CONTROLLER_STATE = STATE::CLOSED;

    if( relay_pin != RELAY::D7_CLOSE ) {
      opposite = RELAY::D7_CLOSE;
      CONTROLLER_STATE = STATE::OPEN;
    }

    Serial.println(o_state);
    Serial.println( static_cast<int>( opposite ) );
    Serial.println( static_cast<int>( relay_pin )) ;
    
    digitalWrite( static_cast<int>( relay_pin ), o_state );
    digitalWrite( static_cast<int>( opposite ), !o_state );
    delayMicroseconds( 999999 );
    digitalWrite( static_cast<int>( relay_pin ), !o_state );
}