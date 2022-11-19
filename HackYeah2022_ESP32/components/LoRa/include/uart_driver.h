#ifndef __UART_DRIVER_H__
#define __UART_DRIVER_H__

#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "esp_system.h"
#include "esp_log.h"
#include "driver/uart.h"
#include "string.h"
#include "driver/gpio.h"
#include "esp_event.h"

#define UART_FREE_BIT BIT0
#define NETWORK_JOINED_BIT BIT1

void uart_driver_tx_task(void *arg);

void uart_driver_rx_task(void *arg);

int uart_driver_send(const char* logName, const char* data);

void uart_driver_init(void);

EventGroupHandle_t uart_driver_event_group;

#endif