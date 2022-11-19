#include <stdio.h>
#include "moisture.h"
void app_main(void)
{
    uint32_t moisture;
    set_ms_adc();
    while (1)
    {
        moisture = get_ms_moisture();
        printf("Moisture in mV : %d\r\n",moisture);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
