#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>

class AccessPoint {
public:
    AccessPoint() {
    }

    void begin() {
        start_soft_ap();
        read_html_file();
    }

    void handle_request() {
        WiFiClient client = server.available();
        if(client) {
            Serial.println("New client connected.");
            String current_line = "";
            String header = "";
            while(client.connected()) {
                if(client.available()) {
                    char c = client.read();
                    Serial.write(c);
                    header += c;
                    if(c == '\n') {
                        if(current_line.length() == 0) {
                            client.println("HTTP/1.1 200 OK");
                            client.println("Content-type:text/html");
                            client.println("Connection: close");
                            client.println();
                            client.println(html_page);
                            client.println();
                            handle_header(header);
                            break;
                        }
                        else {
                            current_line = "";
                        }
                    }
                    else if (c != '\r') {
                        current_line += c;
                    }
                }
            }
            header = "";
            client.stop();
            Serial.println("Client disconnected.");
            Serial.println("");
        }
    }

private:
    WiFiServer server;
    String html_page;

    void start_soft_ap() {
        server = WiFiServer(80);
        const static char* ssid = "SMC-AP";
        const static char* password = "123456789";
        if(WiFi.softAP(ssid, password)) {
            Serial.print("Wifi soft AP started successfully. Access it in ");
            Serial.println(WiFi.softAPIP());
        }
        else {
            Serial.println("Wifi soft AP start failed.");
        }
        server.begin();
    }

    void read_html_file() {
        if(SPIFFS.begin()) {
            Serial.println("Card mounted successfully.");
        }
        else {
            Serial.println("Card mount failed.");
        }
        File html_file = SPIFFS.open("/index.html");
        if(html_file) {
            while(html_file.available()) {
                html_page += char(html_file.read());
            }
            Serial.println("HTML page read successfully.");
            html_file.close();
        }
        else {
            Serial.println("Could not open index file.");
        }
    }

    void handle_header(String header) const {
        Serial.println("Handling header...");
        Serial.println(header);
    }
};

AccessPoint ap;

void setup() {
    Serial.begin(115200);
    ap.begin();
}

void loop() {
    ap.handle_request();
}
