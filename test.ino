#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {
  delay(2000);

  float tempC = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(tempC) || isnan(humidity)) {
    Serial.println("Error reading DHT sensor!");
  } else {
    Serial.print("Temperature: ");
    Serial.print(tempC);
    Serial.print(" °C, Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");
  }
}


/*
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <DHT.h>
#include <InfluxDbClient.h>
#include <InfluxDbCloud.h>

#define WIFI_SSID "WIFIname"
#define WIFI_PASSWORD "WIFIpass"

#define INFLUXDB_URL "https://eu-central-1-1.aws.cloud2.influxdata.com"
#define INFLUXDB_TOKEN "DQiOAwRxA4mM2DZRc6OHhWGQDH17jEpdrXvRtcbPjwgrUnwU86eLxvnIQCsSAYJy811dQgiMcKU_w9coMHaVew=="
#define INFLUXDB_ORG "e43d6a61fffd1b09"
#define INFLUXDB_BUCKET "BUCKET"

#define TZ_INFO "UTC3"

#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

const char* mqtt_server = "mqtt.beia-telemetrie.ro";
const char* mqtt_topic = "/training/device/George-Daniel-Giba/";

WiFiClient espClient;
PubSubClient mqttClient(espClient);

InfluxDBClient influxClient(INFLUXDB_URL, INFLUXDB_ORG, INFLUXDB_BUCKET, INFLUXDB_TOKEN, InfluxDbCloud2CACert);

Point sensor("sensor_data");

void setup() {
  Serial.begin(115200);
  dht.begin();
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(100);
  }

  mqttClient.setServer(mqtt_server, 1883);
  reconnectMQTT();

  timeSync(TZ_INFO, "pool.ntp.org", "time.nis.gov");

  if (influxClient.validateConnection()) {
    Serial.println(influxClient.getServerUrl());
  } else {
    Serial.println(influxClient.getLastErrorMessage());
  }
}

void loop() {
  if (!mqttClient.connected()) {
    reconnectMQTT();
  }
  mqttClient.loop();

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)) {
    return;
  }

  sendToMQTT(temperature, humidity);
  sendToInfluxDB(temperature, humidity);

  delay(60000);
}

void reconnectMQTT() {
  while (!mqttClient.connected()) {
    if (mqttClient.connect("ESP8266Client")) {
      mqttClient.subscribe(mqtt_topic);
    } else {
      delay(5000);
    }
  }
}

void sendToMQTT(float temperature, float humidity) {
  String payload = String("{\"temperature\":") + temperature + ",\"humidity\":" + humidity + "}";
  mqttClient.publish(mqtt_topic, payload.c_str());
}

void sendToInfluxDB(float temperature, float humidity) {
  sensor.clearFields();
  sensor.addField("temperature", temperature);
  sensor.addField("humidity", humidity);

  if (WiFi.status() != WL_CONNECTED) {
    return;
  }

  if (!influxClient.writePoint(sensor)) {
    Serial.println(influxClient.getLastErrorMessage());
  }
}

*/
