#pragma once
#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <HardwareSerial.h>
#include "fortin.h"
#include "shell.h"
#include "ringbuffer.h"
#include "fortinprocessor.h"

enum parserSate {
  unknown,
  messageStarted,
  messageEnded
};


struct OrsSettings
{
    uint8_t version;
    uint8_t address[3];
    bool cloneAddress:1;
    bool blockAlarm:1;
    bool verbose:1;
    uint8_t reserved:5;
    uint16_t checksum;
};

String getUniqueClientID();
void printMessage(String format, uint8_t message[], int messageLength);
void handleMessageToStarter(uint8_t *message, int length);
void handleValidMessage(uint8_t *message, int length);
int handleStatusUpdate(uint8_t *message, int length);
void updateCurrent();
void updateSettings();
void publishUpdate();
void writeMessageToCloudVar(uint8_t *message, int length);
int set(String command);
int sendCommand(remote_command_t cmd);
int sendCommand(uint8_t cmd);
int sendCommand(uint8_t cmd, uint8_t payload[], uint8_t payloadLength);
void mqttCallback(char* topic, byte* payload, unsigned int length);
uint8_t hexToNib(char c);
int carCommand(String command);
uint16_t calculateChecksum(OrsSettings settings);
void saveSettings();
void loadSettings();
#ifdef ORS_ASSET_TRACKER
void gpsOn();
void gpsOff();
#endif
