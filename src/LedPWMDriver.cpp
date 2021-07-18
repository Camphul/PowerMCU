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
#include "LedPWMDriver.h"
#include <freertos/FreeRTOS.h>
#include "driver/i2c.h"
#include <cstdint>
#include <cmath>
#include "esp_err.h"
#include "esp_log.h"
#include "esp32-hal-cpu.h"

using namespace LedDriver;
uint8_t CONTROLLER_ADDRESS = 0x00;
const uint16_t pwmTable[256] = {0, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7,
                                7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10, 11, 11, 11, 12, 12, 12, 13, 13, 13, 14,
                                14, 15, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 21, 21, 22, 22, 23, 24, 24, 25, 26,
                                27, 27, 28, 29, 30, 31, 31, 32, 33, 34, 35, 36, 37, 38, 39, 41, 42, 43, 44, 45, 47, 48,
                                49, 51, 52, 54, 55, 57, 59, 60, 62, 64, 66, 68, 69, 71, 74, 76, 78, 80, 82, 85, 87, 90,
                                92, 95, 98, 100, 103, 106, 109, 112, 116, 119, 122, 126, 130, 133, 137, 141, 145, 149,
                                153, 158, 162, 167, 172, 177, 182, 187, 193, 198, 204, 210, 216, 222, 228, 235, 241,
                                248, 255, 263, 270, 278, 286, 294, 303, 311, 320, 330, 339, 349, 359, 369, 380, 391,
                                402, 413, 425, 437, 450, 463, 476, 490, 504, 518, 533, 549, 564, 581, 597, 614, 632,
                                650, 669, 688, 708, 728, 749, 771, 793, 816, 839, 863, 888, 913, 940, 967, 994, 1023,
                                1052, 1082, 1114, 1146, 1178, 1212, 1247, 1283, 1320, 1358, 1397, 1437, 1478, 1520,
                                1564, 1609, 1655, 1703, 1752, 1802, 1854, 1907, 1962, 2018, 2076, 2135, 2197, 2260,
                                2325, 2391, 2460, 2531, 2603, 2678, 2755, 2834, 2916, 2999, 3085, 3174, 3265, 3359,
                                3455, 3555, 3657, 3762, 3870, 3981, 4095};

/**
 * @brief      Sets the adress where the PCA9685 is located
 *
 * @param[in]  addr  The address
 */
void LedDriver::setI2CAddress(uint8_t addr) {
    CONTROLLER_ADDRESS = addr;
}

/**
 * @brief      Reset the PCA9685
 *
 * @return     result of command
 */
esp_err_t LedDriver::resetLedDriver(void) {
    esp_err_t ret;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CONTROLLER_ADDRESS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, MODE1, ACK_CHECK_EN);   // 0x0 = "Mode register 1"
    i2c_master_write_byte(cmd, 0x80, ACK_CHECK_EN);    // 0x80 = "Reset"
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    vTaskDelay(50 / portTICK_RATE_MS);

    return ret;
}

/**
 * @brief      Write two 16 bit values to the same register on an i2c device
 *
 * @param[in]  regaddr   The register address
 * @param[in]  valueOn   The value on
 * @param[in]  valueOff  The value off
 *
 * @return     result of command
 */
esp_err_t LedDriver::genericWriteI2CRegisterTwoWords(uint8_t regaddr, uint16_t valueOn, uint16_t valueOff) {
    esp_err_t ret;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CONTROLLER_ADDRESS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, valueOn & 0xff, ACK_VAL);
    i2c_master_write_byte(cmd, valueOn >> 8, NACK_VAL);
    i2c_master_write_byte(cmd, valueOff & 0xff, ACK_VAL);
    i2c_master_write_byte(cmd, valueOff >> 8, NACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

/**
 * @brief      Write a 16 bit value to a register on an i2c device
 *
 * @param[in]  regaddr  The register address
 * @param[in]  value    The value
 *
 * @return     result of command
 */
esp_err_t LedDriver::genericWriteI2CRegisterWord(uint8_t regaddr, uint16_t value) {
    esp_err_t ret;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CONTROLLER_ADDRESS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, value & 0xff, ACK_VAL);
    i2c_master_write_byte(cmd, value >> 8, NACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

/**
 * @brief      Write a 8 bit value to a register on an i2c device
 *
 * @param[in]  regaddr  The register address
 * @param[in]  value    The value
 *
 * @return     result of command
 */
esp_err_t LedDriver::genericWriteI2CRegister(uint8_t regaddr, uint8_t value) {
    esp_err_t ret;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CONTROLLER_ADDRESS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, value, NACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_PERIOD_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

/**
 * @brief      Read two 8 bit values from the same register on an i2c device
 *
 * @param[in]  regaddr  The register address
 * @param      valueA   The first value
 * @param      valueB   The second value
 *
 * @return     result of command
 */
esp_err_t LedDriver::genericReadTwoI2CRegister(uint8_t regaddr, uint8_t *valueA, uint8_t *valueB) {
    esp_err_t ret;

    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (CONTROLLER_ADDRESS << 1) | I2C_MASTER_WRITE, ACK_CHECK_EN);
    i2c_master_write_byte(cmd, regaddr, ACK_CHECK_EN);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);
    if (ret != ESP_OK) {
        return ret;
    }
    cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, CONTROLLER_ADDRESS << 1 | I2C_MASTER_READ, ACK_CHECK_EN);
    i2c_master_read_byte(cmd, valueA, ACK_VAL);
    i2c_master_read_byte(cmd, valueB, NACK_VAL);
    i2c_master_stop(cmd);
    ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 1000 / portTICK_RATE_MS);
    i2c_cmd_link_delete(cmd);

    return ret;
}

