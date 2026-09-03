#include <WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <LoRa.h>
#include <ArduinoJson.h>

// Credenciales WiFi
const char* ssid = "ARRIS-4616";
const char* password = "2WC468400231";

// Configuración Broker MQTT
const char* mqtt_server = "broker.hivemq.com"; // Broker público
const int mqtt_port = 1883;
const char* mqtt_topic = "ucol/telematica/lora/equipo1";

// Definición de pines LoRa para ESP32
#define SCK 18
#define MISO 19
#define MOSI 23
#define SS 5
#define RST 14
#define DIO0 26

#define LORA_BAND 433E6

WiFiClient espClient;
PubSubClient client(espClient);

void setupWiFi() {
  delay(10);
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado. IP: ");
  Serial.println(WiFi.localIP());
}

void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Conectando a broker MQTT...");
    String clientId = "ESP32Gateway-";
    clientId += String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("Conectado.");
    } else {
      Serial.print("Fallo, rc=");
      Serial.print(client.state());
      Serial.println(" Reintentando en 5 segundos...");
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  setupWiFi();

  client.setServer(mqtt_server, mqtt_port);

  SPI.begin(SCK, MISO, MOSI, SS);
  LoRa.setPins(SS, RST, DIO0);

  if (!LoRa.begin(LORA_BAND)) {
    Serial.println("Fallo al iniciar LoRa en Gateway.");
    while (1);
  }

  Serial.println("Gateway LoRa -> MQTT Iniciado.");
}

void loop() {
  if (!client.connected()) {
    reconnectMQTT();
  }
  client.loop();

  // Verificar si hay paquetes LoRa entrantes
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    String incomingPayload = "";
    while (LoRa.available()) {
      incomingPayload += (char)LoRa.read();
    }

    int rssi = LoRa.packetRssi();
    Serial.print("Paquete recibido: ");
    Serial.print(incomingPayload);
    Serial.print(" | RSSI: ");
    Serial.println(rssi);

    // Procesar e inyectar RSSI
    StaticJsonDocument<256> doc;
    DeserializationError error = deserializeJson(doc, incomingPayload);

    if (!error) {
      doc["RSSI"] = rssi;

      String finalPayload;
      serializeJson(doc, finalPayload);

      // Publicar a MQTT
      client.publish(mqtt_topic, finalPayload.c_str());
      Serial.print("Publicado a MQTT: ");
      Serial.println(finalPayload);
    } else {
      Serial.println("Error parseando JSON recibido.");
    }
  }
}
