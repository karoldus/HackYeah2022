# Happy Forest - HackYeah 2022
We help foresters remotely take care of their forests by a net of devices with sensors measuring environmental conditions.

# Sensor - ESP32
- using esp-idf
- taking measurements from temperature, humidity, flame, smoke and moisture sensors
- sending data using LoRaWAN to The Things Network

# Server - Python
- MQTT paho client subscribing messages from The Things Network and saving payload (data from sensors)
- FastAPI server loading data and exposing URLs for forester webapp
