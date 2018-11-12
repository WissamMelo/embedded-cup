#include <WiFi.h>
#include <HTTPClient.h>

const char * ssid = "LadesConvidado";
const char * password = "bemvindoconvidado";

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
	HTTPClient http;
	http.begin("http://172.16.1.105:9000/posts"); //Specify destination for HTTP request
	http.addHeader("Content-Type", "application/json");
	int httpResponseCode = http.POST("{\"slot\": \"10\", \"event\": \"nao tomou\"}"); //Send the actual POST request

	if(httpResponseCode > 0){
		String response = http.getString();  //Get the response to the request

		Serial.println(httpResponseCode);   //Print return code
		Serial.println(response);           //Print request answer
	}else{
		Serial.print("Error on sending POST: ");
		Serial.println(httpResponseCode);

	}
	http.end();  //Free resources
	delay(60*1000);  //Send a request every 10 seconds
}