/**
 * @brief      Read a 16 bit value from a register on an i2c decivde
 *
 * @param[in]  regaddr  The register address
 * @param      value    The value
 *
 * @return     result of command
 */
esp_err_t LedDriver::genericReadI2CRegisterWord(uint8_t regaddr, uint16_t *value) {
    esp_err_t ret;

    uint8_t valueA;
    uint8_t valueB;

    ret = genericReadTwoI2CRegister(regaddr, &valueA, &valueB);
    if (ret != ESP_OK) {
        return ret;
    }

    *value = (valueB << 8) | valueA;

    return ret;
}


/**
 * @brief      Sets the frequency of PCA9685
 *
 * @param[in]  freq  The frequency
 *
 * @return     result of command
 */
esp_err_t LedDriver::setI2CLedDriverFrequency(uint16_t freq) {
    esp_err_t ret;

    // Send to sleep
    ret = genericWriteI2CRegister(MODE1, 0x10);
    if (ret != ESP_OK) {
        return ret;
    }

    // Set prescaler
    // calculation on page 25 of datasheet
    uint32_t cpu_freq = getCpuFrequencyMhz() * HZ_TO_MHZ_SCALER;
    if (cpu_freq == 0) {
        /* DIVIDE BY ZERO IS NOT ALLOWED */
        return ESP_ERR_INVALID_STATE;
    }
    uint8_t prescale_val = round((cpu_freq / 4096 / (0.9 * freq)) - 1 + 0.5);
    ret = genericWriteI2CRegister(PRE_SCALE, prescale_val);
    if (ret != ESP_OK) {
        return ret;
    }

    // reset again
    resetLedDriver();

    // Send to sleep again
    ret = genericWriteI2CRegister(MODE1, 0x10);
    if (ret != ESP_OK) {
        return ret;
    }

    // wait
    vTaskDelay(5 / portTICK_PERIOD_MS);

    // Write 0xa0 for auto increment LED0_x after received cmd
    ret = genericWriteI2CRegister(MODE1, 0xa0);
    if (ret != ESP_OK) {
        return ret;
    }

    // // Read back set data
    // cmd = i2c_cmd_link_create();
    // i2c_master_start(cmd);
    // i2c_master_write_byte(cmd, (CONTROLLER_ADDRESS << 1) | I2C_MASTER_READ, 1);
    // i2c_master_read_byte(cmd, data,   0);
    // i2c_master_read_byte(cmd, data+1, 0);
    // i2c_master_read_byte(cmd, data+2, 1);
    // i2c_master_stop(cmd);
    // ret = i2c_master_cmd_begin(I2C_NUM_0, cmd, 100/portTICK_PERIOD_MS);
    // i2c_cmd_link_delete(cmd);
    // if (ret != ESP_OK) {
    //     return ret;
    // }

    return ret;
}

/**
 * @brief      Sets the pwm of the pin
 *
 * @param[in]  num   The pin number
 * @param[in]  on    On time
 * @param[in]  off   Off time
 *
 * @return     result of command
 */
esp_err_t LedDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
    esp_err_t ret;

    uint8_t pinAddress = LED0_ON_L + LED_MULTIPLYER * num;
    ret = genericWriteI2CRegisterTwoWords(pinAddress & 0xff, on, off);

    return ret;
}


/**
 * @brief Sets a channel either fully on or fully off depending on state.
 * @param num i2c channel num
 * @param value new channel value
 * @return
 */
