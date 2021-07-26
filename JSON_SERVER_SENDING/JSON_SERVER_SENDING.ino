/*******************************************************************************
* Vou ler os valores do sensor DHT e criar um JSON a partir destes valores.
* E vou enviar para o adafruit.
*******************************************************************************/

// Inclui a biblioteca DHT que possui as funções dos sensores do tipo DHT
#include "DHT.h"
#include "SoftwareSerial.h"
const int pino_dht = 12; // pino onde o sensor DHT está conectado
float temperatura; // variável para armazenar o valor de temperatura
float umidade; // variável para armazenar o valor de umidade
DHT dht(pino_dht, DHT11); // define o pino e o tipo de DHT
const float value = 22.587;

// JSON CONFIG
#include<ArduinoJson.h>
StaticJsonDocument<100> doc; // RAM alocada para criar este documento JSON.
const char* sensor = "dht sensor";

// MQTT ADAFRUIT
#include "config.h"
AdafruitIO_Feed *temp_humdt = io.feed("temp_humdt");
char buffer1[256];

void setup() {
  // Inicia e configura a Serial
  Serial.begin(115200); // 115200bps
  // Espera para abrir o serial monitor
  while(! Serial);
  dht.begin(); // inicializa o sensor DHT


  // adafruit config
  doc["value"] = value;
  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  // we are connected
  Serial.println();
  Serial.println(io.statusText());
}

void loop() {
  // Aguarda alguns segundos entre uma leitura e outra
  delay(2000); // 2 segundos (Datasheet)

  // A leitura da temperatura ou umidade pode levar 250ms
  // O atraso do sensor pode chegar a 2 segundos
  temperatura = dht.readTemperature(); // lê a temperatura em Celsius
  umidade = dht.readHumidity(); // lê a umidade
  // Adicionando os valores ao JSON
  doc["temperature"] = temperatura;
  doc["umidade"] = umidade;
  
  // Se ocorreu alguma falha durante a leitura
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha na leitura do Sensor DHT!");
  }
  else { // Se não
  serializeJson(doc,Serial);
  temp_humdt -> save(temperatura);
  temp_humdt -> save(umidade);
  }
}
