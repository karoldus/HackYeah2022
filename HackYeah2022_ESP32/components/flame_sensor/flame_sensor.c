#include "flame_sensor.h"

#define FLAME_SENSOR_PIN 5

volatile bool my_flag = false;

static void IRAM_ATTR flame_sensor_intr_handler(void *arg)
{
    my_flag = true;
    // WAKE UP & ALARM
}

esp_err_t flame_sensor_init()
{
    gpio_reset_pin(FLAME_SENSOR_PIN);
    gpio_set_direction(FLAME_SENSOR_PIN, GPIO_MODE_INPUT);
    gpio_pullup_en(FLAME_SENSOR_PIN);

    gpio_set_intr_type(FLAME_SENSOR_PIN, GPIO_INTR_ANYEDGE);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(FLAME_SENSOR_PIN, flame_sensor_intr_handler, NULL);

    return ESP_OK;
}

// void test_task(void *arg)
// {
//     while (1)
//     {
//         if (my_flag)
//         {
//             printf("Alarm!\n");
//             my_flag = false;
//         }
//     }
// }