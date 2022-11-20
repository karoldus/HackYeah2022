#include <stdio.h>

#include "moisture.h"
#include "MQ2.h"
#include "DHT22.h"
#include "uart_driver.h"
#include "lora.h"
#include "flame_sensor.h"
#include "ble_beacon_scanner.h"

#define SLEEP_DELAY 100000
#define LORA_TX_BUFFER_SIZE 1024

static const char *TAG = "MAIN";

char *tx_buffer;

static esp_err_t sensors_init(void)
{
    set_ms_adc();
    set_MQ2_adc();
    flame_sensor_init();
    setDHTgpio(DHT_DATA_PIN);

    init_ble_beacon_scan();

    return ESP_OK;
}

static esp_err_t prepare_the_message(char *buffer,
                                        int moisture,
                                        int smoke, 
                                        bool flame,
                                        float temperature,
                                        float humidity)
{
    sprintf(buffer, "%d,%d,%d,%.1f,%.1f", moisture, smoke, flame, temperature, humidity);

    return ESP_OK;
}

void app_main(void)
{
    sensors_init();
    uart_driver_init();
    if (lora_init() == ESP_OK)
    {
        lora_join();
    }
    else
    {
        ESP_LOGE(TAG, "Failed to init lora, aborting...");
        abort();
    }

    uint32_t moisture;
    uint32_t smoke;
    bool flame;
    float temperature;
    float humidity;
    char buf[30] = {" "};
    while (1)
    {

        moisture = get_ms_moisture();
        printf("Moisture in mV : %d\r\n", moisture);
        for (int i = 0; i < 30; i++)
        {
            buf[i] = " ";
        }
        sprintf(buf, "\"moisture\":%d", (int)moisture);
        // lora_send_data(buf);
        vTaskDelay(pdMS_TO_TICKS(SLEEP_DELAY / portTICK_PERIOD_MS));

        smoke = get_MQ2_smoke();
        printf("Smoke in mV : %d\r\n", smoke);
        for (int i = 0; i < 30; i++)
        {
            buf[i] = " ";
        }
        sprintf(buf, "\"smoke\":%d\r\n", (int)smoke);
        // lora_send_data(buf);
        vTaskDelay(pdMS_TO_TICKS(SLEEP_DELAY / portTICK_PERIOD_MS));

        flame = flame_sensor_read();
        printf("Flame: %d\r\n", flame);
        for (int i = 0; i < 30; i++)
        {
            buf[i] = " ";
        }
        sprintf(buf, "\"flame\":%d\r\n", (int)flame);
        // lora_send_data(buf);
        vTaskDelay(pdMS_TO_TICKS(SLEEP_DELAY / portTICK_PERIOD_MS));

        temperature = getTemperature();
        // snprintf(temperature_buf, TEMP_HUM_BUF_SIZE, "%.1f C", temperature);
        printf("Temperature: %.1f C\r\n", temperature);
        // lora_send_data(temperature);
        vTaskDelay(pdMS_TO_TICKS(SLEEP_DELAY / portTICK_PERIOD_MS));

        humidity = getHumidity();
        // snprintf(humidity_buf, TEMP_HUM_BUF_SIZE, "%.1f %%", humidity);
        printf("Humidity: %1.f %%\r\n", humidity);
        // lora_send_data(humidity);
        vTaskDelay(pdMS_TO_TICKS(SLEEP_DELAY / portTICK_PERIOD_MS));

        tx_buffer = malloc(LORA_TX_BUFFER_SIZE * sizeof(char));
        prepare_the_message(tx_buffer, moisture, smoke, flame, temperature, humidity);
        printf("Data to send: %s\n", tx_buffer);
        lora_send_data(tx_buffer);
        free(tx_buffer);
        vTaskDelay(pdMS_TO_TICKS(SLEEP_DELAY / portTICK_PERIOD_MS));
    }
}
