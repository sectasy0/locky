#ifndef ROUTES_HPP
#define ROUTES_HPP

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "../functions.hpp"
#include "../settings.hpp"

namespace webserver {

    namespace routes {

        void handleHome( AsyncWebServerRequest *request );
        void interact( AsyncWebServerRequest *request );
        
    }
}

#endif // ROUTES_HPP