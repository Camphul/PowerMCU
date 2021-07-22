//
// Created by luca on 7/22/21.
//

#ifndef POWERMCU_SHUTDOWNSCREEN_H
#define POWERMCU_SHUTDOWNSCREEN_H
#endif //POWERMCU_SHUTDOWNSCREEN_H
#include "../StatusDisplay.h"
#include <cstdint>
namespace ShutdownScreen {
    extern void drawShutdownScreen(Display display);
    extern void setSecondsLeft(uint8_t secondsLeft);
    extern displayscreen_t getShutdownScreen();
}
