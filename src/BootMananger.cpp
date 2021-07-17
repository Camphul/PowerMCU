//
// Created by luca on 7/12/21.
//
#include "config.h"
#include "pins.h"
#include <Arduino.h>
#include "BootMananger.h"
#include "esp32-hal-gpio.h"
#include "driver/rtc_io.h"
#include "ServicesContainer.h"

static ServicesContainer servicesContainer;

BootMananger::BootMananger() {
}

/**
 * Sets softlatch to high to keep fet open
 * @return
 */
BootResponse BootMananger::coreBootInit() {
    gpio_set_direction(SOFTLATCH_OUTPUT_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(SOFTLATCH_OUTPUT_PIN, HIGH);
    gpio_hold_en(SOFTLATCH_OUTPUT_PIN);
    gpio_set_direction(SOFTLATCH_BTN_PIN, GPIO_MODE_INPUT);
    //rtc_gpio_set_direction(SOFTLATCH_BTN_PIN, RTC_GPIO_MODE_INPUT_ONLY);
    //rtc_gpio_pulldown_en(SOFTLATCH_BTN_PIN);
    gpio_set_pull_mode(SOFTLATCH_BTN_PIN, GPIO_PULLDOWN_ONLY);
    esp_sleep_enable_ext0_wakeup(SOFTLATCH_BTN_PIN, HIGH);
    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    return BOOT_SECTION_OK;
}

BootResponse BootMananger::registerBasicIO() {
    gpio_set_direction(LEDRING_PIN, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(LEDRING_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_direction(SAFESHUTDOWN_WARN_PIN, GPIO_MODE_OUTPUT);
    gpio_set_pull_mode(SAFESHUTDOWN_WARN_PIN, GPIO_PULLDOWN_ONLY);
    gpio_set_level(SAFESHUTDOWN_WARN_PIN, HIGH);
    gpio_hold_en(SAFESHUTDOWN_WARN_PIN);
    gpio_set_level(LEDRING_PIN, HIGH);
    delay(2000);
    gpio_set_level(LEDRING_PIN, LOW);
    return BOOT_SECTION_OK;
}

BootResponse BootMananger::registerIIC() {
    return BOOT_SECTION_OK;
}

BootResponse BootMananger::initTasksAndServices() {
    Serial.begin(CONFIG_CONSOLE_UART_BAUDRATE);
    Serial2.begin(HWSERIAL_2_BAUDRATE, HWSERIAL_2_CONF, RXD2, TXD2);
    servicesContainer.registerServices();
    return BOOT_SECTION_OK;
}

void BootMananger::sysInit() {
    BootResponse bootResponse = startSequence();
    if (bootResponse != BOOT_OK) {
        //Boot failed lets try restart
        esp_restart();
    }
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