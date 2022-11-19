#ifndef __LORA_H__
#define __LORA_H__

#include "esp_err.h"

esp_err_t lora_send_data(char *payload, size_t payload_size);

#endif