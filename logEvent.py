import time
import datetime

def log_event(protocol, packet_id=None):
    timestamp = time.time()
    with open(f"logs/{protocol}_log.txt", "a") as f:
        if(packet_id is not None):
            f.write(f"{packet_id},{timestamp}\n")
        else:
            f.write(f"{timestamp}\n")
    print(f"[{protocol.upper()}] Pacote {packet_id if packet_id else ''} recebido às {timestamp:.6f}")