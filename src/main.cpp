// #include <Arduino.h>
// #include "server.h"

// // paramètres de votre réseau WiFi
// const char *ssid = "Esp32-SacroSaint-Wifi";
// const char *password = "patate12";

// // Set your Static IP address
// IPAddress local_IP(192, 168, 0, 1);
// IPAddress gateway(192, 168, 0, 0);
// IPAddress subnet(255, 255, 255, 0);

// void setup()
// {
//   // ----------------- Serial -----------------

//   Serial.begin(115200);

//   // ------------------ Wifi ------------------

//   WiFi.mode(WIFI_AP);
//   WiFi.softAPConfig(local_IP, gateway, subnet);
//   WiFi.softAP(ssid, password);

//   Serial.println("WiFi connected");

//   Serial.println("IP:");
//   Serial.println(WiFi.localIP());

//   // ---------------- SPIFFS -----------------

//   if (!SPIFFS.begin())
//   {
//     Serial.println("SPIFFS err");
//     return;
//   }

//   File root = SPIFFS.open("/");
//   File file = root.openNextFile();

//   while (file)
//   {
//     Serial.print("File: ");
//     Serial.println(file.name());
//     file.close();
//     file = root.openNextFile();
//   }

//   // --------- Server & Camera ---------------

//   setupServer();

//   // --------------- Pin engine ---------------

//   Serial.println("Setup done!");
// }

// void loop()
// {
//   vTaskDelay(5000 / portTICK_PERIOD_MS);
// }

#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(27);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  myservo.write(170);
            // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position

    myservo.write(0);              // tell servo to go to position in variable 'pos'
    delay(1000);                       // waits 15ms for the servo to reach the position
  
}