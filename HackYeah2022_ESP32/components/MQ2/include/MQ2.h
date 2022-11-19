 
 
#ifndef MQ2_H_  
#define MQ2_H_

#include <stdio.h>
#include <stdlib.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/adc.h"
#include "esp_adc_cal.h"


void set_MQ2_adc(void);
uint32_t get_MQ2_smoke (void);

#endif