esp_err_t LedDriver::setLevel(uint8_t num, bool value) {
    switch (value) {
        case CHANNEL_HIGH:
            return setPWM(num, PWM_VALUE_MAX, PWM_VALUE_MIN);
        case CHANNEL_LOW:
            return setPWM(num, PWM_VALUE_MIN, PWM_VALUE_MAX);
        default:
            return ESP_ERR_INVALID_STATE;
    }
}

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
esp_err_t
LedDriver::getPWMDetail(uint8_t num, uint8_t *dataReadOn0, uint8_t *dataReadOn1, uint8_t *dataReadOff0,
                        uint8_t *dataReadOff1) {
    esp_err_t ret;

    uint8_t pinAddress = LED0_ON_L + LED_MULTIPLYER * num;

    ret = genericReadTwoI2CRegister(pinAddress, dataReadOn0, dataReadOn1);
    if (ret != ESP_OK) {
        return ret;
    }

    pinAddress = LED0_OFF_L + LED_MULTIPLYER * num;
    ret = genericReadTwoI2CRegister(pinAddress, dataReadOff0, dataReadOff1);

    return ret;
}

/**
 * @brief      Gets the pwm of a pin
 *
 * @param[in]  num      The number
 * @param      dataOn   The data on
 * @param      dataOff  The data off
 *
 * @return     result of command
 */
esp_err_t LedDriver::getPWM(uint8_t num, uint16_t *dataOn, uint16_t *dataOff) {
    esp_err_t ret;

    uint8_t readPWMValueOn0;
    uint8_t readPWMValueOn1;
    uint8_t readPWMValueOff0;
    uint8_t readPWMValueOff1;

    ret = getPWMDetail(num, &readPWMValueOn0, &readPWMValueOn1, &readPWMValueOff0, &readPWMValueOff1);

    *dataOn = (readPWMValueOn1 << 8) | readPWMValueOn0;
    *dataOff = (readPWMValueOff1 << 8) | readPWMValueOff0;

    return ret;
}

/**
 * @brief      Turn all LEDs off
 *
 * @return     result of command
 */
esp_err_t LedDriver::turnAllOff(void) {
    return genericWriteI2CRegisterTwoWords(ALLLED_ON_L, PWM_VALUE_MIN, PWM_VALUE_MAX);
}

/**
 * @brief      fade pin up to maximum and back down
 *
 * @param[in]  pin   The pin
 *
 * @return     result of command
 */
esp_err_t LedDriver::fadePinUpDown(uint8_t pin) {
    return fadePinUpDown(pin, PWM_DEFAULT_FADING_DELAY);
}

/**
 * @brief      fade pin up to maximum and back down
 *
 * @param[in]  pin   The pin
 * @param[in]  delayTime delay between steps
 * @return     result of command
 */
esp_err_t LedDriver::fadePinUpDown(uint8_t pin, uint16_t delayTime) {
    esp_err_t ret;

    for (uint8_t i = 0; i < 255; i++) {
        // fade up
        ret = setPWM(pin, PWM_VALUE_MIN, pwmTable[i]);
        if (ret != ESP_OK) {
            return ret;
        }

        vTaskDelay(delayTime / portTICK_PERIOD_MS);
    }

    for (uint8_t i = 1/*since we already at the max*/; i < 255; i++) {
        // fade down
        ret = setPWM(pin, pwmTable[i], PWM_VALUE_MIN);
        if (ret != ESP_OK) {
            return ret;
        }

        vTaskDelay(delayTime / portTICK_PERIOD_MS);
    }

    // ensure it's really off
    ret = setLevel(pin, CHANNEL_LOW);
    if (ret != ESP_OK) {
        return ret;
    }
    vTaskDelay(50 / portTICK_PERIOD_MS);

    return ret;
}

/**
 * @brief      fade each pin up to maximum and back down
 *
 * @return     result of command
 */
esp_err_t LedDriver::fadeAllUpDown(void) {
    return fadeAllUpDown(PWM_DEFAULT_FADING_DELAY);
}

/**
* @brief      fade each pin up to maximum and back down
* @param [in] delayTime delaytime between each pwm cycle
* @return     result of command
*/
esp_err_t LedDriver::fadeAllUpDown(uint16_t delayTime) {
    esp_err_t ret;

    for (uint8_t pin = 0; pin < USED_PWM_CHANNELS; pin++) {
        ret = fadePinUpDown(pin, delayTime);
        if (ret != ESP_OK) {
            return ret;
        }
    }

    return ret;
}

/**
 * @brief      test function to show buffer
 *
 * @param      buf   The buffer
 * @param[in]  len   The length
 */
void LedDriver::displayBuffer(uint16_t *buf, uint8_t len) {
    uint8_t i;
    for (i = 0; i < len; i++) {
        printf("%02x ", buf[i]);
        if ((i + 1) % 16 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

