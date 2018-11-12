#include <WiFi.h>
#include <FS.h>
#include <SPIFFS.h>
#include <map>

namespace smc {
    class AccessPoint {
    public:
        AccessPoint() {
        }

        void begin() {
            begin_soft_ap();
            read_html_file();
        }

        void end() {
            end_soft_ap();
        }

        std::map<String, String> handle_request() {
            WiFiClient client = server.available();
            std::map<String, String> credentials;
            if(client) {
                Serial.println("New client connected.");
                String current_line = "";
                String header = "";
                while(client.connected()) {
                    if(client.available()) {
                        char c = client.read();
                        header += c;
                        if(c == '\n') {
                            if(current_line.length() == 0) {
                                client.println("HTTP/1.1 200 OK");
                                client.println("Content-type:text/html");
                                client.println("Connection: close");
                                client.println();
                                client.println(html_page);
                                client.println();
                                credentials = handle_header(header);
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
            return credentials;
        }

    private:
        WiFiServer server;
        String html_page;

        void begin_soft_ap() {
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

        void end_soft_ap() {
            if(WiFi.softAPdisconnect(true)) {
                Serial.println("Wifi soft AP disconnected successfully.");
            }
            else {
                Serial.println("Wifi soft AP could not disconnect.");
            }
            server.end();
            Serial.println("AP server ended.");
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

        std::map<String, String> handle_header(String header) const {
            Serial.println("Handling header...");
            Serial.println(header);

            const int SSID_SLENGTH = 6;
            int ssid_index = std::max(header.indexOf("?SSID"), header.indexOf("&SSID"));
            String ssid = "";
            for(int i = ssid_index + SSID_SLENGTH; header[i] != '&' && header[i] != ' '; i++) {
                ssid += header[i];
            }

            const int PASS_SLENGTH = 10;
            int pass_index = std::max(header.indexOf("?password"), header.indexOf("&password"));
            String password = "";
            for(int i = pass_index + PASS_SLENGTH; header[i] != '&' && header[i] != ' '; i++) {
                password += header[i];
            }

            std::map<String, String> credentials;
            credentials["ssid"] = ssid;
            credentials["password"] = password;

            return credentials;
        }
    };
}

smc::AccessPoint ap;

void handle_new_credentials(std::map<String, String> credentials) {
    Serial.println("Handling new credentials...");
    ap.end();
    Serial.println("ssid: " + credentials["ssid"]);
    Serial.println("password: " + credentials["password"]);

    // try to connect with new credentials on wifi here
    // in case of success, store credentials in wifi_credentials.txt file.
    WiFi.begin(credentials["ssid"], credentials["password"]);
    int tries = 0;
    while(WiFi.status() != WL_CONNECTED && tries < 10) {
        delay(1000);
        tries++;
        Serial.println("Connecting to wifi with new credentials...");
    }

    if(WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected successfully to wifi with new credentials.");
        // record credentials in file here.
    }
    else {
        Serial.println("Could not connect to wifi with new credentials.");
    }
}

void setup() {
    Serial.begin(115200);
    ap.begin();
}

void loop() {
    std::map<String, String> credentials = ap.handle_request();
    if(!credentials.empty()) {
        handle_new_credentials(credentials);
    }
}
