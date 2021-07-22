//
// Created by luca on 7/22/21.
//

#include "BatteryStatusScreen.h"
#include "../../include/config.h"
#include "../../include/config-display.h"
#include <cstdint>
using namespace BatteryPercentageScreen;

volatile uint8_t batteryPercentage = 0;
volatile bat_status_t batStatus = UNKNOWN;
#if IS_DEBUG
volatile uint8_t dbgPercentage = 0;
#endif

/**
 * Sets battery charging status
 * @param [in] status battery status
 */
void BatteryPercentageScreen::setBatteryStatus(bat_status_t status) {
    batStatus = status;
}
/**
 * Sets battery percentage that is left.
 * @param [in] percentage left battery percentage
 */
void BatteryPercentageScreen::setBatteryPercentage(uint8_t percentage) {
    batteryPercentage = percentage;
}
/**
 * Get battery status
 * @return battery status
 */
bat_status_t BatteryPercentageScreen::getBatteryStatus() {
    return batStatus;
}

/**
 * Battery percentage info
 * @return battery percentage
 */
uint8_t BatteryPercentageScreen::getBatteryPercentage() {
    return batteryPercentage;
}
void BatteryPercentageScreen::drawBatteryPercentageScreen(Display display) {
#if IS_DEBUG
    if(batteryPercentage >= 100) {
            dbgPercentage = 0;
            setBatteryPercentage(0);
    }
    ++dbgPercentage;
    setBatteryPercentage(dbgPercentage);
    bat_status_t stat = dbgPercentage % 3 == 0 ? CHARGING : DISCHARGING;
    setBatteryStatus(stat);
#endif
    char *batStatusStr = const_cast<char*>(DEFAULT_UNKNOWN_ERROR_STR);
    switch (getBatteryStatus()) {
        case DISCHARGING:
            batStatusStr = const_cast<char*>(DISCHARGING_STR);
            break;
        case CHARGING:
            batStatusStr = const_cast<char*>(CHARGING_STR);
            break;
        case UNKNOWN:
            batStatusStr = const_cast<char*>(UNKNOWN_STR);
            break;
        default:
            batStatusStr = const_cast<char*>(DEFAULT_UNKNOWN_ERROR_STR);
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
    asprintf(&txtStr, "%u%% charged", getBatteryPercentage());
    display.drawStr(0, DISPLAY_MAX_Y-DISPLAY_TEXT_BORDER_OFFSET_Y, txtStr);
}
static const displayscreen_t SCREEN_STRUCT = {
        const_cast<char*>("BatteryPercentageScreen"),
        drawBatteryPercentageScreen,
};
displayscreen_t BatteryPercentageScreen::getBatteryPercentageScreen() {
    return SCREEN_STRUCT;
}