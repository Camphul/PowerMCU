//
// Created by luca on 7/13/21.
//

#include "SleepManager.h"
#include "Arduino.h"
#include "config.h"
#include "pins.h"
#include "soc/rtc_cntl_reg.h"
#include "SafeShutdownTask.h"
#include "driver/rtc_io.h"

RTC_DATA_ATTR int bootCount = 0;
RTC_DATA_ATTR SleepManager sleepManager;

SleepManager::SleepManager() {}

void SleepManager::initTimedSleep() {
    ++bootCount;
    Serial.println("Boot number: " + String(bootCount));
    gpio_set_level(SAFESHUTDOWN_WARN_PIN, HIGH);
    gpio_hold_en(SAFESHUTDOWN_WARN_PIN);
    //Since we know the power button is wakeup reason for this we want to actually shut down
    esp_sleep_wakeup_cause_t wakeup_reason;
    wakeup_reason = esp_sleep_get_wakeup_cause();
    if (wakeup_reason == ESP_SLEEP_WAKEUP_EXT0) {
        Serial.println("EXT0 wakeup  reason triggered");
        delay(400);
        safeShutdown();
        delay(SAFESHUTDOWN_DELAY*mS_TO_S_FACTOR + 2000);
    }
    gpio_set_intr_type(SOFTLATCH_BTN_PIN, GPIO_INTR_POSEDGE);
    gpio_intr_enable(SOFTLATCH_BTN_PIN);
    printWakeupReason(wakeup_reason);
#ifdef TIME_PREDELAY_SLEEP
    delay((TIME_PREDELAY_SLEEP*mS_TO_S_FACTOR) / portTICK_PERIOD_MS);
#endif
    esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
    Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
                   " Seconds");
    Serial.println("Going to sleep now");
    Serial.flush();
    esp_deep_sleep_start();
}

/*
Method to print the reason by which ESP32
has been awaken from sleep
*/
void SleepManager::printWakeupReason(esp_sleep_wakeup_cause_t wakeup_reason) {
    switch (wakeup_reason) {
        case ESP_SLEEP_WAKEUP_EXT0 :
            Serial.println("Wakeup caused by external signal using RTC_IO");
            break;
        case ESP_SLEEP_WAKEUP_EXT1 :
            Serial.println("Wakeup caused by external signal using RTC_CNTL");
            break;
        case ESP_SLEEP_WAKEUP_TIMER :
            Serial.println("Wakeup caused by timer");
            break;
        case ESP_SLEEP_WAKEUP_TOUCHPAD :
            Serial.println("Wakeup caused by touchpad");
            break;
        case ESP_SLEEP_WAKEUP_ULP :
            Serial.println("Wakeup caused by ULP program");
            break;
        default :
            Serial.printf("Wakeup was not caused by deep sleep: %d\n", wakeup_reason);
            break;
    }
}

void taskSleepManager(void *parameter) {
    while (1) {
#if SLEEP_TASK_ENABLED
        sleepManager.initTimedSleep();
#endif
    }
}
