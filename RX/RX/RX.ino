#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   7
#define CSN_PIN 8


const uint64_t pipe = 0xE8E8F0F0E1LL ; // Define the transmit pipe
int calibration;
int datain[1];
byte dataout[1];

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

void setup()
{
  Serial.begin(115200);
  radio.begin();
  radio.openReadingPipe(1, pipe);
  radio.startListening();
  delay(1000);
}


void loop()
{
  if ( radio.available() )
  {
    radio.read( datain, sizeof(datain) );
    Serial.write(datain[0]);
    delay(100);
  }
  if (Serial.available())
  { 
    int Realtemp =Serial.read() ;
    int temp = (bitRead(Realtemp, 0)*1)+(bitRead(Realtemp, 1)*2)+(bitRead(Realtemp, 2)*4)+(bitRead(Realtemp, 3)*8)+(bitRead(Realtemp, 4)*16)+(bitRead(Realtemp, 5)*32);
  }
}
