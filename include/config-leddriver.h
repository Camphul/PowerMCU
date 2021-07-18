//
// Created by luca on 7/18/21.
// Contains definitions used by LedPWMDriver
//

#ifndef POWERMCU_CONFIG_LEDDRIVER_H
#define POWERMCU_CONFIG_LEDDRIVER_H


// #define CONTROLLER_ADDRESS     0x50    /*!< slave address for PCA9685 chip */
#define ACK_CHECK_EN    0x1     /*!< I2C master will check ack from slave */
#define ACK_CHECK_DIS   0x0     /*!< I2C master will not check ack from slave */
#define ACK_VAL         I2C_MASTER_ACK     /*!< I2C ack value */
#define NACK_VAL        I2C_MASTER_NACK    /*!< I2C nack value */
#define MODE1           0x00    /*!< Mode register 1 */
#define MODE2           0x01    /*!< Mode register 2 */
#define SUBADR1         0x02    /*!< I2C-bus subaddress 1 */
#define SUBADR2         0x03    /*!< I2C-bus subaddress 2 */
#define SUBADR3         0x04    /*!< I2C-bus subaddress 3 */
#define ALLCALLADR      0x05    /*!< LED All Call I2C-bus address */
#define LED0            0x6     /*!< LED0 start register */
#define LED0_ON_L       0x6     /*!< LED0 output and brightness control byte 0 */
#define LED0_ON_H       0x7     /*!< LED0 output and brightness control byte 1 */
#define LED0_OFF_L      0x8     /*!< LED0 output and brightness control byte 2 */
#define LED0_OFF_H      0x9     /*!< LED0 output and brightness control byte 3 */
#define LED_MULTIPLYER  4       /*!< For the other 15 channels */
#define ALLLED_ON_L     0xFA    /*!< load all the LEDn_ON registers, byte 0 (turn 0-7 channels on) */
#define ALLLED_ON_H     0xFB    /*!< load all the LEDn_ON registers, byte 1 (turn 8-15 channels on) */
#define ALLLED_OFF_L    0xFC    /*!< load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off) */
#define ALLLED_OFF_H    0xFD    /*!< load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off) */
#define PRE_SCALE       0xFE    /*!< prescaler for output frequency */
#define HZ_TO_MHZ_SCALER 1000000 /* conversion used to convert cpu mhz which is given in hz to MHZ*/
#define USED_PWM_CHANNELS 3
#define AVAILABLE_PWM_CHANNELS 16
#define PWM_VALUE_MIN 0
#define PWM_VALUE_MAX 4096
#define PWM_DEFAULT_FADING_DELAY 5
#define PWM_DRIVER_FREQ_MAX 1526

typedef enum {
    CHANNEL_HIGH,
    CHANNEL_LOW,
} led_binary_state_t;
#define CHANNEL_HIGH true
#define CHANNEL_LOW false
#endif //POWERMCU_CONFIG_LEDDRIVER_H
