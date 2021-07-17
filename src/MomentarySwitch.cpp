//
// Created by luca on 7/13/21.
//

#include "MomentarySwitch.h"
#include "pins.h"
#include "config.h"
#include <EasyButton.h>
#include "SafeShutdownTask.h"
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
bool ledState = false;
void handleOnPressed() {
    Serial.println("Button pressed callback was fired");
    ledState = !ledState;
    gpio_set_level(LEDRING_PIN, ledState);
    safeShutdown();

}

void taskMomentaryButtonRead( void * parameter)
{
    EasyButton powerButton(SOFTLATCH_BTN_PIN, 50, false, true);
    powerButton.begin();
    powerButton.onPressed(handleOnPressed);
   if (powerButton.supportsInterrupt())
    {
       //Serial.println("PwrButton does support interrupts.");
       // powerButton.enableInterrupt(handleMomentaryButtonInterrupt);
    }
    while(1) {
        portENTER_CRITICAL_ISR(&mux);
        powerButton.read();
        portEXIT_CRITICAL_ISR(&mux);
        vTaskDelay(5 / portTICK_PERIOD_MS);
    }


}