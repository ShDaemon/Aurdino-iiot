#include <WiFi.h>

const char* ssid = "Merlin";
const char* password = "2444*****";

WiFiServer server(80);

// Define LED GPIOs
const int led1 = 26;
const int led2 = 27;
const int led3 = 25;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }

    Serial.println("Connected to WiFi!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());

    server.begin();

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);
    pinMode(led3, OUTPUT);
}

void loop() {
    WiFiClient client = server.available();
    if (!client) return;

    Serial.println("New Client Connected!");
    String request = "";
    while (client.connected()) {
        if (client.available()) {
            char c = client.read();
            request += c;
            if (c == '\n' && request.endsWith("\r\n\r\n")) break;
        }
    }

    if (request.indexOf("/led1/on") != -1) {
        digitalWrite(led1, HIGH);
    } else if (request.indexOf("/led1/off") != -1) {
        digitalWrite(led1, LOW);
    } else if (request.indexOf("/led2/on") != -1) {
        digitalWrite(led2, HIGH);
    } else if (request.indexOf("/led2/off") != -1) {
        digitalWrite(led2, LOW);
    }  else if (request.indexOf("/led3/on") != -1) {
        digitalWrite(led3, HIGH);
    } else if (request.indexOf("/led3/off") != -1) {
        digitalWrite(led3, LOW);
    }

    // HTML Response
    client.println("HTTP/1.1 200 OK");
    client.println("Content-type:text/html");
    client.println();
    client.println("<html><body>");
    client.println("<h1>ESP32 LED Control</h1>");
    client.println("<button onclick=\"location.href='/led1/on'\">LED 1 ON</button>");
    client.println("<button onclick=\"location.href='/led1/off'\">LED 1 OFF</button>");
    client.println("<button onclick=\"location.href='/led2/on'\">LED 2 ON</button>");
    client.println("<button onclick=\"location.href='/led2/off'\">LED 2 OFF</button>");
    client.println("<button onclick=\"location.href='/led3/on'\">LED 3 ON</button>");
    client.println("<button onclick=\"location.href='/led3/off'\">LED 3 OFF</button>");
    client.println("</body></html>");
    client.println();

    delay(1);
    client.stop();
    Serial.println("Client Disconnected");
}
