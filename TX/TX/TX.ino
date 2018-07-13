
// CODE Completely designed BY : Hamed Rahimi

#include "DHT.h"
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN  7
#define CSN_PIN 8

#define DHTPIN 6     // what pin we're connected to Dht11
#define DHTTYPE DHT11   // DHT 11  (AM2302)


const uint64_t pipe = 0xE8E8F0F0E1LL;
unsigned int joystick[1];

int PTA ; // PC TO Arduino
int t ; // Tempreture

RF24 radio(CE_PIN, CSN_PIN); // Create a Radio

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  radio.begin();
  radio.openWritingPipe(pipe);
  delay(1000);

}

void loop() {
  if (Serial.available())
  {
    PTA = Serial.read();
    if (PTA == 100) {
      delay(100);
      t = dht.readHumidity();
      int data = Encoding(Quantization(t)).toInt() ;
      Serial.write(data);

    }
    else
    {
      joystick[0] = PTA ;
      radio.write( joystick, sizeof(joystick) );
      delay(1000);
    }
  }
}
// Encoding function
String Encoding(int temp)
{
  int myNum = temp ;
  int zeros = 6 - String(myNum, BIN).length();
  String myStr;
  for (int i = 0; i < zeros; i++)
  {
    myStr = myStr + "0" ;
  }
  myStr = myStr + String(myNum, BIN);
  return (myStr);
}
// quantization function
int Quantization (int in)
{
  int out;
   int a[100]; // quantization levels
for (int i=1;i<100;i++)  
{
   
  if ( a[i] <= in <=  a[i+1] )
{
 out = a[i];
  break;
}
}
return out;
}

