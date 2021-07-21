#include "http.hpp"

namespace webserver {

    namespace routes {

        void handleHome( AsyncWebServerRequest *request ) {
            Serial.print("request / ");
            request -> send_P(200, "text/plain", "/");
            return;
        }

        void interact( AsyncWebServerRequest *request ) {

            if( request -> hasParam( "authtoken" ) ) {
                const String authtoken = request -> getParam( "authtoken" ) -> value();

                if( !isValidAuthToken( authtoken ) ) {
                    request -> send_P(401, "text/plain", "{\"message\": \"bad auth token\"}");
                    return;
                }

                if( request -> hasParam( "action" ) ) {
                    const String action_param = request -> getParam( "action" ) -> value();
                    const String acceptableActions[] = { "open", "close" };

                    if( in_array( action_param, acceptableActions ) ) {

                        if( action_param == acceptableActions[0] ) {

                            setRelaysState( RELAY::D6_OPEN, LOW );
                            request -> send_P( 200, "text/plain", "{\"message\": \"opened\"}" );
                            return;

                        } else if( action_param == acceptableActions[1] ) {

                            setRelaysState( RELAY::D7_CLOSE, LOW );
                            request -> send_P(200, "text/plain", "{\"message\": \"closed\"}");
                            return;

                        }


                    } else {
                        request -> send_P( 400, "text/plain", "{\"message\": \"unexpected parameters\"}" );
                        return;
                    }

                } else {
                    request -> send_P( 401, "text/plain", "{\"message\": \"incorrect password\"}" );
                    return;
                }


            } else {
                request -> send_P( 401, "text/plain", "{\"message\": \"you don't have permissions to this site\"}" );
                return;
            }
        }

        

    }


}