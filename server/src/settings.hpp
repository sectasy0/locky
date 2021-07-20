
#ifndef SETTINGS_HPP
#define SETTINGS_HPP

enum class STATE : int { OPEN = 1, CLOSED = 0 };
enum class RELAY : int { D6_OPEN = 12, D7_CLOSE = 13 };

struct NETWORK_CONFIG {
  const char*  ssid       = "locky";
  // network ssid
  const char*  password   = "wiadomoktowiadomokogowiadomoco";
  //  network password
  const char*  authtoken = "1234";
  // security password for interact with server.
  // Password at this moment is hardcoded, You can change it only in source code.

  const int channel = 12;
  const int ssid_hidden = 0; // the network name is not broadcasting.
  const int max_connection = 4; // max connections for ap server, default 4.

};

extern struct NETWORK_CONFIG NETWORK_CONFIG;
extern STATE CONTROLLER_STATE;

#endif //SETTINGS_HPP