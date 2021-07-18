//
// Created by luca on 7/18/21.
//

#include "Arduino.h"
#include "TaskLedController.h"
#include "LedControl.h"
#include <esp_log.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "driver/i2c.h"
#define I2C_SDA GPIO_NUM_21
#define I2C_SCL GPIO_NUM_22
#define I2C_FREQ 100000
#undef ESP_ERROR_CHECK
#define ESP_ERROR_CHECK(x)   do { esp_err_t rc = (x); if (rc != ESP_OK) { ESP_LOGE("err", "esp_err_t = %d", rc); assert(0 && #x);} } while(0);
#define I2C_EXAMPLE_MASTER_TX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define I2C_EXAMPLE_MASTER_RX_BUF_DISABLE   0   /*!< I2C master do not need buffer */
#define LEDCONTROL_I2C_ADDR 0x40
SemaphoreHandle_t drvMutex = xSemaphoreCreateMutex();
static void i2c_example_master_init(void)
{
    ESP_LOGD(tag, ">> PCA9685");
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_SDA;
    conf.scl_io_num = I2C_SCL;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = I2C_FREQ;

    ESP_ERROR_CHECK(i2c_param_config(I2C_NUM_0, &conf));
    ESP_ERROR_CHECK(i2c_driver_install(I2C_NUM_0, conf.mode,
                                       I2C_EXAMPLE_MASTER_RX_BUF_DISABLE,
                                       I2C_EXAMPLE_MASTER_TX_BUF_DISABLE, 0));
}
void taskLedController(void * args) {
    Serial.println("Started taskLedController");
    xSemaphoreTake(drvMutex, portMAX_DELAY);
    i2c_example_master_init();
    delay(50);
    set_pca9685_adress(0x40);
    resetPCA9685();
    setFrequencyPCA9685(1000);  // 1000 Hz
    turnAllOff();
    xSemaphoreGive(drvMutex);
    vTaskDelay(50/portTICK_PERIOD_MS);
    while(1) {
        esp_err_t ret;
        // fade up and down each pin with static logarithmic table
        // see Weber Fechner Law
        ret = fade_all_up_down();

        if (ret == ESP_ERR_TIMEOUT) {
            Serial.printf("I2C timeout\n");
        } else if (ret == ESP_OK) {
            // all good
        } else {
            Serial.printf("No ack, sensor not connected...skip...\n");
        }

        vTaskDelay(50 / portTICK_RATE_MS);

        printf("Blink all pins starting from 0\n");

        for (uint8_t pin = 0; pin < 3; pin++) {
            Serial.printf("Turn LED %d on\n", pin);
            setPWM(pin, 4096, 0);

            if (ret == ESP_ERR_TIMEOUT) {
                printf("I2C timeout\n");
            } else if (ret == ESP_OK) {
                // all good
            } else {
                printf("No ack, sensor not connected...skip...\n");
            }

            vTaskDelay(1000 / portTICK_PERIOD_MS);

            Serial.printf("Turn LED %d off\n", pin);
            setPWM(pin, 0, 4096);
        }
    }
}
