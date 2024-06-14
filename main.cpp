#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "router";
const char* pass = "1234";
const char* user_email = "user@gmail.com";
const char* user_pass = "password";
const char* user_server = "mqtt.beia-telemetrie.ro";

WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  delay(100);
  Serial.println("\nConnecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print("-");
  }
  Serial.println("\nConnected to ");
  Serial.println(ssid);
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("\nConnecting again to ");
    Serial.println(user_server);
    if (client.connect("router", user_email, user_pass)) {
      Serial.print("\nConnected to ");
      Serial.println(user_server);
    } else {
      Serial.println("\nTrying to connect again...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setupWiFi();
  client.setServer(user_server, 1883);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
