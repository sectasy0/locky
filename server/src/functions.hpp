
#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include "settings.hpp"
#include "Arduino.h"

bool isValidAuthToken( const String token );
void setRelaysState( const RELAY relay_pin, const int o_state = 0 );

template <std::size_t Size>
bool in_array( const String& value, const String(&array)[Size] ) {
  for( const auto& arr : array ) {
    if( arr == value ) {
      return true;
    }
  }
  return false;
}

#endif //FUNCTIONS_HPP
