/***************************************************
  This is a library for the PCA9685 LED PWM Driver

  This chip is connected via I2C, 2 pins are required to interface. The PWM frequency is set for all pins, the PWM for each individually. The set PWM is active as long as the chip is powered.

  Written by Jonas Scharpf <jonas@brainelectronics.de>
  BSD license, all text above must be included in any redistribution
 ****************************************************/
/***************************************************
  Heavily modified version to meet custom requirements.
  Will migrate to PCA9432DP1 soon but using PCA9685 for prototyping.
  Noncommercial use only.
  Modified by Luca Camphuisen <luca@camphuisen.com>
 ****************************************************/
#ifndef POWERMCU_LED_PWM_DRIVER_H
#define POWERMCU_LED_PWM_DRIVER_H

#include <cstdint>
#include <driver/i2c.h>
#include <cmath>
#include "esp_err.h"
#include <cerrno>
#include "esp_log.h"
#include "esp_system.h"
#include <freertos/FreeRTOS.h>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include "config-leddriver.h"
#include "config-i2c.h"

namespace LedDriver {

    /**
     * @brief Sets the slave i2c address which is our led driver.
     * @param addr i2c address. Can be obtained through i2c scanner sketch: https://www.esp32.com/viewtopic.php?t=4742
     */
    extern void setI2CAddress(uint8_t addr);

    /**
     * @brief Resets driver device
     * @return any error thrown while resetting.
     */
    extern esp_err_t resetLedDriver(void);

    /**
     * @brief Sets the i2c led driver frequency
     * @param freq i2c frequency
     * @return when something failed setting the i2c frequency
     */
    extern esp_err_t setI2CLedDriverFrequency(uint16_t freq);

    /**
     * Set all channels on the driver to LOW
     * @return when something failed to set all to low.
     */
    extern esp_err_t turnAllOff(void);

    /**
     * @brief sets the PWM of the specified channel(num) of the driver device.
     * @param num channel number
     * @param on duty cycle on(max 4096)
     * @param off duty cycle off(max 4096)
     * @return any error that may occur during the setting of the PWM signal.
     */
    extern esp_err_t setPWM(uint8_t num, uint16_t on, uint16_t off);

    /**
     * @brief Sets a channel either fully on or fully off depending on state.
     * @param num i2c channel num
     * @param value new channel value
     * @return
     */
    extern esp_err_t setLevel(uint8_t num, bool value);

    /**
     * @brief      Gets the pwm of a pin detail
     *
     * Have read each LED0_ON_L and LED0_OFF_L seperate
     *
     * @param[in]  num           The number
     * @param      dataReadOn0   The data read on 0
     * @param      dataReadOn1   The data read on 1
     * @param      dataReadOff0  The data read off 0
     * @param      dataReadOff1  The data read off 1
     *
     * @return     result of command
     */
    extern esp_err_t
    getPWMDetail(uint8_t num, uint8_t *dataReadOn0, uint8_t *dataReadOn1, uint8_t *dataReadOff0, uint8_t *dataReadOff1);

    /**
     * @brief      Gets the pwm of a pin
     *
     * @param[in]  num      The number
     * @param      dataOn   The data on
     * @param      dataOff  The data off
     *
     * @return     result of command
     */
    extern esp_err_t getPWM(uint8_t num, uint16_t *dataOn, uint16_t *dataOff);

    /**
     * @brief Fades a channel on the driver up and down using PWM.
     * @param [in] pin i2c driver channel
     * @return when something fails during fade.
     */
    extern esp_err_t fadePinUpDown(uint8_t pin);

    /**
     * @brief Fades a channel on the driver up and down using PWM.
     * @param [in] pin i2c driver channel
     * @param [in] delay delay between each fading step.
     * @return when something fails during fade.
     */
    extern esp_err_t fadePinUpDown(uint8_t pin, uint16_t delay);

    /**
     * @brief Fades all channels on the driver up and down using PWM.
     * @return when something fails during fade.
     */
    extern esp_err_t fadeAllUpDown(void);

    /**
     * @brief Fades all channels on the driver up and down using PWM.
     * @param [in] delayTime delay between each fading step.
     * @return when something fails during fade.
     */
    extern esp_err_t fadeAllUpDown(uint16_t delayTime);

    extern esp_err_t genericWriteI2CRegisterTwoWords(uint8_t regaddr, uint16_t valueOn, uint16_t valueOff);

    extern esp_err_t genericWriteI2CRegisterWord(uint8_t regaddr, uint16_t value);

    extern esp_err_t genericWriteI2CRegister(uint8_t regaddr, uint8_t value);

    extern esp_err_t genericReadI2CRegisterWord(uint8_t regaddr, uint16_t *value);

    extern esp_err_t genericReadTwoI2CRegister(uint8_t regaddr, uint8_t *valueA, uint8_t *valueB);

    /**
     * @brief Prints buffer to serial
     * @param [in] buf buffer to display
     * @param [in] len length of the buffer to display.
     */
    extern void displayBuffer(uint16_t *buf, uint8_t len);
}
#endif /* POWERMCU_LED_PWM_DRIVER_H */
