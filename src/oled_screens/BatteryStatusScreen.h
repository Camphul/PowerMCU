//
// Created by luca on 7/22/21.
//

#ifndef POWERMCU_BATTERYSTATUSSCREEN_H
#define POWERMCU_BATTERYSTATUSSCREEN_H
#endif //POWERMCU_BATTERYSTATUSSCREEN_H

#include "../include/config-display.h"

typedef enum bat_status_t {
    DISCHARGING,
    CHARGING,
    UNKNOWN
} bat_status;

namespace BatteryPercentageScreen {
    extern void drawBatteryPercentageScreen(Display display);

    extern displayscreen_t getBatteryPercentageScreen();

    extern void setBatteryStatus(bat_status_t status);

    extern void setBatteryPercentage(uint8_t percentage);

    extern bat_status_t getBatteryStatus(void);

    extern uint8_t getBatteryPercentage(void);
}
