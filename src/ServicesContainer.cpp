//
// Created by luca on 7/13/21.
//

#include "ServicesContainer.h"
#include "MomentarySwitch.h"
#include "SleepManager.h"
static TaskHandle_t handle_taskMomentaryButtonRead;
static TaskHandle_t handle_taskSleepManager;
void ServicesContainer::registerServices() {
    xTaskCreate(taskMomentaryButtonRead, "Momentary switch read task", 1024, NULL, 3, &handle_taskMomentaryButtonRead);
    xTaskCreate(taskSleepManager, "Deepsleeps MCU to preserve power", 2048, NULL, 3, &handle_taskSleepManager);
}