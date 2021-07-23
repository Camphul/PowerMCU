//
// Created by luca on 7/19/21.
//

#ifndef POWERMCU_STATUSDISPLAY_H
#define POWERMCU_STATUSDISPLAY_H

#include <cstdint>
#include "config-i2c.h"
#include "config-display.h"
#include "esp_err.h"
#include "esp32-hal-gpio.h"
#include <U8x8lib.h>
#include <clib/u8g2.h>
#include <U8g2lib.h>
#include "freertos/timers.h"
//#define U8G2_ESP32_HAL_UNDEFINED (-1)
//#define U8G2_ESP32_HAL_DEFAULT { I2C_SDA, I2C_SCL }
#define ACTION_OLED_ON 0x1
namespace StatusDisplay {
    [[noreturn]] static void taskRenderStatusDisplay(void *args);

    extern void setDisplayScreen(displayscreen_t screen);

    extern void resetDisplayScreen(void);

    extern displayscreen_t getDisplayScreen(void);

    extern void setI2CAddress(uint8_t addr);

    extern void turnOff(void);
    extern void turnOffTimerHandle(TimerHandle_t timer);


    extern void turnOn(void);

    extern void turnOnFor(uint16_t duration);

    extern void turnOnForDurationFromISR(void);

    extern void clear(void);

    extern void draw(void);

    extern void begin(void);

    extern void shutdown(void);

}


#endif //POWERMCU_STATUSDISPLAY_H
