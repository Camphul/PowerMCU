//
// Created by luca on 7/12/21.
//

#ifndef POWERMCU_PINS_H
#define POWERMCU_PINS_H
#include "esp32-hal-touch.h"
#include "esp32-hal-gpio.h"
#define SOFTLATCH_OUTPUT_PIN GPIO_NUM_2
#define SOFTLATCH_BTN_PIN GPIO_NUM_27
#define LEDRING_R_PIN 0
#define LEDRING_G_PIN 1
#define LEDRING_B_PIN 2
#define SAFESHUTDOWN_WARN_PIN GPIO_NUM_33
#define RXD2 16
#define TXD2 17
#define OLED_TOUCH_WAKEUP_PIN GPIO_NUM_4
#define OLED_TOUCH_WAKEUP_PAD TOUCH_PAD_NUM0
#endif //POWERMCU_PINS_H
