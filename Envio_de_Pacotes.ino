#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiUdp.h>
#include <PubSubClient.h>

const char* ssid = "Iniesta";
const char* senha = "ozzy01042019rir";

const char* servidoMQTT = "192.168.15.10";
const int portaMQTT = 1884;

const char* servidorHTTP = "http://192.168.15.10:5001/latencia";

const char* servidorUDP = "192.168.15.10";
const int portaUDP = 4210;

const size_t pacote = 800 * 1024;

WiFiClient espClient;
PubSubClient mqttClient(espClient);
WiFiUDP udp;

void geraDados(uint8_t* buffer, size_t len) {
  for (size_t i = 0; i < len; i++) {
    buffer[i] = i % 256;
  }
}

void MQTT() {
  Serial.print("\n");

  mqttClient.setServer(servidoMQTT, portaMQTT);

  if (mqttClient.connect("ESP32CAM")) {
    Serial.print("ESP Conectado!");
  }

  const size_t size = 1000;

  uint8_t* data = (uint8_t*)malloc(pacote);
  geraDados(data, pacote);

  for (int i = 0; i < 30; i++) {
    unsigned long start = millis();
    for (size_t offset = 0; offset < pacote; offset += size) {
      size_t sendSize = min(size, pacote - offset);
      mqttClient.publish("esp32cam/mqtt", &data[offset], sendSize);
      delay(10);
    }
    unsigned long end = millis();
    Serial.printf("[MQTT] Pacote %d enviado em %lu ms\n", i + 1, end - start);
    delay(500);
  }
  free(data);
}

void HTTP() {
  Serial.print("\n");

  uint8_t* data = (uint8_t*)malloc(pacote);
  geraDados(data, pacote);

  for (int i = 0; i < 30; i++) {

    HTTPClient http;
    http.begin(espClient, servidorHTTP);

    http.addHeader("Content-Type", "application/octet-stream");

    unsigned long start = millis();
    int respostaHTTP = http.POST(data, pacote);
    unsigned long end = millis();

    Serial.printf("[HTTP] Pacote %d enviado em %lu ms (HTTP Code: %d)\n", i + 1, end - start, respostaHTTP);
    
    http.end();

    delay(500);
  }

  free(data);
}

void UDP() {
  Serial.print("\n");

  const size_t size = 1460;

  uint8_t* data = (uint8_t*)malloc(pacote);
  geraDados(data, pacote);

  for (int i = 0; i < 30; i++) {
    unsigned long inicio = millis();

    for (size_t offset = 0; offset < pacote; offset += size) {
      size_t sendSize = min(size, pacote - offset);
      udp.beginPacket(servidorUDP, portaUDP);
      udp.write(&data[offset], sendSize);
      delay(2);
    }

    udp.endPacket();
    unsigned long fim = millis();

    Serial.printf("[UDP] Pacote %d enviado em %lu ms\n", i + 1, fim - inicio);
    
    delay(500);
  }

  free(data);
}

void iniciarMultiplosTestes(int *count) {

  delay(2000);
  MQTT();
  delay(5000);
  HTTP();
  delay(5000);
  UDP();

}

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, senha);
  Serial.print("Conectando ao Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(" Conectado!");

  udp.begin(portaUDP);

  delay(1000);
  MQTT();
  delay(1000);
  HTTP();
  delay(1000);
  UDP();

  Serial.print("Envio de pacotes finalizado");
}

void loop() {
  // int count = 1;
  // Serial.print("Iniciando teste ");
  // Serial.println(count);
  // // iniciarTestes(&count);
  // Serial.print("Teste ");
  // Serial.println(count);
  // Serial.print(" finalizado!");
  // count++;
}
