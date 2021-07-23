//
// Created by luca on 7/12/21.
//
#include "config.h"
#include "driver/i2c.h"
#include "config-i2c.h"
#include "pins.h"
#include <Arduino.h>
#include "BootMananger.h"
#include "esp32-hal-gpio.h"
#include "driver/rtc_io.h"
#include "ServicesContainer.h"
#include "LedPWMDriver.h"
#include "StatusDisplay.h"
#include "CapacitiveTouchHandle.h"
#include "esp32-hal-log.h"

static ServicesContainer servicesContainer;

BootMananger::BootMananger() {
}

/**
 * Sets softlatch to high to keep fet open
 * @return
 */
BootResponse BootMananger::coreBootInit() {
    try {
        gpio_set_direction(SOFTLATCH_OUTPUT_PIN, GPIO_MODE_OUTPUT);
        gpio_set_level(SOFTLATCH_OUTPUT_PIN, HIGH);
        gpio_hold_en(SOFTLATCH_OUTPUT_PIN);
        gpio_set_direction(SOFTLATCH_BTN_PIN, GPIO_MODE_INPUT);
        gpio_set_pull_mode(SOFTLATCH_BTN_PIN, GPIO_PULLDOWN_ONLY);
        //gpio_set_direction(OLED_TOUCH_WAKEUP_PIN, GPIO_MODE_INPUT);
        esp_sleep_enable_ext0_wakeup(SOFTLATCH_BTN_PIN, HIGH);
        gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    } catch (std::exception &e ) {
        ESP_LOGE(e.what());
        return BOOT_SECTION_FAILED;
    }
    return BOOT_SECTION_OK;
}

BootResponse BootMananger::registerBasicIO() {
    try {
        gpio_set_direction(SAFESHUTDOWN_WARN_PIN, GPIO_MODE_OUTPUT);
        gpio_set_pull_mode(SAFESHUTDOWN_WARN_PIN, GPIO_PULLDOWN_ONLY);
        gpio_set_level(SAFESHUTDOWN_WARN_PIN, HIGH);
        gpio_hold_en(SAFESHUTDOWN_WARN_PIN);
        ESP_LOGI("RegisterBasicIOTouch", "Initializing touch pad");
        ESP_ERROR_CHECK(touch_pad_init());
        ESP_ERROR_CHECK(touch_pad_set_fsm_mode(TOUCH_FSM_MODE_TIMER));
        ESP_ERROR_CHECK(touch_pad_set_voltage(TOUCH_HVOLT_2V7, TOUCH_LVOLT_0V5, TOUCH_HVOLT_ATTEN_1V));
        ESP_ERROR_CHECK(touch_pad_set_trigger_mode(OLED_TOUCH_CAPACITIVE_TRIGGERMODE));
        ESP_ERROR_CHECK(touch_pad_filter_start(OLED_TOUCH_CAPACITIVE_PERIOD));
        ESP_ERROR_CHECK(touch_pad_set_filter_period(OLED_TOUCH_CAPACITIVE_PERIOD));
        ESP_ERROR_CHECK(touch_pad_config(OLED_TOUCH_WAKEUP_PAD, OLED_TOUCH_CAPACITIVE_THRESHOLD));
        ESP_ERROR_CHECK(touch_pad_isr_register(CapacitiveTouch::handleTouch, NULL));
        ESP_ERROR_CHECK(touch_pad_intr_enable());
        ///touchAttachInterrupt(OLED_TOUCH_WAKEUP_PIN, CapacitiveTouch::handleTouch, OLED_TOUCH_CAPACITIVE_THRESHOLD);
    } catch (std::exception &e ) {
        ESP_LOGE(e.what());
        return BOOT_SECTION_FAILED;
    }
    return BOOT_SECTION_OK;
}

BootResponse BootMananger::registerIIC() {
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_SDA;
    conf.scl_io_num = I2C_SCL;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_FREQ;

    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, conf.mode,
                                       I2C_MASTER_RX_BUF_DISABLE,
                                       I2C_MASTER_TX_BUF_DISABLE, 0));
    //OLED DISPLAY BELOW
    StatusDisplay::setI2CAddress(I2C_ADDRESS_OLED_DISPLAY);
    //LED DRIVER BELOW
    LedDriver::setI2CAddress(I2C_ADDRESS_LED_PWM_DRIVER);
    LedDriver::setI2CLedDriverFrequency(PWM_DRIVER_FREQ_MAX);
    esp_err_t ret = LedDriver::turnAllOff();
    if (ret != ESP_OK) {
#if IS_DEBUG
        Serial.printf("Failed boot due to led driver not turning off all. Error: %u", ret);
#endif
        ESP_LOGE("Failed to turn all led's off from led driver.");
        return BOOT_SECTION_FAILED;
    }
    ret = LedDriver::fadePinUpDown(LEDRING_R_PIN);
    if (ret != ESP_OK) {
#if IS_DEBUG
        Serial.printf("Welcomes fade failed. Error: %u", ret);
#endif
        ESP_LOGE("Failed to fade ledring color r");
        return BOOT_SECTION_FAILED;
    }
    return BOOT_SECTION_OK;
}

BootResponse BootMananger::initTasksAndServices() {
    try {
        Serial.begin(CONFIG_CONSOLE_UART_BAUDRATE);
        Serial2.begin(HWSERIAL_2_BAUDRATE, HWSERIAL_2_CONF, RXD2, TXD2);
        servicesContainer.registerServices();
    } catch (std::exception &e) {
        ESP_LOGE(e.what());
        return BOOT_SECTION_FAILED;
    }
    return BOOT_SECTION_OK;
}

void BootMananger::sysInit() {
    BootResponse bootResponse = startSequence();
    if (bootResponse != BOOT_OK) {
        //Boot failed lets try restart
        esp_restart();
    }
    StatusDisplay::turnOnFor(DISPLAY_TURN_ON_TIME * mS_TO_S_FACTOR);
    // Boot has finished
}

BootResponse BootMananger::startSequence() {
    if (coreBootInit() != BOOT_SECTION_OK) {
        return BOOT_FAILED;
    }
    if (registerBasicIO() != BOOT_SECTION_OK) {
        return BOOT_FAILED;
    }
    if (registerIIC() != BOOT_SECTION_OK) {
        return BOOT_FAILED;
    }
    if (initTasksAndServices() != BOOT_SECTION_OK) {
        return BOOT_FAILED;
    }
    return BOOT_OK;
}