//
// Created by luca on 7/13/21.
//

#include "MomentarySwitch.h"
#include "pins.h"
#include "config.h"
#include <EasyButton.h>
#include "SafeShutdownTask.h"
#include "LedPWMDriver.h"

static SemaphoreHandle_t btnMutex = xSemaphoreCreateMutex();
static SemaphoreHandle_t pressedMutex = xSemaphoreCreateMutex();
bool ledState = false;

void handleOnPressed() {
    xSemaphoreTake(pressedMutex, portMAX_DELAY);
    Serial.println("Button pressed callback was fired");
    ledState = !ledState;
    LedDriver::setLevel(LEDRING_R_PIN, ledState);
    safeShutdown();
    xSemaphoreGive(pressedMutex);
}

void taskMomentaryButtonRead(void *parameter) {
    EasyButton powerButton(SOFTLATCH_BTN_PIN, 50, false, false);
    powerButton.begin();
    powerButton.onPressed(handleOnPressed);
    while (1) {
        xSemaphoreTake(btnMutex, portMAX_DELAY);
        powerButton.read();
        xSemaphoreGive(btnMutex);
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }


}