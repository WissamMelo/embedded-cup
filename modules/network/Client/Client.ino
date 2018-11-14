#include <WiFi.h>
#include <HTTPClient.h>
const char * ssid = "SSID";
const char * password = "password";

namespace smc {
	class Client {
		public:
			Client(){
				destHost = "http://host:port/create/";

				http.begin(destHost); //Specify destination for HTTP request
				http.addHeader("Content-Type", "application/json");
			}
			~Client(){
				http.end();  //Free resources
			}
			int makeRequest(String payload){
				int httpResponseCode = http.POST(payload); //Send the actual POST request

				if(httpResponseCode > 0){
					String response = http.getString();  //Get the response to the request
					Serial.println(httpResponseCode);   //Print return code
					Serial.println(response);           //Print request answer
				}else{
					Serial.print("Error on sending POST: ");
					Serial.println(httpResponseCode);
				}

				return httpResponseCode;
			}

		private:
			String destHost;

			HTTPClient http;
	};
}

void setup() {
	Serial.begin(115200);
	delay(4000);   //Delay needed before calling the WiFi.begin

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) { //Check for the connection
		delay(1000);
		Serial.println("Connecting to WiFi..");
	}
	Serial.println("Connected to the WiFi network");
}

void loop() {
	smc::Client client;
	client.makeRequest("{\"slot\": \"10\", \"event\": \"nao tomou\"}");
	delay(60*1000);
}
