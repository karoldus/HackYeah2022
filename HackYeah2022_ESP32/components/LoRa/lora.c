#include "lora.h"
#include "uart_driver.h"

#define CONFIGURE_DELAY_MS 1000
#define JOIN_DELAY_MS 500

static const char *TAG = "LoRa";
// static const int RX_BUF_SIZE = 1024;
static const int TX_BUF_SIZE = 1024;
static TaskHandle_t *rx_task_handle;

static const char *dev_eui = "70B3D57ED0057A60";
static const char *app_eui = "0000000000000000";
static const char *app_key = "88AC67FE315F73B300DA6B5B0C9854FF";

esp_err_t lora_configure(void)
{
    char tx_buf[TX_BUF_SIZE];

    snprintf(tx_buf, TX_BUF_SIZE, "AT+ID=DevEui, \"%s\"\r\n", dev_eui);
    uart_driver_send(TAG, tx_buf);
    vTaskDelay(CONFIGURE_DELAY_MS / portTICK_PERIOD_MS);
    
    snprintf(tx_buf, TX_BUF_SIZE, "AT+ID=AppEui, \"%s\"\r\n", app_eui);
    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT, pdTRUE, pdFALSE, CONFIGURE_DELAY_MS);
    uart_driver_send(TAG, tx_buf);
    vTaskDelay(CONFIGURE_DELAY_MS / portTICK_PERIOD_MS);

    snprintf(tx_buf, TX_BUF_SIZE, "AT+KEY=APPKEY, \"%s\"\r\n", app_key);
    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT, pdTRUE, pdFALSE, CONFIGURE_DELAY_MS);
    uart_driver_send(TAG, tx_buf);
    vTaskDelay(CONFIGURE_DELAY_MS / portTICK_PERIOD_MS);

    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT, pdTRUE, pdFALSE, CONFIGURE_DELAY_MS);
    uart_driver_send(TAG, "AT+DR=EU868\r\n");   
    vTaskDelay(CONFIGURE_DELAY_MS / portTICK_PERIOD_MS);

    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT, pdTRUE, pdFALSE, CONFIGURE_DELAY_MS);
    uart_driver_send(TAG, "AT+CH=NUM,0-2\r\n");   
    vTaskDelay(CONFIGURE_DELAY_MS / portTICK_PERIOD_MS);

    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT, pdTRUE, pdFALSE, CONFIGURE_DELAY_MS);
    uart_driver_send(TAG, "AT+MODE=LWOTAA\r\n");   
    vTaskDelay(CONFIGURE_DELAY_MS / portTICK_PERIOD_MS);
    
    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT, pdTRUE, pdFALSE, CONFIGURE_DELAY_MS);
    uart_driver_send(TAG, "AT+JOIN\r\n");    
    vTaskDelay(CONFIGURE_DELAY_MS / portTICK_PERIOD_MS);

    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT, pdTRUE, pdFALSE, CONFIGURE_DELAY_MS);
    uart_driver_send(TAG, "AT+MSGHEX=\"a1b2c3\"\r\n");     
    vTaskDelay(CONFIGURE_DELAY_MS / portTICK_PERIOD_MS);  

    return ESP_OK;
}

esp_err_t lora_init(void)
{
    // create rx task
    uart_driver_event_group = xEventGroupCreate();
    xTaskCreate(uart_driver_rx_task, "uart_driver_rx_task", 2048, NULL, 10, rx_task_handle);

    return ESP_OK;
}

esp_err_t lora_join(void)
{
    uart_driver_send(TAG, "AT+JOIN=FORCE\r\n");
    vTaskDelay(JOIN_DELAY_MS / portTICK_PERIOD_MS);
    return ESP_OK;
}

esp_err_t lora_send_data(char *payload)
{
    char tx_buf[TX_BUF_SIZE];
    snprintf(tx_buf, TX_BUF_SIZE, "AT+MSG=\"%s\"\r\n", payload);
    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT | NETWORK_JOINED_BIT, pdTRUE, pdTRUE, CONFIGURE_DELAY_MS);
    uart_driver_send(TAG, tx_buf); 

    return ESP_OK;
}

esp_err_t lora_send_data_hex(char *payload)
{
    xEventGroupWaitBits(uart_driver_event_group, UART_FREE_BIT, pdTRUE, pdFALSE, CONFIGURE_DELAY_MS);
    char tx_buf[TX_BUF_SIZE];
    snprintf(tx_buf, TX_BUF_SIZE, "AT+MSGHEX=\"%s\"\r\n", payload);
    uart_driver_send(TAG, tx_buf); 

    return ESP_OK;
}