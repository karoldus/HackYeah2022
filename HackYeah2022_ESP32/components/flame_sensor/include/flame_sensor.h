#ifndef __FLAME_SENSOR_H__
#define __FLAME_SENSOR_H__

#include <stdbool.h>

#include "driver/gpio.h"
#include "esp_err.h"

esp_err_t flame_sensor_init(void);

esp_err_t flame_sensor_read(void);

#endif