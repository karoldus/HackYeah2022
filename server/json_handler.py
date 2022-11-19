import json

def configuration_save(key, value):
    """ 
    Save key:value pair to configuration.json file
    Parameters: key, value
    """
    with open("configuration.json", "r") as read_file:
        data = json.load(read_file)
    with open("configuration.json", "w") as write_file:
        data[key] = value
        json.dump(data, write_file)
    
def configuration_read(key):
    """ 
    Read value for key from configuration.json file
    Parameters: key
    Return: key's value
    """
    with open("configuration.json", "r") as read_file:
        data = json.load(read_file)
        return data[key]

def keys_read(key):
    """ 
    Read value for key from keys.json file
    Parameters: key
    Return: key's value
    """
    with open("keys.json", "r") as read_file:
        data = json.load(read_file)
        return data[key]

# def devices_read():

#     with open("devices.json", "r") as read_file:
#         data = json.load(read_file)
#         return data["dev_list"]


def measurements_add(device_id, value):

    with open("measurements.json", "r") as read_file:
        data = json.load(read_file)
    with open("measurements.json", "w") as write_file:
        data["devices"][str(device_id)]["history"].append(value)
        json.dump(data, write_file)

def measurements_read():

    with open("measurements.json", "r") as read_file:
        data = json.load(read_file)
        return data["devices"]