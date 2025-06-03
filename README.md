# TesteLatencia

Este repositório contém um teste para verificar a latência de envio de dados fictícios via protocolos MQTT, HTTP e UDP para análise de eficiência.
O intuito deste teste é verificar a melhor solução para o envio de grandes quantidades de dados (no caso estou simulando o envia de 30 frames ou 1 segundo de gravação de vídeo em 2MP com tamanho de 88KB por frame) para o uso de transmissão de dados para um servidor que fará o processsamento de imagem para detecção de objetos.

## Referência utilizadas para criar o código:

### ESP32:

__HTTP no ESP32__: https://www.youtube.com/watch?v=LiQaPJ9UrSM

__MQTT no ESP32__: https://www.emqx.com/en/blog/esp32-connects-to-the-free-public-mqtt-broker

__UDP no ESP32__: https://gist.github.com/santolucito/4016405f54850f7a216e9e453fe81803

### Servidor Local:

__Servidor HTTP__: https://www.digitalocean.com/community/tutorials/how-to-make-a-web-application-using-flask-in-python-3

__Servidor MQTT__: https://www.emqx.com/en/blog/how-to-use-mqtt-in-python

__Servidor UDP__: https://wiki.python.org/moin/UdpCommunication

## Documentação das bibliotecas utilizadas:

__Flask__: https://flask.palletsprojects.com/en/stable/

__Paho MQTT__: https://pypi.org/project/paho-mqtt/

__Sockets__: https://docs.python.org/3/library/socket.html
