//
// Created by luca on 7/17/21.
//

#include "SafeShutdownTask.h"
#include "config.h"
#include "pins.h"
#include <Arduino.h>
#include "ServicesContainer.h"

static SemaphoreHandle_t shutdownMutex = xSemaphoreCreateMutex();
static TaskHandle_t shutdownTaskHandle;

void safeShutdown() {
    xTaskCreate(taskSafeShutdown, "Safe shutdown task", 4096, NULL, 1, &shutdownTaskHandle);
}

void taskSafeShutdown(void *args) {
    xSemaphoreTake(shutdownMutex, portMAX_DELAY);
    Serial.println("Shutting down");
    shutdownServices();
    gpio_hold_en(SOFTLATCH_OUTPUT_PIN);
    gpio_set_level(SOFTLATCH_OUTPUT_PIN, HIGH);
    gpio_set_level(LEDRING_PIN, LOW);
    Serial.println("Going for a safe shutdown!");
    gpio_set_level(SAFESHUTDOWN_WARN_PIN, LOW);
    gpio_hold_dis(SAFESHUTDOWN_WARN_PIN);
    delay(SAFESHUTDOWN_DELAY * mS_TO_S_FACTOR);
    Serial.println("System has been shutdown");
    Serial.flush();
    Serial2.flush();
    gpio_set_level(SOFTLATCH_OUTPUT_PIN, LOW);
    gpio_hold_dis(SOFTLATCH_OUTPUT_PIN);
    //gpio_set_direction(SOFTLATCH_BTN_PIN, GPIO_MODE_DISABLE);
    delay(100);
    xSemaphoreGive(shutdownMutex);
}