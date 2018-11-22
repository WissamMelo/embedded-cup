#ifndef CLIENT_H_
#define CLIENT_H_

#include <HTTPClient.h>
#include "PayloadEncoder.h"

const char * ssid = "SSID";
const char * password = "password";

namespace smc {
	class Client {
		public:
			Client(){
				destHost = "http://host:port/create/";

				http.begin(destHost);
				http.addHeader("Content-Type", "application/json");
			}
			~Client(){
				http.end();
			}
			int makeRequest(PayloadEncoder payload){
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
			String destHost;

			HTTPClient http;
	};
}

#endif  // CLIENT_H_
