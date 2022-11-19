import logging
import signal
import json
import json_handler
from time import sleep
import paho.mqtt.client as mqtt
import base64

# Global consts
# TOPICS = {"UP": json_handler.configuration_read("TOPIC_BASE")+"/+/up",
#         "JOIN": json_handler.configuration_read("TOPIC_BASE")+"/+/join",
#         "DOWN": json_handler.configuration_read("TOPIC_BASE")+"/insert_dev_id/down/replace"}

# Initialize Logging
logging.basicConfig(level=logging.WARNING)  # Global logging configuration
logger = logging.getLogger("main")  # Logger for this module
logger.setLevel(logging.INFO) # Debugging for this file.


######################## Analyze messages ######################

def analyze_message(msg):
    """ Analyze message (only uplink) from MQTT (I know, this function is bad)"""
    topic = msg.topic
    payload = json.loads(msg.payload)

    print(payload)

    splitted_topic = topic.split('/')

    extracted_data = {}

    extracted_data['dev_id'] = splitted_topic[3]
   

    if 'up' in splitted_topic[-1]: # uplink in TTS
        extracted_data["message_type"] = 'uplink'
        
        raw_m = payload['uplink_message']['frm_payload']
        bytes_m = base64.b64decode(raw_m.encode())
        # int_m = int.from_bytes(bytes_m, byteorder='big')

        # #payload to list of ints (1 element = 1 byte)
        # tab_m = []
        # while int_m > 0:
        #     tab_m.insert(0,int_m%256)
        #     int_m = int(round(int_m / 256, 0))


        # UP_ORDER = {1: ['ambient_temp', 1], 2: ['sky_temp', 1]}

        # fields = tab_m.pop(0)

        # for i in range(1,9):
        #     if (fields & (1 << (i-1))): # if i byte in payload is not empty
        #         if i in UP_ORDER.keys(): # if i in list of uplink elements
        #             t = 0
        #             e = UP_ORDER[i]
        #             for j in range(e[1]):
        #                 t = t + tab_m.pop(0)
        #             extracted_data[e[0]] = t

        # if 'ambient_temp' in extracted_data.keys():
        #     extracted_data['ambient_temp'] = extracted_data['ambient_temp'] - 100

        # if 'sky_temp' in extracted_data.keys():
        #     extracted_data['sky_temp'] = extracted_data['sky_temp'] - 100

        # if 'ambient_temp' in extracted_data.keys() and 'sky_temp' in extracted_data.keys():
        #     extracted_data['delta_temp'] = extracted_data['ambient_temp'] - extracted_data['sky_temp']
        #     if extracted_data['delta_temp'] < 10:
        #         extracted_data['status'] = 3
        #     elif extracted_data['delta_temp'] < 25:
        #         extracted_data['status'] = 2
        #     elif extracted_data['delta_temp'] < 40:
        #         extracted_data['status'] = 1
        #     else:
        #         extracted_data['status'] = 0

        #     db.send_data_to_influxdb(extracted_data)
        
        # print(extracted_data)      
        # return extracted_data
    else:
        return {}

    


######################## MQTT Subscribe Callbacks ######################

def on_connect(client, user_data, flags, connection_result_code):
    """on_connect is called when our program connects to the MQTT Broker."""

    if connection_result_code == 0: # 0 = successful connection
        logger.info("Connected to MQTT Broker")
    else:
        logger.error("Failed to connect to MQTT Broker: " + mqtt.connack_string(connection_result_code)) # connack_string() gives us a user friendly string for a connection code.

    # Subscribe to the topic(s))
    TOPICS_S = json_handler.configuration_read('TOPIC_BASE')

    client.subscribe(TOPICS_S+"/#", qos=2) 

    logger.info(f'Listening for messages from {TOPICS_S+"/#"}')



def on_disconnect(client, user_data, disconnection_result_code):
    """on_disconnect is called when our program disconnects from the MQTT Broker."""
    logger.error("Disconnected from MQTT Broker")



def on_message(client, userdata, msg):
    """Callback called when a message is received on a subscribed topic."""
    logger.debug("Received message for topic {}: {}".format( msg.topic, msg.payload))

    data = None
    print(f"\n\n")
    print("TOPIC: ", msg.topic)

    analyze_message(msg)
    




######################## MQTT Publishing ######################
#https://www.thethingsindustries.com/docs/integrations/mqtt/

def publish(client, topic, data, qos=0, retain=False): # TO DO: topic -> id of device
    
    data_64 = base64.b64encode(data.encode()).decode('ascii')

    payload = '''{
        "downlinks": [{
            "f_port": 1,
            "frm_payload": "''' + data_64 + '''",
            "priority": "NORMAL"
        }]
        }'''
    client.publish(topic, payload, qos, retain)


    
######################## MQTT initialization ######################

def init_mqtt():
    """ 
    Initialize MQTT connection to broker and run loop handling messages.
    Returns: MQTT Client object
    """

    BROKER_HOST = json_handler.configuration_read('BROKER_HOST')
    BROKER_PORT = json_handler.configuration_read('BROKER_PORT')
    CLIENT_ID = json_handler.configuration_read('CLIENT_ID')

    client = mqtt.Client(
        client_id=CLIENT_ID,
        clean_session=False)

    client.username_pw_set(
        username=json_handler.keys_read("USERNAME"),
        password=json_handler.keys_read("PASSWORD"))

    # Route Paho logging to Python logging.
    client.enable_logger()

    # Setup callbacks
    client.on_connect = on_connect
    client.on_disconnect = on_disconnect
    client.on_message = on_message

    # Connect to Broker.
    client.connect(BROKER_HOST, BROKER_PORT)

    # run client in loop - The loop_start() starts a new thread, that calls the loop method at regular intervals for you. It also handles re-connects automatically.
    client.loop_start()

    return client


######################## Example ######################

if __name__ == "__main__":
    client = init_mqtt()
    from signal_handler import signal_handler
    from functools import partial
    
    signal.signal(signal.SIGINT, partial(signal_handler, client, logger))  # Capture Control + C
    
    while(1):
        pass
