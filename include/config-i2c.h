//
// Created by luca on 7/18/21.
// Config dedicated to i2c related configurations
//

#ifndef POWERMCU_CONFIG_I2C_H
#define POWERMCU_CONFIG_I2C_H

#define I2C_SDA GPIO_NUM_21
#define I2C_SCL GPIO_NUM_22
#define I2C_FREQ 100000

#undef ESP_ERROR_CHECK
#define ESP_ERROR_CHECK(x)   do { esp_err_t rc = (x); if (rc != ESP_OK) { ESP_LOGE("err", "esp_err_t = %d", rc); assert(0 && #x);} } while(0);
#define I2C_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */

#define I2C_ADDRESS_LED_PWM_DRIVER 0x40

#endif //POWERMCU_CONFIG_I2C_H
