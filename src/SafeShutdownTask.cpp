//
// Created by luca on 7/17/21.
//

#include "SafeShutdownTask.h"
#include "config.h"
#include "pins.h"
#include <Arduino.h>
#include "ServicesContainer.h"
portMUX_TYPE shutdownMux = portMUX_INITIALIZER_UNLOCKED;
void safeShutdown() {
    xTaskCreate(taskSafeShutdown, "Safe shutdown task", 1024, NULL, 1, NULL);
}
void taskSafeShutdown(void * args) {
   // portENTER_CRITICAL_ISR(&shutdownMux);
    gpio_hold_en(SOFTLATCH_OUTPUT_PIN);
    gpio_set_level(SOFTLATCH_OUTPUT_PIN, HIGH);
    gpio_set_level(LEDRING_PIN, LOW);
    Serial.println("Going for a safe shutdown!");
    gpio_set_level(SAFESHUTDOWN_WARN_PIN, HIGH);
    delay(SAFESHUTDOWN_DELAY);
    //gpio_set_direction(SOFTLATCH_BTN_PIN, GPIO_MODE_DISABLE);
    //gpio_hold_dis(SOFTLATCH_OUTPUT_PIN);
    shutdownServices();
    Serial.flush();
    Serial2.flush();
    gpio_set_level(SOFTLATCH_OUTPUT_PIN, LOW);
    gpio_hold_dis(SOFTLATCH_OUTPUT_PIN);
    delay(200);
    //portEXIT_CRITICAL_ISR(&shutdownMux);
}