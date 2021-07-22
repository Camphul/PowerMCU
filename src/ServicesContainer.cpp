//
// Created by luca on 7/13/21.
//

#include "ServicesContainer.h"
#include "config.h"
#include "MomentarySwitch.h"
#if SLEEP_TASK_ENABLED
#include "SleepManager.h"
#endif
#include "BMSCommunicator.h"
#include "LedPWMDriver.h"
#include "StatusDisplay.h"

static TaskHandle_t handle_taskMomentaryButtonRead;
#if SLEEP_TASK_ENABLED
static TaskHandle_t handle_taskSleepManager;
#endif
static TaskHandle_t handle_taskBMSCommunicator;

//static TaskHandle_t handle_taskStatusLCD;
void ServicesContainer::registerServices() {
#if SLEEP_TASK_ENABLED
    xTaskCreatePinnedToCore(taskSleepManager, "Deepsleeps MCU to preserve power", 2048, NULL, 1, &handle_taskSleepManager, 1);
#endif
    xTaskCreatePinnedToCore(taskBMSCommunicator, "Communicate with BMS", 2014, NULL, 1, &handle_taskBMSCommunicator, 1);
    xTaskCreatePinnedToCore(taskMomentaryButtonRead, "Momentary switch read task", 2048, NULL, 1,
                            &handle_taskMomentaryButtonRead, 1);
    StatusDisplay::begin();
}

void shutdownServices() {
    LedDriver::turnAllOff();
#if SLEEP_TASK_ENABLED
    vTaskSuspend(handle_taskSleepManager);
#endif
    vTaskSuspend(handle_taskMomentaryButtonRead);
    vTaskSuspend(handle_taskBMSCommunicator);
}