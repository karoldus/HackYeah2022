#ifndef MOISTURE_SENSOR_H_  
#define MOISTURE_SENSOR_H_

#include <stdio.h>
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include <stdlib.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"


uint32_t get_ms_moisture(void);
void set_ms_adc(void);

#endif