//
// Created by luca on 7/13/21.
//

#ifndef POWERMCU_SLEEPMANAGER_H
#define POWERMCU_SLEEPMANAGER_H

#include "esp32-hal-gpio.h"

class SleepManager {
public:
    SleepManager();

    void printWakeupReason(esp_sleep_wakeup_cause_t wakeup_reason);

    void initTimedSleep();
};

void taskSleepManager(void *args);


#endif //POWERMCU_SLEEPMANAGER_H
