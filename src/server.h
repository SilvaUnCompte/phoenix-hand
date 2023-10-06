#ifndef SERVER_H
#define SERVER_H

#include <SPIFFS.h> // Contrains FS.h
#include "ESPAsyncWebServer.h"

#define THUMB_PIN 0
#define INDEX_PIN 1
#define MIDDLE_PIN 2
#define RING_PIN 3
#define PINKY_PIN 4


void setupServer();

#endif