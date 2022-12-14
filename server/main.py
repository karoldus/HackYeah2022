from fastapi import FastAPI
import json_handler

types_of_data = ["temperature", "humidity", "flame", "smoke", "moisture"]

app = FastAPI()


@app.get("/data_types")
def data_types():
    return {"data_types": types_of_data}


@app.get("/last_measurement/{param}")
def last_measurement(param):

    output_tab = []

    measurment_history = json_handler.measurements_read()
    
    if(param not in types_of_data):
        return ""

    for device_id in measurment_history:
        history_obj = measurment_history[device_id]["history"]
        output_tab.append({"id" : device_id, "lat" : measurment_history[device_id]["lat"],
        "long" : measurment_history[device_id]["long"], 
        "time" : history_obj[-1]["time"], "value" : history_obj[-1][param]})
    return {"devices" : output_tab}



@app.get("/{device_id}/measurement")
def last_measurement(device_id):

    output_tab = []

    measurment_history = json_handler.measurements_read()
    
    if device_id in measurment_history:
        return {"history" : measurment_history[device_id]["history"]}
    else:
        return {}
