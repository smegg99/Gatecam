#ifndef COMMON_H
#define COMMON_H

#include "config.h"
#include <Arduino.h>
#include <ESP32Encoder.h>
#include <freertos/semphr.h>
#include <TFT_eSPI.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

#ifdef ENABLE_OTA
#include <ArduinoOTA.h>
#endif
#include <WebServer.h>

extern const char* API_HOST;
extern const int API_PORT;

#ifdef ENABLE_OTA
extern const uint16_t OTA_PORT;
#endif

#ifdef USE_RGB565_FRAMES
extern const char* pathFormat;
extern const size_t FRAME_SIZE;
extern const size_t CHUNK_SIZE;
#else
extern const char* pathFormat;
extern const size_t FRAME_SIZE;
extern const size_t CHUNK_SIZE;
extern uint16_t grayToRGB565Table[256];
void initGrayToRGB565Table();
#endif

#if defined(ENABLE_DEEP_SLEEP) || defined(ENABLE_REST)
extern const uint64_t DEEP_SLEEP_INTERVAL;
#endif

extern uint8_t* frameBuffer1;
extern uint8_t* frameBuffer2;
extern uint8_t* displayBuffer;
extern uint8_t* fetchBuffer;

extern SemaphoreHandle_t bufferMutex;
extern SemaphoreHandle_t frameReadySemaphore;
extern SemaphoreHandle_t displayUpdateSemaphore;

extern TaskHandle_t fetchTaskHandle;
extern TaskHandle_t displayTaskHandle;
extern TaskHandle_t periphTaskHandle;
extern TaskHandle_t httpServerTaskHandle;

#ifdef RESTART_PERIODICALLY
extern TaskHandle_t autoRestartTaskHandle;

extern const char* ntpServer;
extern const long gmtOffset_sec;
extern const int daylightOffset_sec;
extern const int targetHour;
extern const int targetMinute;
#endif

extern volatile bool displayUpdatePending;
extern volatile bool cameraIdChanged;
extern volatile bool frameReady;
extern volatile bool streamAvailable;

extern volatile uint8_t currentCameraID;

extern unsigned long lastEncoderChangeTime;
extern unsigned long lastProcessTime;

#if defined(ENABLE_DEEP_SLEEP) || defined(ENABLE_REST) 
extern unsigned long lastStimulusTime;
#endif

extern volatile bool showStreamFlag;
extern unsigned long streamDisplayStartTime;

enum DisplayState {
	SHOW_CAMERA_STATUS,
	SHOW_STREAM
};

extern DisplayState currentDisplayState;

extern TFT_eSPI tft;

#ifndef DISABLE_NETWORKING
extern WiFiClient wifiClient;
extern HTTPClient http;

extern WebServer server;
#endif

extern ESP32Encoder encoder;
extern volatile bool buzzerOn;
extern unsigned long buzzerOffTime;
extern const unsigned long BUZZER_DURATION;

String buildFetchURL(uint8_t cameraId);
void setupBuffers();

#endif