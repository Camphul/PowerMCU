//
// Created by luca on 7/13/21.
//

#include "MomentarySwitch.h"
#include "FunctionalInterrupt.h"
#include "pins.h"
volatile int numberOfButtonInterrupts = 0;
volatile bool lastState;
volatile uint32_t debounceTimeout = 600;
// For setting up critical sections (enableinterrupts and disableinterrupts not available)
// used to disable and interrupt interrupts

portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;


// Interrupt Service Routine - Keep it short!
void IRAM_ATTR handleMomentaryButtonInterrupt() {
    portENTER_CRITICAL_ISR(&mux);
    numberOfButtonInterrupts++;
    lastState = gpio_get_level(SOFTLATCH_BTN_PIN);
    debounceTimeout = xTaskGetTickCount(); //version of millis() that works from interrupt
    portEXIT_CRITICAL_ISR(&mux);
}
void taskMomentaryButtonRead( void * parameter)
{
    gpio_intr_enable(SOFTLATCH_BTN_PIN);
    attachInterrupt(SOFTLATCH_BTN_PIN, handleMomentaryButtonInterrupt, FALLING);
    uint32_t saveDebounceTimeout;
    bool saveLastState;
    int save;
    // Enter RTOS Task Loop
#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
    for(;;) {
        portENTER_CRITICAL_ISR(&mux); // so that value of numberOfButtonInterrupts,l astState are atomic - Critical Section
        save  = numberOfButtonInterrupts;
        saveDebounceTimeout = debounceTimeout;
        saveLastState  = lastState;
        portEXIT_CRITICAL_ISR(&mux); // end of Critical Section

        bool currentState =gpio_get_level(SOFTLATCH_BTN_PIN);

        // This is the critical IF statement
        // if Interrupt Has triggered AND Button Pin is in same state AND the debounce time has expired THEN you have the button push!
        //
        if ((save != 0) //interrupt has triggered
            && (currentState == saveLastState) // pin is still in the same state as when intr triggered
            && (millis() - saveDebounceTimeout > DEBOUNCETIME ))
        { // and it has been low for at least DEBOUNCETIME, then valid keypress
            Serial.println();
            Serial.println();
            Serial.println();
            if (currentState == LOW)
            {
                gpio_set_level(LEDRING_PIN, HIGH);
                Serial.printf("Button is pressed and debounced, current tick=%d\n", millis());
            }
            else
            {
                gpio_set_level(LEDRING_PIN, LOW);
                Serial.printf("Button is released and debounced, current tick=%d\n", millis());
            }
            Serial.printf("Button Interrupt Triggered %d times, current State=%u, time since last trigger %dms\n", save, currentState, millis() - saveDebounceTimeout);
            portENTER_CRITICAL_ISR(&mux); // can't change it unless, atomic - Critical section
            numberOfButtonInterrupts = 0; // acknowledge keypress and reset interrupt counter
            portEXIT_CRITICAL_ISR(&mux);


            vTaskDelay(10 / portTICK_PERIOD_MS);
        }

        vTaskDelay(10 / portTICK_PERIOD_MS);

    }
#pragma clang diagnostic pop
}