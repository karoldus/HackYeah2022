from fastapi import FastAPI

devices = [
    {"id" : 1, "lat" : 50.078179, "long" : 19.9486106},
    {"id" : 2, "lat" : 50.456787, "long" : 19.8888888}
]

last_measurment_history = [
    {"id" : 1, "time" : 1668879619, "temperature" : 30, "humidity" : 50},
    {"id" : 2, "time" : 1668879555, "temperature" : 20, "humidity" : 70}
]

app = FastAPI()


@app.get("/data_types")
def data_types():
    return {"data_types": ["temperature", "humidity"]}


@app.get("/last_measurement/{param}")
def last_measurement(param):

    output_tab = []
    
    if(param == "temperature"):
        for i in last_measurment_history:
            output_tab.append({"id" : i["id"], "time" : i["time"], "value" : i["temperature"]})
        return {"devices" : output_tab}

    elif param == "humidity":
        for i in last_measurment_history:
            output_tab.append({"id" : i["id"], "time" : i["time"], "value" : i["humidity"]})
        return {"devices" : output_tab}

    else:
        return {}
