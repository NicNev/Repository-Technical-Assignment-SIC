#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHT22PIN 13

DHT dht(DHT22PIN, DHT22);

const char* ssid = "Mzm231";
const char* password = "Nevchris";
const char* serverName = "http://192.168.1.100:5000/sensor-data";

void setup() {
  Serial.begin(115200);
  delay(10);

  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected to WiFi");

  dht.begin();
}

void loop(){
  delay(3000);

  float temp = dht.readTemperature();

  if(isnan(temp)){
    Serial.println("Failed to read temperature");
    return;
  }
  
  if(WiFi.status() == WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName);

    http.addHeader("Content-Type", "application/json");
    String data = "{\"temperature\": " + String(temp) + "}";
    int response = http.POST(data);

    if (response > 0) {
      String response = http.getString();
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(response);
    }

    http.end();
  }else {
    Serial.println("Error in WiFi connection");
  }
}