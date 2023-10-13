#include <Arduino.h>
#include "server.h"

AsyncWebServer server(80);
Servo thumb_s;
Servo index_s;
Servo middle_s;
Servo ring_s;
Servo pinky_s;

void setupServer()
{
    thumb_s.attach(THUMB_PIN);
    index_s.attach(INDEX_PIN);
    middle_s.attach(MIDDLE_PIN);
    ring_s.attach(RING_PIN);
    pinky_s.attach(PINKY_PIN);

    // ------------------ File System ------------------

    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.html", "text/html"); });

    server.on("/style.css", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/style.css", "text/css"); });

    server.on("/script.js", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/script.js", "text/javascript"); });

    server.on("/base", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/base.png", "image/png"); });

    server.on("/index", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/index.png", "image/png"); });

    server.on("/middle", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/middle.png", "image/png"); });

    server.on("/pinky", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/pinky.png", "image/png"); });

    server.on("/ring", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/ring.png", "image/png"); });

    server.on("/thumb", HTTP_GET, [](AsyncWebServerRequest *request)
              { request->send(SPIFFS, "/thumb.png", "image/png"); });

    // ------------------ Page Stream ------------------

    server.on("/set-pos", HTTP_GET, [](AsyncWebServerRequest *request)
              { 
                if (request->hasParam("0") && 
                    request->hasParam("1") &&
                    request->hasParam("2") && 
                    request->hasParam("3") && 
                    request->hasParam("4"))
                {
                    int thumb = request->getParam("0")->value().toInt();
                    int index = request->getParam("1")->value().toInt();
                    int middle = request->getParam("2")->value().toInt();
                    int ring = request->getParam("3")->value().toInt();
                    int pinky = request->getParam("4")->value().toInt();
                    
                    thumb_s.write(thumb*170);
                    index_s.write(index*170);
                    middle_s.write(middle*170);
                    ring_s.write(ring*170);
                    pinky_s.write(pinky*170);
                }
                request->send(200); });

    // ------------------ Server Start ------------------

    server.begin();

    Serial.println("HTTP server started");
}