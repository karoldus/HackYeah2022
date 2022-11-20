#ifndef __LORA_H__
#define __LORA_H__

#include "esp_err.h"

esp_err_t lora_configure(void);

esp_err_t lora_init(void);

esp_err_t lora_join(void);

esp_err_t lora_send_data(char *payload);

esp_err_t lora_send_data_hex(char *payload);

#endif