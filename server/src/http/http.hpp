#ifndef HTTP_HPP
#define HTTP_HPP

#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "routes.hpp"

namespace webserver {

    void initHTTPServer();
    
}


#endif // HTTP_HPP