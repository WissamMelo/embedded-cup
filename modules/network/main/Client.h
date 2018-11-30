#ifndef CLIENT_H_
#define CLIENT_H_

#include <HTTPClient.h>
#include "PayloadEncoder.h"

namespace smc {
    const String dest_host = "https://smartmedicinecup.herokuapp.com/api/info/";

    class Client {
        public:
            Client(){
                http.begin(dest_host);
                http.addHeader("Content-Type", "application/json");
            }
            ~Client(){
                http.end();
            }

            int sendRequest(PayloadEncoder payload, String url=dest_host){
                String payloadStr = payload.encode();
                int httpResponseCode = http.POST(payloadStr);

                if(httpResponseCode > 0){
                    String response = http.getString();
                    Serial.println(httpResponseCode);
                    Serial.println(response);
                }else{
                    Serial.print("[ERROR] POST request returned an error: ");
                    Serial.println(httpResponseCode);
                }

                return httpResponseCode;
            }

        private:
            HTTPClient http;
    };
}

#endif  // CLIENT_H_
