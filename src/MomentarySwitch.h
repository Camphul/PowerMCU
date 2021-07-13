//
// Created by luca on 7/13/21.
//

#ifndef POWERMCU_MOMENTARYSWITCH_H
#define POWERMCU_MOMENTARYSWITCH_H
#define DEBOUNCETIME 10
#include "Arduino.h"
void IRAM_ATTR handleMomentaryButtonInterrupt();
void taskMomentaryButtonRead( void * parameter);

#endif //POWERMCU_MOMENTARYSWITCH_H
