//
// Created by luca on 7/12/21.
//

#ifndef POWERMCU_CONFIG_H
#define POWERMCU_CONFIG_H
#include <FreeRTOS.h>
#include "esp32-hal-uart.h"

/**
 * Debug mode
 */
#ifndef IS_DEBUG
#define IS_DEBUG 1
#endif

/**
 * FreeRTOS core config
 */
#if CONFIG_FREERTOS_UNICORE
static const BaseType_t app_cpu = 0;
#else
static const BaseType_t app_cpu = 1;
#endif
#ifndef configSUPPORT_STATIC_ALLOCATION
#define configSUPPORT_STATIC_ALLOCATION 1
#endif
/**
 * ESP INTERRUPT FLAG
 */
#define ESP_INTR_FLAG_DEFAULT 0

#define uS_TO_S_FACTOR 1000000 /* Conversion factor for micro seconds to seconds */
#define mS_TO_S_FACTOR 1000 /* Conversion factor for milli seconds to seconds */
#define SLEEP_TASK_ENABLED true
#define TIME_TO_SLEEP 5 /* Time ESP32 will go to sleep (in seconds) */
#define TIME_PREDELAY_SLEEP 30000 /* ESP32 will delay this amount before initializing sleeping sequence(in seconds)*/

#define HWSERIAL_2_BAUDRATE  9600
#define HWSERIAL_2_CONF SERIAL_8N1
#define HWSERIAL_2_MAXBUFFER_READ 128

#define SAFESHUTDOWN_DELAY 30 // IN SECONDS


#endif //POWERMCU_CONFIG_H
