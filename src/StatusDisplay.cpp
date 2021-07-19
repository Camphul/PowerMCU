//
// Created by luca on 7/19/21.
//

#include "StatusDisplay.h"
#include <U8g2lib.h>
#include <FreeRTOS.h>
#include <driver/i2c.h>
#include "config-display.h"
#include "config-i2c.h"
using namespace StatusDisplay;
static TaskHandle_t statusDisplayTaskHandle;
//Chip's i2c address
uint8_t displayI2CAddresss = I2C_ADDRESS_OLED_DISPLAY;
//Actual display driver.
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C disp(U8G2_R0, /*clock=*/18,  /*data=*/19,/* reset=*/ U8X8_PIN_NONE);


[[noreturn]] static void StatusDisplay::taskRenderStatusDisplay(void *args) {
    setI2CAddress(I2C_ADDRESS_OLED_DISPLAY);
    disp.setI2CAddress(displayI2CAddresss);
    disp.begin();
    disp.clearDisplay();
    vTaskDelay(100/portTICK_PERIOD_MS);
    while(1) {
        //Redraw loop
        disp.clearBuffer();
        draw();
        disp.sendBuffer();
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void StatusDisplay::setI2CAddress(uint8_t addr) {
    displayI2CAddresss = addr;
}

void StatusDisplay::begin() {
    disp.setI2CAddress(I2C_ADDRESS_OLED_DISPLAY);
//    u8g2_Setup_ssd1306_i2c_128x32_univision_f(
//            &disp,
//            U8G2_R0,
//            u8g2_esp32_i2c_byte_cb,
//            u8g2_esp32_gpio_and_delay_cb);  // init u8g2 structure
    xTaskCreatePinnedToCore(taskRenderStatusDisplay, "Rendering of i2c based display", 8192, NULL, 1, &statusDisplayTaskHandle, 1);
}

void StatusDisplay::shutdown() {
    clear();
    turnOff();
    vTaskSuspend(statusDisplayTaskHandle);
}

void StatusDisplay::draw() {
    disp.setFontMode(1);  // Transparent
    disp.setDrawColor(2);
    disp.setFontDirection(0);
    disp.setFont(DISPLAY_TEXT_FONT_TOPBAR);
    disp.drawUTF8(0, DISPLAY_TEXT_TOPBAR_BORDER_OFFSET_Y, "☃ OFF");
    disp.drawLine(0,DISPLAY_LINE_Y,DISPLAY_MAX_X, DISPLAY_LINE_Y);
    disp.setFont(DISPLAY_TEXT_FONT_LARGE);
    disp.drawStr(0, DISPLAY_MAX_Y-DISPLAY_TEXT_BORDER_OFFSET_Y, "100% Charge");
}

void StatusDisplay::clear() {
    //xSemaphoreTake(&drawMutex, portMAX_DELAY);
    disp.clearBuffer();
    disp.clearDisplay();
    disp.sendBuffer();
}


void StatusDisplay::turnOff() {
    clear();
    disp.setPowerSave(1);
}

void StatusDisplay::turnOn() {
    clear();
    disp.setPowerSave(0);
}

/**
 * Turn display on for a specified period.
 * @param [in] duration time to keep display on in milliseconds.
 * @return if anything goes wrong
 */
void StatusDisplay::turnOnFor(uint16_t duration) {
    turnOn();
    vTaskDelay(duration/portTICK_PERIOD_MS);
    turnOff();
}