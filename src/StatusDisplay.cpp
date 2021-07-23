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
#if IS_DEBUG
#include "Arduino.h"
#endif

using namespace StatusDisplay;
static TimerHandle_t onOffTimer;
static TaskHandle_t statusDisplayTaskHandle;
static QueueHandle_t queuePtr = xQueueCreate(10, sizeof(uint8_t));
static displayscreen_t DEFAULT_SCREEN;
int timerId = 1;
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
    if(onOffTimer != NULL) {
        xTimerStop(onOffTimer, 0);
        xTimerDelete(onOffTimer, 1);
        vTaskDelay(10/portTICK_PERIOD_MS);
        onOffTimer = NULL;
    }
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
    disp.setPowerSave(0);
}

void StatusDisplay::turnOffTimerHandle(TimerHandle_t timer) {
    turnOff();
    xTimerStop(timer, 0);
    xTimerDelete(timer, 1);
    vTaskDelay(10/portTICK_PERIOD_MS);
    onOffTimer = NULL;
}

/**
 * Turn display on for a specified period.
 * @param [in] duration time to keep display on in milliseconds.
 * @return if anything goes wrong
 */
void StatusDisplay::turnOnFor(uint16_t duration) {
    turnOn();
    if(onOffTimer != NULL) {
        xTimerStop(onOffTimer, 0);
        xTimerDelete(onOffTimer, 1);
        vTaskDelay(10/portTICK_PERIOD_MS);
        onOffTimer = NULL;
    }
    onOffTimer = xTimerCreate("DisplayOnOffTimer", pdMS_TO_TICKS(duration), pdTRUE, &timerId, &turnOffTimerHandle);
    xTimerStart(onOffTimer, 0);
}

void StatusDisplay::turnOnForDurationFromISR() {
    if(queuePtr != NULL) {
        uint8_t action = ACTION_OLED_ON;
        xQueueSendFromISR(queuePtr, &action, NULL);
    }
}

/**
 * Initializes i2c display
 * @param [in] args argumemts given to task
 */
[[noreturn]] static void StatusDisplay::taskRenderStatusDisplay(void *args) {
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
            //turn on when screen changes
            turnOnFor(DISPLAY_TURN_ON_TIME * mS_TO_S_FACTOR);
        }
        disp.clearBuffer();
        draw();
        previousScreenName = currentScreen.screenName;
        disp.sendBuffer();
        if(queuePtr != NULL && uxQueueMessagesWaiting(queuePtr) > 0) {
            uint8_t message;
            xQueueReceive(queuePtr, &message, 1);
            if(message == NULL || message <= 0) {
                continue;
            } else {
                switch (message) {
                    case ACTION_OLED_ON:
                        turnOnFor(DISPLAY_TURN_ON_TIME * mS_TO_S_FACTOR);
                        break;
                    default:
                        Serial.printf("Unknown queuePtr action: %u\r\n", message);
                        break;
                }
            }
        }
        vTaskDelay(DISPLAY_REFRESH_RATE_DELAY_MS / portTICK_PERIOD_MS);
    }
}