#include "uart_driver.h"

static const int RX_BUF_SIZE = 1024;

#define TXD_PIN (GPIO_NUM_4)
#define RXD_PIN (GPIO_NUM_5)

void uart_driver_init(void) 
{
    const uart_config_t uart_config = {
        .baud_rate = 9600,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    // We won't use a buffer for sending data.
    uart_driver_install(UART_NUM_1, RX_BUF_SIZE * 2, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_1, &uart_config);
    uart_set_pin(UART_NUM_1, TXD_PIN, RXD_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
}

int uart_driver_send(const char* logName, const char* data)
{
    const int len = strlen(data);
    const int txBytes = uart_write_bytes(UART_NUM_1, data, len);
    ESP_LOGI(logName, "Wrote %d bytes, data wrote: %s", txBytes, data);
    return txBytes;
}

void uart_driver_tx_task(void *arg)
{
    static const char *TX_TASK_TAG = "TX_TASK";
    esp_log_level_set(TX_TASK_TAG, ESP_LOG_INFO);
    while (1) {
        uart_driver_send(TX_TASK_TAG, "AT+JOIN\r\n");
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void uart_driver_rx_task(void *arg)
{
    static const char *RX_TASK_TAG = "RX_TASK";
    ESP_LOGI(RX_TASK_TAG, "uart_driver_rx_task created!");
    esp_log_level_set(RX_TASK_TAG, ESP_LOG_INFO);
    uint8_t* data = (uint8_t*) malloc(RX_BUF_SIZE+1);
    while (1) {
        const int rxBytes = uart_read_bytes(UART_NUM_1, data, RX_BUF_SIZE, 1000 / portTICK_PERIOD_MS);
        if (rxBytes > 0) {
            data[rxBytes] = 0;
            ESP_LOGI(RX_TASK_TAG, "Read %d bytes: '%s'", rxBytes, data);
            ESP_LOG_BUFFER_HEXDUMP(RX_TASK_TAG, data, rxBytes, ESP_LOG_INFO);

            // If modem is not busy, set UART_FREE_BIT
            if (strcmp("Network joined", (const char*)data) == 0)
            {
                xEventGroupSetBits(uart_driver_event_group, NETWORK_JOINED_BIT);
            }
            else 
            {
                ESP_LOGI(RX_TASK_TAG, "Modem is not busy!");
                xEventGroupSetBits(uart_driver_event_group, UART_FREE_BIT);
            }
        }
    }
    free(data);
}