from os import makedirs, path
import sys
import time
import threading

# Importando funções para chamada dos protocolos
from mqttServer import start_mqtt_server
from httpServer import start_http_server
from updServer import start_udp_server


if(not path.exists("logs")):
    makedirs("logs", exist_ok=True)

if __name__ == "__main__":
    threading.Thread(target=start_mqtt_server, daemon=True).start()
    threading.Thread(target=start_http_server, daemon=True).start()
    threading.Thread(target=start_udp_server, daemon=True).start()
    
    try:
        while True:
            time.sleep(1)
    except KeyboardInterrupt:
        print("\nEncerrando")