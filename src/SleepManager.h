//
// Created by luca on 7/13/21.
//

#ifndef POWERMCU_SLEEPMANAGER_H
#define POWERMCU_SLEEPMANAGER_H
#include "esp32-hal-gpio.h"
class SleepManager {
public:
    SleepManager();
    void printWakeupReason();
    void initTimedSleep();
};

void taskSleepManager(void * args);


#endif //POWERMCU_SLEEPMANAGER_H
