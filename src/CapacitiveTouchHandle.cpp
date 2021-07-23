//
// Created by luca on 7/23/21.
//

#include "CapacitiveTouchHandle.h"
#include "config.h"
#include "pins.h"
#include "Arduino.h"
#include "StatusDisplay.h"
using namespace CapacitiveTouch;

static SemaphoreHandle_t touchMutex = xSemaphoreCreateMutex();
volatile u_long lastBounce = -1;

void CapacitiveTouch::handleTouch(void* args){
    xSemaphoreTake(touchMutex, portMAX_DELAY);
    if(lastBounce == -1 || ((millis() - lastBounce) >= OLED_TOUCH_CAPACITIVE_DEBOUNCE_PERIOD)) {
        lastBounce = millis();
#if IS_DEBUG
        uint16_t touchValue;
        touch_pad_read_filtered(OLED_TOUCH_WAKEUP_PAD, &touchValue);
        Serial.printf("Read filtered touch value of: %u while threshold is %u\r\n", touchValue,
                      OLED_TOUCH_CAPACITIVE_THRESHOLD);
#endif
        touch_pad_clear_status();
        StatusDisplay::turnOnForDurationFromISR();
        //StatusDisplay::turnOnFor(DISPLAY_TURN_ON_TIME * mS_TO_S_FACTOR);
    }
    xSemaphoreGive(touchMutex);
}