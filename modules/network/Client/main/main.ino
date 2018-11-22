#include <WiFi.h>
#include "PayloadEncoder.h"
#include "Client.h"

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
	smc::Moment moment;
	moment.hour = 10;
	moment.minute = 20;
	moment.day = 10;
	moment.month = 10;
	moment.year = 2018;

	smc::AlarmInfo alarmInfo;
	alarmInfo.start.hour = 10;
	alarmInfo.start.minute = 13;
	alarmInfo.period.hour = 11;
	alarmInfo.period.minute = 12;


	smc::Client client;
	smc::PayloadEncoder payload(1, 2, moment, "registered", alarmInfo);
	client.makeRequest(payload);

	delay(20*1000);
}
