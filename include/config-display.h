//
// Created by luca on 7/19/21.
//

#ifndef POWERMCU_CONFIG_DISPLAY_H
#define POWERMCU_CONFIG_DISPLAY_H
#include <U8g2lib.h>
#define DISPLAY_MAX_Y 32
#define DISPLAY_MAX_X 128
#define DISPLAY_MIN_Y 0
#define DISPLAY_MIN_X 0
#define DISPLAY_LINE_Y 9
#define DISPLAY_TEXT_FONT_LARGE u8g2_font_logisoso16_tf
#define DISPLAY_TEXT_FONT_TOPBAR u8g2_font_victoriabold8_8r
//#define DISPLAY_TEXT_FONT_TOPBAR_ICONS open_iconic_embedded_8x
#define DISPLAY_TEXT_BORDER_OFFSET_Y 4
#define DISPLAY_TEXT_TOPBAR_BORDER_OFFSET_Y 8
#define DISPLAY_REFRESH_RATE_DELAY_MS 1000
#define DISCHARGING_STR "Discharging"
#define CHARGING_STR "Charging"
#define UNKNOWN_STR "Unknown"
#define DEFAULT_UNKNOWN_ERROR_STR "Unkwn Error"
#define DISPLAY_TURN_ON_TIME 10
typedef U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C Display;

typedef struct displayscreen_t {
    char *screenName;
    void(*render)(Display display);
} displayscreen;
#endif //POWERMCU_CONFIG_DISPLAY_H
