//
// Created by luca on 7/17/21.
//

#include "BMSCommunicator.h"

#include <Arduino.h>
#include <pins.h>
#include <config.h>
#define EMPTY_BUFF ""
/* Mutex used to safely read into buffer*/
portMUX_TYPE serialMux = portMUX_INITIALIZER_UNLOCKED;
int readBuff;

[[noreturn]] void taskBMSCommunicator(void * args) {
    //char buff*;
    /*Wait for serial connection to be setup*/
    vTaskDelay(50/portTICK_PERIOD_MS);
    while(1) {
        if (Serial2.available()) {
            /* Enter critical mutex to read incoming data */
            portENTER_CRITICAL(&serialMux);
            readBuff = Serial2.read();
            /* Exit critical mutex to read incoming data */
            Serial.write(readBuff);
            Serial2.write(readBuff);
            portEXIT_CRITICAL(&serialMux);
        }
        vTaskDelay(5/portTICK_PERIOD_MS);
    }
}