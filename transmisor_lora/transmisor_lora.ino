#include <SPI.h>
#include <LoRa.h>
#include <ArduinoJson.h>

// Definición de pines para Arduino UNO
const int csPin = 10;
const int resetPin = 9;
const int irqPin = 2;
const int buttonPin = 4; // Cambiado al Pin 4

// Cambia las iniciales por las de tu equipo
const char* INITIALS = "EQ-01"; 

#define LORA_BAND 433E6 // Cambiar a 915E6 si tus módulos son de esa frecuencia

int counter = 0;
bool lastButtonState = HIGH;

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);

  LoRa.setPins(csPin, resetPin, irqPin);

  if (!LoRa.begin(LORA_BAND)) {
    Serial.println("Error iniciando LoRa. Revisa las conexiones.");
    while (1);
  }

  // Configuración de parámetros LoRa
  LoRa.setSpreadingFactor(7);
  LoRa.setSignalBandwidth(125E3);
  LoRa.setCodingRate4(5);
  LoRa.setTxPower(14);

  Serial.println("Nodo Transmisor LoRa Listo. Presiona el boton.");
}

void loop() {
  bool currentButtonState = digitalRead(buttonPin);

  // Detecta el momento exacto en que se presiona el botón (Transición de HIGH a LOW)
  if (lastButtonState == HIGH && currentButtonState == LOW) {
    counter++;
    sendLoRaPacket();
    delay(250); // Antirrebote simple para evitar múltiples envíos por un solo pulso
  }

  lastButtonState = currentButtonState;
}

void sendLoRaPacket() {
  StaticJsonDocument<128> doc;
  doc["Equipo"] = INITIALS;
  doc["Contador"] = counter;

  String jsonPayload;
  serializeJson(doc, jsonPayload);

  Serial.print("Enviando paquete LoRa: ");
  Serial.println(jsonPayload);

  LoRa.beginPacket();
  LoRa.print(jsonPayload);
  LoRa.endPacket();
}
