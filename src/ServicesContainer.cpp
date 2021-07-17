//
// Created by luca on 7/13/21.
//

#include "ServicesContainer.h"
#include "MomentarySwitch.h"
#include "SleepManager.h"
#include "BMSCommunicator.h"

static TaskHandle_t handle_taskMomentaryButtonRead;
static TaskHandle_t handle_taskSleepManager;
static TaskHandle_t handle_taskBMSCommunicator;

//static TaskHandle_t handle_taskStatusLCD;
void ServicesContainer::registerServices() {
    xTaskCreate(taskMomentaryButtonRead, "Momentary switch read task", 1024, NULL, 1, &handle_taskMomentaryButtonRead);
    xTaskCreate(taskSleepManager, "Deepsleeps MCU to preserve power", 2048, NULL, 1, &handle_taskSleepManager);
    xTaskCreate(taskBMSCommunicator, "Communicate with BMS", 2014, NULL, 1, &handle_taskBMSCommunicator);
}

void shutdownServices() {
    vTaskSuspend(handle_taskSleepManager);
    vTaskSuspend(handle_taskMomentaryButtonRead);
    vTaskSuspend(handle_taskBMSCommunicator);
}