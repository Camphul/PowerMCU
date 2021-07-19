//
// Created by luca on 7/19/21.
//

#ifndef POWERMCU_STATUSDISPLAY_H
#define POWERMCU_STATUSDISPLAY_H
#include <cstdint>
#include "config-i2c.h"
#include "esp_err.h"
#include "esp32-hal-gpio.h"
#include <U8x8lib.h>

#define U8G2_ESP32_HAL_UNDEFINED (-1)
#define U8G2_ESP32_HAL_DEFAULT { I2C_SDA, I2C_SCL }
namespace StatusDisplay {
    [[noreturn]] static void taskRenderStatusDisplay(void *args);
    extern void setI2CAddress(uint8_t addr);
    extern void turnOff(void);
    extern void turnOn(void);
    extern void turnOnFor(uint16_t duration);
    extern void clear(void);
    extern void draw(void);
    extern void begin(void);
    extern void shutdown(void);

}


#endif //POWERMCU_STATUSDISPLAY_H
