#include <Arduino.h>
#include "config.h"
#include "BootMananger.h"
/**
 * Main code setup
 */
void setup() {
    BootMananger bootManager;
    bootManager.sysInit();
    vTaskDelay(500/portTICK_PERIOD_MS);
    Serial.println("Hello world");
    vTaskDelete(NULL);
}

void loop() {
}