# For more information about build system see
# https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html
# The following five lines of boilerplate have to be in your project's
# CMakeLists in this exact order for cmake to work correctly
cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
set(EXTRA_COMPONENT_DIRS components/DHT22)
set(EXTRA_COMPONENT_DIRS components/flame_sensor)
set(EXTRA_COMPONENT_DIRS components/LoRa)
set(EXTRA_COMPONENT_DIRS components/Moisture_sensor)
set(EXTRA_COMPONENT_DIRS components/Beacon)
set(EXTRA_COMPONENT_DIRS components/MQ2)
set(EXTRA_COMPONENT_DIRS components/BLE_driver)


project(HackYeah2022_ESP32)
