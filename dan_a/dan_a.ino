
#include <BnrOneA.h>   // Bot'n Roll ONE A library
#include <EEPROM.h>    // EEPROM reading and writing
#include <SPI.h>       // SPI communication library required by BnrOne.cpp
BnrOneA one;           // declaration of object variable to control the Bot'n Roll ONE A

//constants definition
#define SSPIN  2       // Slave Select (SS) pin for SPI communication

void setup()
{
  Serial.begin(57600);     // set baud rate to 57600bps for printing values at serial monitor.
  one.spiConnect(SSPIN);   // start SPI communication module
  one.stop();              // stop motors
  for (int i = 0; i < 3; i++) {
    for (int i = 0; i < 5; i++) {
      for (int i = 0; i < 4; i++) {
        one.move(-15, 80);
        delay(250);
       one.stop();
       delay(300);
       one.move(80, -15);
       delay(250);
       one.stop();
       delay(320);
      }
      one.move(-80, 80);
      delay(300);
    }
    for (int i = 0; i < 8; i++) {
     one.move(-25, 80);
     delay(100);
     one.stop();
     delay(150);
     one.move(80, -25);
     delay(100);
     one.stop();
     delay(150);
    }
  }
}
void loop()
{
}
