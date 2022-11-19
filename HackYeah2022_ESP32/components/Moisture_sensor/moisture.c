

#define LOG_LOCAL_LEVEL ESP_LOG_VERBOSE




#include "moisture.h"


static const char* TAG = "MS";




static esp_adc_cal_characteristics_t adc1_chars;

void set_ms_adc(void){

        esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_DEFAULT, 0, &adc1_chars);
        ESP_ERROR_CHECK(adc1_config_width(ADC_WIDTH_BIT_DEFAULT));
        ESP_ERROR_CHECK(adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_11));

    }

uint32_t get_ms_moisture (void) 
    {
        uint32_t voltage;
        voltage = esp_adc_cal_raw_to_voltage(adc1_get_raw(ADC1_CHANNEL_6), &adc1_chars);
        ESP_LOGI(TAG, "ADC1_CHANNEL_6: %d mV", voltage);
        return voltage;
    }