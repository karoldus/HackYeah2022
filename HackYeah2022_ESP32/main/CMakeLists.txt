idf_component_register(SRCS "main.c"
                    INCLUDE_DIRS "."
                    REQUIRES LoRa Moisture_sensor MQ2 DHT22 flame_sensor)
