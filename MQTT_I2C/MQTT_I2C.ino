/*
MASTER - I2C WITH ESP8266
*/


// edit the config.h tab and enter your Adafruit IO credentials
// and any additional configuration needed for WiFi, cellular,
// or ethernet clients.
#include "config.h"

#include "Wire.h"


/************************ MQTT ADAFRUIT *******************************/
// bool que vem da net
 bool testebool; 
AdafruitIO_Feed *flagbool = io.feed("flagbool");

/************************ I2C *******************************/
// endereco do modulo slave que pode ser um valor de 0 a 255
#define slaveAdress 0x08



void setup() {
  /************************ MQTT ADAFRUIT *******************************/
  
  // start the serial connection
  Serial.begin(115200);

  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // set up a message handler for the 'flagbool' feed.
  // the handleMessage function (defined below)
  // will be called whenever a message is
  // received from adafruit io.
  flagbool->onMessage(handleMessageF);
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());
  flagbool->get();

  /************************ I2C *******************************/
  Wire.begin(); // ingressa ao barramento I2C

}

void loop() {
/************************ MQTT ADAFRUIT *******************************/
  // io.run(); is required for all sketches.
  // it should always be present at the top of your loop
  // function. it keeps the client connected to
  // io.adafruit.com, and processes any incoming data.
  io.run();
  
  /************************ I2C *******************************/

      // apenas altera o estado do LED se o novo estado do botao e HIGH
    if (testebool == HIGH) {
    
      // incia a transmissao para o endereco 0x08 (slaveAdress)
      Wire.beginTransmission(slaveAdress);
      Wire.write(testebool); // envia um byte contendo o estado do LED
      Wire.endTransmission(); // encerra a transmissao
      Serial.println("Ligado");
      }
      else{
      Wire.beginTransmission(slaveAdress);
      Wire.write(testebool); // envia um byte contendo o estado do LED
      Wire.endTransmission(); // encerra a transmissao
      Serial.println("Desligado");
      }
    }
 

void handleMessageF(AdafruitIO_Data *data) {

  Serial.print("Flag recebida ");

  if(data->toPinLevel() == true){
    testebool = true;
  }
  else{
    testebool = false;
  }
}
