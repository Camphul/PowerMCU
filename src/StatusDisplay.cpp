//
// Created by luca on 7/19/21.
//

#include "StatusDisplay.h"
#include <U8g2lib.h>
#include <driver/i2c.h>
#include "config-display.h"
#include "config-i2c.h"
#include "config.h"
#include "esp32-hal-log.h"
#include "oled_screens/BatteryStatusScreen.h"

using namespace StatusDisplay;
static TaskHandle_t statusDisplayTaskHandle;
static displayscreen_t DEFAULT_SCREEN;
//Chip's i2c address
uint8_t displayI2CAddresss = I2C_ADDRESS_OLED_DISPLAY;

displayscreen currentScreen;
//Actual display driver.
Display disp(U8G2_R0, /*clock=*/I2C_SCL1,  /*data=*/I2C_SDA1,/* reset=*/ U8X8_PIN_NONE);

void StatusDisplay::setI2CAddress(uint8_t addr) {
    displayI2CAddresss = addr;
}

/**
 * Initializes the display
 */
void StatusDisplay::begin() {
    disp.setI2CAddress(I2C_ADDRESS_OLED_DISPLAY);
    DEFAULT_SCREEN = BatteryPercentageScreen::getBatteryPercentageScreen();
    setDisplayScreen(DEFAULT_SCREEN);
    xTaskCreatePinnedToCore(taskRenderStatusDisplay, "Rendering of i2c based display", 8192, NULL, 1,
                            &statusDisplayTaskHandle, 1);
}

/**
 * Stops rendering task and turns off the display
 */
void StatusDisplay::shutdown() {
    clear();
    turnOff();
    vTaskSuspend(statusDisplayTaskHandle);
}

/**
 * Draws on the display
 */
void StatusDisplay::draw() {
    if (currentScreen.screenName == NULL || currentScreen.render == NULL) {
        currentScreen = DEFAULT_SCREEN;
#if IS_DEBUG
        ESP_LOGV("Set to default screen since current screen was null");
#endif
    }
#if IS_DEBUG
    char *screenNameTxt;
    asprintf(&screenNameTxt, "%s as current screen render", currentScreen.screenName);
    ESP_LOGI(screenNameTxt);
    //Serial.println(screenNameTxt);
#endif
    currentScreen.render(disp);
}

void StatusDisplay::setDisplayScreen(displayscreen_t screen) {
    currentScreen = screen;
}

displayscreen_t StatusDisplay::getDisplayScreen() {
    return currentScreen;
}

void StatusDisplay::resetDisplayScreen() {
    setDisplayScreen(DEFAULT_SCREEN);
}

/**
 * Clear display framebuffer and render
 */
void StatusDisplay::clear() {
    disp.clearBuffer();
    disp.clearDisplay();
    disp.sendBuffer();
}

/**
 * Turns off display
 */
void StatusDisplay::turnOff() {
    clear();
    disp.setPowerSave(1);
}

/**
 * Turns on display
 */
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
    vTaskDelay(duration / portTICK_PERIOD_MS);
    turnOff();
}

/**
 * Initializes i2c display
 * @param [in] args argumemts given to task
 */
static void StatusDisplay::taskRenderStatusDisplay(void *args) {
    setI2CAddress(I2C_ADDRESS_OLED_DISPLAY);
    setDisplayScreen(BatteryPercentageScreen::getBatteryPercentageScreen());
    disp.setI2CAddress(displayI2CAddresss);
    disp.begin();
    disp.clearDisplay();
    vTaskDelay(100 / portTICK_PERIOD_MS);
    char *previousScreenName = currentScreen.screenName;
    while (RUNNING) {
        //Redraw loop
        if (previousScreenName != currentScreen.screenName) {
#if IS_DEBUG
            Serial.printf("Switching screen from %s to %s\r\n",previousScreenName, currentScreen.screenName);
#endif
            clear();
        }
        disp.clearBuffer();
        draw();
        previousScreenName = currentScreen.screenName;
        disp.sendBuffer();
        vTaskDelay(DISPLAY_REFRESH_RATE_DELAY_MS / portTICK_PERIOD_MS);
    }
}