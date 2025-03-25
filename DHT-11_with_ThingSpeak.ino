#include <WiFi.h>
#include <DHT.h>
#include <ThingSpeak.h>

DHT dht(32, DHT11);

WiFiClient client;
long myChannelNumber =    2891***;           //Enter channel number
const char myWriteAPIKey[] = "XZ80DGYQHT******";    //Enter API Key

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.begin("Merlin", "2444*****");  // “Wifi name”, “Password” 
  while(WiFi.status() != WL_CONNECTED)
  {
    delay(200);
    Serial.print("..");
  }
  Serial.println();
  Serial.println("NodeMCU is connected!");
  Serial.println(WiFi.localIP());
  dht.begin();
  ThingSpeak.begin(client);
}

void loop() {
  // put your main code here, to run repeatedly:
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println("Temperature: " + (String) t);
  Serial.println("Humidity: " + (String) h);
  if ()
  ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);
  ThingSpeak.writeField(myChannelNumber, 2, h, myWriteAPIKey);
  delay(2000);
}
