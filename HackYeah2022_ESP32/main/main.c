#include <stdio.h>
#include "moisture.h"
#include "MQ2.h"
#include "ble_beacon_scanner.h"

void app_main(void)
{
    uint32_t moisture;
    uint32_t smoke;
    init_ble_beacon_scan();
    set_ms_adc();
    set_MQ2_adc();
    while (1)
    {
        moisture = get_ms_moisture();
        printf("Moisture in mV : %d\r\n",moisture);
        vTaskDelay(pdMS_TO_TICKS(1000));
        smoke = get_MQ2_smoke();
        printf("Smoke in mV : %d\r\n",smoke);
        vTaskDelay(pdMS_TO_TICKS(1000));
        scan_ble_beacons();
    }
}
