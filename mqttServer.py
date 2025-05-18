import paho.mqtt.client as mqtt
from logEvent import log_event

def start_mqtt_server():

    def on_connect(client, userdata, flags, rc):
        if(rc == 0): # 0: Conexão aceita
            print("[MQTT] Connected with code: ", rc)
        else:
            print("Failed to connect.\nReturn code:", rc)
        client.subscribe("esp32cam/mqtt")

    mqtt_counter = {"count": 0}
    def on_message(client, userdata, msg):
        mqtt_counter["count"] += 1
        log_event("mqtt", mqtt_counter["count"])

    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message
    client.connect("127.0.0.1", 1883, 60)
    client.loop_forever()