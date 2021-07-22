//
// Created by luca on 7/13/21.
//

#include "ServicesContainer.h"
#include "MomentarySwitch.h"
//#include "SleepManager.h"
#include "BMSCommunicator.h"
#include "LedPWMDriver.h"
#include "StatusDisplay.h"

static TaskHandle_t handle_taskMomentaryButtonRead;
//static TaskHandle_t handle_taskSleepManager;
static TaskHandle_t handle_taskBMSCommunicator;

//static TaskHandle_t handle_taskStatusLCD;
void ServicesContainer::registerServices() {
    //xTaskCreatePinnedToCore(taskSleepManager, "Deepsleeps MCU to preserve power", 2048, NULL, 1, &handle_taskSleepManager, 1);
    xTaskCreatePinnedToCore(taskBMSCommunicator, "Communicate with BMS", 2014, NULL, 1, &handle_taskBMSCommunicator, 1);
    xTaskCreatePinnedToCore(taskMomentaryButtonRead, "Momentary switch read task", 2048, NULL, 1, &handle_taskMomentaryButtonRead, 1);
    StatusDisplay::begin();
}

void shutdownServices() {
    LedDriver::turnAllOff();
    //vTaskSuspend(handle_taskSleepManager);
    vTaskSuspend(handle_taskMomentaryButtonRead);
    vTaskSuspend(handle_taskBMSCommunicator);
}