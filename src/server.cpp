#include <Arduino.h>
#include "server.h"

#define PART_BOUNDARY "123456789000000000000987654321"
static const char *STREAM_CONTENT_TYPE = "multipart/x-mixed-replace;boundary=" PART_BOUNDARY;
static const char *STREAM_BOUNDARY = "\r\n--" PART_BOUNDARY "\r\n";
static const char *STREAM_PART = "Content-Type: %s\r\nContent-Length: %u\r\n\r\n";
static const char *JPG_CONTENT_TYPE = "image/jpeg";

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

    // ------------------ Page Stream ------------------

    // server.on("/direction-stream", HTTP_GET, [](AsyncWebServerRequest *request)
    //           { 
    //             if (request->hasParam("right") && request->hasParam("left"))
    //             {
    //                 int right = request->getParam("right")->value().toInt();
    //                 int left = request->getParam("left")->value().toInt();
                    
    //                 bool leftDirection = left > 0 ? 1 : 0;
    //                 bool rightDirection = right > 0 ? 1 : 0;

    //                 digitalWrite(LEFT_MOTOR_IN1, leftDirection);
    //                 digitalWrite(LEFT_MOTOR_IN2, !leftDirection);
    //                 ledcWrite(LEFT_PWM_CHANNEL, abs(left));

    //                 digitalWrite(RIGHT_MOTOR_IN1, rightDirection);
    //                 digitalWrite(RIGHT_MOTOR_IN2, !rightDirection);
    //                 ledcWrite(RIGHT_PWM_CHANNEL, abs(right));

    //                 Serial.println("Left: " + String(left) + " Right: " + String(right));
    //             }
    //             request->send(200); });

    // ------------------ Server Start ------------------

    server.begin();

    Serial.println("HTTP server started");
}