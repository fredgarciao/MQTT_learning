/*******************************************************************************
* Vou ler os valores do sensor DHT e criar um JSON a partir destes valores.
*******************************************************************************/

// Inclui a biblioteca DHT que possui as funções dos sensores do tipo DHT
#include "DHT.h"
#include<ArduinoJson.h>
const int pino_dht = 9; // pino onde o sensor DHT está conectado
float temperatura; // variável para armazenar o valor de temperatura
float umidade; // variável para armazenar o valor de umidade
DHT dht(pino_dht, DHT11); // define o pino e o tipo de DHT

StaticJsonDocument<100> doc; // RAM alocada para criar este documento JSON.
const char* sensor = "dht sensor";



void setup() {
  // Inicia e configura a Serial
  Serial.begin(9600); // 9600bps

  dht.begin(); // inicializa o sensor DHT
  temperatura = dht.readTemperature(); // lê a temperatura em Celsius
  umidade = dht.readHumidity(); // lê a umidade

  doc["sensor"] = sensor;
  doc["temperatura"] = temperatura; // coloquei o valor da temperatura no documento json.
  doc["umidade"] = umidade;

}

void loop() {
  // Aguarda alguns segundos entre uma leitura e outra
  delay(2000); // 2 segundos (Datasheet)
  // A leitura da temperatura ou umidade pode levar 250ms
  // O atraso do sensor pode chegar a 2 segundos


  // Se ocorreu alguma falha durante a leitura
  if (isnan(umidade) || isnan(temperatura)) {
    Serial.println("Falha na leitura do Sensor DHT!");
  }
  else { // Se não
    serializeJson(doc,Serial);
    Serial.println();
    serializeJsonPretty(doc,Serial);
    Serial.println();
    
  }
}
