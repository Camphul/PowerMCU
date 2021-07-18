//
// Created by luca on 7/17/21.
//

#include "SafeShutdownTask.h"
#include "config.h"
#include "pins.h"
#include <Arduino.h>
#include "ServicesContainer.h"
#include "LedPWMDriver.h"

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
    Serial.println("Going for a safe shutdown!");
    gpio_set_level(SAFESHUTDOWN_WARN_PIN, LOW);
    gpio_hold_dis(SAFESHUTDOWN_WARN_PIN);
    for (int i = 0; i < SAFESHUTDOWN_DELAY; i++) {
        LedDriver::fadePinUpDown(LEDRING_PIN,2);
        delay(mS_TO_S_FACTOR);
    }
    LedDriver::setLevel(LEDRING_PIN, CHANNEL_LOW);
    Serial.println("System has been shutdown");
    Serial.flush();
    Serial2.flush();
    gpio_set_level(SOFTLATCH_OUTPUT_PIN, LOW);
    gpio_hold_dis(SOFTLATCH_OUTPUT_PIN);
    //gpio_set_direction(SOFTLATCH_BTN_PIN, GPIO_MODE_DISABLE);
    while (1) {
        delay(1000);//just block as a demo, requiring a complete board reset.
    }
    xSemaphoreGive(shutdownMutex);
}