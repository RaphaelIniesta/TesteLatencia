import socket
from logEvent import log_event

def start_udp_server():
    udp_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    udp_socket.bind(("0.0.0.0", 4210))
    udp_counter = 0
    print("[UDP] Aguardando pacotes na porta 4210...")
    while True:
        data, addr = udp_socket.recvfrom(2048)
        udp_counter += 1
        log_event("udp", udp_counter)