#include <WiFi.h>
#include "PayloadEncoder.h"
#include "Client.h"
#include "AccessPoint.h"

char *ssid = "ssid";
char *password = "password";
smc::AccessPoint ap;

void setup() {
	Serial.begin(115200);

	while(!Serial) delay(0);
	delay(4000);   // Delay needed before calling the WiFi.begin

	WiFi.begin(ssid, password);

	while (WiFi.status() != WL_CONNECTED) { //Check for the connection
		delay(1000);
		Serial.println("Connecting to WiFi..");
	}

	Serial.println("Connected to the WiFi network");
	Serial.println(WiFi.localIP());

	ap.begin(); // Importante dar o begin do access point no setup antes de qualquer ação com ele 
}

void loop() {
	// Preenchendo momento em que o evento aconteceu
	smc::Moment moment;
	moment.hour = 10;
	moment.minute = 20;
	moment.day = 10;
	moment.month = 10;
	moment.year = 2018;

	// Preenchendo informações sobre o alarme
	smc::AlarmInfo alarmInfo;
	alarmInfo.start.hour = 10;
	alarmInfo.start.minute = 13;
	alarmInfo.period.hour = 11;
	alarmInfo.period.minute = 12;
	alarmInfo.duration = 15; // Em dias

	// Preenchendo informações extra
	int id_cup = 1; // Número único que identifica um copo
	int partition = 2; // Compartimento em que o remédio foi inserido
	char event[] = "registered"; // Nome do evento que aconteceu, pode ser: taken, not_taken, registered ou removed

	// Preparando e enviando requisição
	smc::Client client;
	smc::PayloadEncoder payload(id_cup, partition, moment, "registered", alarmInfo);
	client.sendRequest(payload);

	// Modo AP
	ap.handle_request(); // Deixar isso aqui rodando no loop sempre

	delay(20*1000); // Não tem relevância
}
