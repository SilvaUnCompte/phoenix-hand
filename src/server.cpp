#include <Arduino.h>
#include "server.h"

AsyncWebServer server(80);

void setupServer()
{
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
                    
                    // digitalWrite(LEFT_MOTOR_IN1, leftDirection);
                    // digitalWrite(LEFT_MOTOR_IN2, !leftDirection);
                    // ledcWrite(THUMB_PIN, 1);

                    // digitalWrite(RIGHT_MOTOR_IN1, rightDirection);
                    // digitalWrite(RIGHT_MOTOR_IN2, !rightDirection);
                    // ledcWrite(RIGHT_PWM_CHANNEL, abs(right));
                }
                request->send(200); });

    // ------------------ Server Start ------------------

    server.begin();

    Serial.println("HTTP server started");
}