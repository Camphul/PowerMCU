//
// Created by luca on 7/22/21.
//

#include "ShutdownScreen.h"
#include "../../include/config-display.h"
#include "../../include/config.h"
#include <cstdint>
using namespace ShutdownScreen;
volatile uint8_t timeLeft = SAFESHUTDOWN_DELAY;
void ShutdownScreen::drawShutdownScreen(Display display) {
    display.setFontMode(1);  // Transparent
    display.setDrawColor(2);
    display.setFontDirection(0);
    display.setFont(DISPLAY_TEXT_FONT_TOPBAR);
    char *timeLeftTxt;
    asprintf(&timeLeftTxt, "%02u seconds left", timeLeft);
    display.drawStr(0, DISPLAY_TEXT_TOPBAR_BORDER_OFFSET_Y, timeLeftTxt);
    display.drawLine(0,DISPLAY_LINE_Y,DISPLAY_MAX_X, DISPLAY_LINE_Y);
    display.setFont(DISPLAY_TEXT_FONT_LARGE);
    display.drawStr(0, DISPLAY_MAX_Y-DISPLAY_TEXT_BORDER_OFFSET_Y, "Shutting down");
}
void ShutdownScreen::setSecondsLeft(uint8_t secondsLeft) {
    timeLeft = secondsLeft;
}
static const displayscreen_t SCREEN_STRUCT = {
        const_cast<char*>("ShutdownScreen"),
        drawShutdownScreen,
};
displayscreen_t ShutdownScreen::getShutdownScreen() {
    return SCREEN_STRUCT;
}