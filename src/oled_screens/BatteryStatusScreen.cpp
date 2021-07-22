//
// Created by luca on 7/22/21.
//

#include "BatteryStatusScreen.h"
#include "../../include/config-display.h"
using namespace BatteryPercentageScreen;
void BatteryPercentageScreen::drawBatteryPercentageScreen(Display display) {
    char *batStatusStr = DEFAULT_UNKNOWN_ERROR_STR;
    switch (StatusDisplay::getBatteryStatus()) {
        case DISCHARGING:
            batStatusStr = DISCHARGING_STR;
            break;
        case CHARGING:
            batStatusStr = CHARGING_STR;
            break;
        case UNKNOWN:
            batStatusStr = UNKNOWN_STR;
            break;
        default:
            batStatusStr = DEFAULT_UNKNOWN_ERROR_STR;
            break;
    }
    display.setFontMode(1);  // Transparent
    display.setDrawColor(2);
    display.setFontDirection(0);
    display.setFont(DISPLAY_TEXT_FONT_TOPBAR);
    display.drawStr(0, DISPLAY_TEXT_TOPBAR_BORDER_OFFSET_Y, batStatusStr);
    display.drawLine(0,DISPLAY_LINE_Y,DISPLAY_MAX_X, DISPLAY_LINE_Y);
    display.setFont(DISPLAY_TEXT_FONT_LARGE);
    char *txtStr;
    asprintf(&txtStr, "%u%% charged", StatusDisplay::getBatteryPercentage());
    display.drawStr(0, DISPLAY_MAX_Y-DISPLAY_TEXT_BORDER_OFFSET_Y, txtStr);
}

displayscreen_t BatteryPercentageScreen::getBatteryPercentageScreen() {
    return {
            "BatteryPercentageScreen",
            drawBatteryPercentageScreen,
    };
}