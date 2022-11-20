#include <stdio.h>

#include "moisture.h"
#include "MQ2.h"
#include "DHT22.h"
#include "uart_driver.h"
#include "lora.h"
#include "flame_sensor.h"
#include "ble_beacon_scanner.h"

#define SLEEP_DELAY 100000
#define JSON_TX_BUFFER_SIZE 1024
#define TEMP_HUM_BUF_SIZE 20

static const char *TAG = "MAIN";

static char json_tx_buffer[JSON_TX_BUFFER_SIZE];

static esp_err_t sensors_init(void)
{
    set_ms_adc();
    set_MQ2_adc();
    flame_sensor_init();
    setDHTgpio(DHT_DATA_PIN);
    
    init_ble_beacon_scan();

    return ESP_OK;
}

static void prepare_the_json_data(char *buffer,
                                    int buffer_size,
                                    uint32_t moisture,
                                    uint32_t smoke, 
                                    bool flame,
                                    char *temperature,
                                    char *humidity)
{
    snprintf(buffer, buffer_size, "{\"moisture\": %d, \"smoke\": %d, \"flame\": %d, \"temperature\": \"%s\", \"humidity\": \"%s\"}",
                moisture,
                smoke,
                flame,
                temperature,
                humidity);
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
    char temperature_buf[TEMP_HUM_BUF_SIZE];
    float humidity;
    char humidity_buf[TEMP_HUM_BUF_SIZE];
     while (1)
    {
        // moisture = get_ms_moisture();
        moisture = 0;
        printf("Moisture in mV : %d\r\n", moisture);

        // smoke = get_MQ2_smoke();
        smoke = 0;
        printf("Smoke in mV : %d\r\n", smoke);

        flame = flame_sensor_read();
        printf("Flame: %d\r\n", flame);

        temperature = getTemperature();
        snprintf(temperature_buf, TEMP_HUM_BUF_SIZE, "%.1f C", temperature);
        printf("Temperature: %s\r\n", temperature_buf);

        humidity = getHumidity();
        snprintf(humidity_buf, TEMP_HUM_BUF_SIZE, "%.1f %%", humidity);
        printf("Humidity: %s\r\n", humidity_buf);

        prepare_the_json_data(json_tx_buffer, JSON_TX_BUFFER_SIZE, moisture, smoke, flame, temperature_buf, humidity_buf);

        printf("Data to send: %s\n", json_tx_buffer);
        // lora_send_data(json_tx_buffer);
        lora_send_data(temperature_buf);

        vTaskDelay(pdMS_TO_TICKS(SLEEP_DELAY / portTICK_PERIOD_MS));
    }
}
