/*
      RoboCore - Tutorial Comunicacao entre Arduinos: I2C - Parte 1
                                                            (Slave)
                                                       (03/05/2015)

  Escrito por Marcelo Farias.

  Exemplo de como comunicar Arduinos utilizando o protocolo I2C.

  Altera o estado do LED conectado a placa Slave quando o botao ligado
  a placa Master for pressionado.

  Na placa Master foi utilizado um botao conectado ao pino 4, com o
  resistor de pullup interno da placa acionado e realizou-se um debounce
  em software. Na placa Slave foi utilizado um LED conectado ao pino 7.

  Referencias:
  Exemplo Debounce - https://www.arduino.cc/en/Tutorial/Debounce
  Tutorial Master Writer - https://www.arduino.cc/en/Tutorial/MasterWriter
*/

#include "Wire.h"

#define ledPin 7 // numero do pino onde o LED esta conectado
  
  
// endereco do modulo slave que pode ser um valor de 0 a 255
#define myAdress 0x08

void setup() {
  // ingressa ao barramento I2C com o endereço definido no myAdress (0x08)
  Wire.begin(myAdress);

  //Registra um evento para ser chamado quando chegar algum dado via I2C
  Wire.onReceive(receiveEvent);
  Serial.begin(115200);

  pinMode(ledPin, OUTPUT);  // configura o pino do LED como saida
}

void loop() {
  // nada para ser exexutado
}

// funcao executada sempre que algum dado e recebido no barramento I2C
// vide "void setup()"
void receiveEvent(int howMany) {
  Serial.println("test");
  // verifica se existem dados para serem lidos no barramento I2C
  if (Wire.available()) {
    // le o byte recebido
    char received = Wire.read();
    Serial.println(received);
    // se o byte recebido for igual a 0, apaga o LED
    if (received == 0) {
      digitalWrite(ledPin, HIGH);

    }

    // se o byte recebido for igual a 1 acende o LED
    if (received == 1) {
      digitalWrite(ledPin, LOW);
    }
  }
}
