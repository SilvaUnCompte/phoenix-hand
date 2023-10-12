#include <Arduino.h>
#include "server.h"

// paramètres de votre réseau WiFi
const char* ssid = "Esp32-SacroSaint-Wifi";
const char* password = "patate12";

// Set your Static IP address
IPAddress local_IP(192, 168, 0, 1);
IPAddress gateway(192, 168, 0, 0);
IPAddress subnet(255, 255, 255, 0);

void setup()
{
  // ----------------- Serial -----------------

  Serial.begin(115200);

  // ------------------ Wifi ------------------

  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP, gateway, subnet);
  WiFi.softAP(ssid, password);

  Serial.println("WiFi connected");

  Serial.println("IP:");
  Serial.println(WiFi.localIP());

  // ---------------- SPIFFS -----------------

  if (!SPIFFS.begin())
  {
    Serial.println("SPIFFS err");
    return;
  }

  File root = SPIFFS.open("/");
  File file = root.openNextFile();

  while (file)
  {
    Serial.print("File: ");
    Serial.println(file.name());
    file.close();
    file = root.openNextFile();
  }

  // --------- Server & Camera ---------------

  setupServer();

  // --------------- Pin engine ---------------

  pinMode(THUMB_PIN, OUTPUT);
  pinMode(INDEX_PIN, OUTPUT);
  pinMode(MIDDLE_PIN, OUTPUT);
  pinMode(RING_PIN, OUTPUT);
  pinMode(PINKY_PIN, OUTPUT);

  // ledcSetup(THUMB_PWM_CHANNEL, 30000, 8);
  // ledcAttachPin(THUMB_PIN, THUMB_PWM_CHANNEL);
  // ledcSetup(INDEX_PWM_CHANNEL, 30000, 8);
  // ledcAttachPin(INDEX_PIN, INDEX_PWM_CHANNEL);
  // ledcSetup(MIDDLE_PWM_CHANNEL, 30000, 8);
  // ledcAttachPin(MIDDLE_PIN, MIDDLE_PWM_CHANNEL);
  // ledcSetup(RING_PWM_CHANNEL, 30000, 8);
  // ledcAttachPin(RING_PIN, RING_PWM_CHANNEL);
  // ledcSetup(PINKY_PWM_CHANNEL, 30000, 8);
  // ledcAttachPin(PINKY_PIN, PINKY_PWM_CHANNEL);

  Serial.println("Setup done!");
}

void loop() { vTaskDelay(5000 / portTICK_PERIOD_MS); }
