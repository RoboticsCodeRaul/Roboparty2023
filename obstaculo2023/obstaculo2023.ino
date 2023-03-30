/* 
 This example was created by José Cruz (www.botnroll.com)
 on the 29th January 2014
 
 This code example is in the public domain. 
 http://www.botnroll.com
ç
Description: 
Read obstacle sensors and move the robot avoiding obstacles.
*/

#include <BnrOneA.h>   // Bot'n Roll ONE A library
#include <EEPROM.h>    // EEPROM reading and writing
#include <SPI.h>       // SPI communication library required by BnrOne.cpp
BnrOneA one;           // declaration of object variable to control the Bot'n Roll ONE A

//constants definition
#define SSPIN  2      // Slave Select (SS) pin for SPI communication

// Velocidade
#define speed 73

void setup() 
{ 
    //setup routines -> runs only once when program starts
    delay(1500);       // wait 1,5 second to stabilize sensors
    Serial.begin(57600);     // set baud rate to 57600bps for printing values at serial monitor. Press (ctrl+shift+m) after uploading    
    one.spiConnect(SSPIN);   // start the SPI communication module
    one.stop();              // stop motors
    one.obstacleEmitters(ON);// activate obstacles detection
    one.lcd1("Modo: Obstaculos");
    //one.lcd2("");
    while(one.readButton()==0)
       delay(50);
}

void loop()
{
    byte obstacles=one.obstacleSensors(); //Read obstacle sensors
    switch(obstacles)
    {
        case 0:   // no obstacles detected
            one.lcd2("Dir: ^");
            one.move(speed,speed);     // Move Forward
            
            break;
        case 1:   // obstacle detected on Left sensor
            one.lcd2("Dir: <");
            while(obstacles == 1)
            {
              obstacles=one.obstacleSensors();
                one.move(10,(10 * -1));
            }
                       
//            for(int i = 0; i < (speed - 1); i++) {
//              one.move(i,(i * -1));
//              delay(1);
//            }
//            one.move(speed,(speed * -1));    // Rotate Right

            break;          
        case 2:   // obstacle detected on Right sensor
            one.lcd2("Dir: >");
            while(obstacles == 2)
            {
              obstacles=one.obstacleSensors();
                one.move((10 * -1),10);
            }
            
//            for(int i = 0; i < (speed - 1); i++) {
//              one.move((i * -1), i);
//              delay(1);
//            }
//            one.move((speed * -1),speed);    // Rotate Left

            break;
        case 3:   // obstacle detected on both sensors
            one.lcd2("Dir: ~");
            one.move(speed,(speed * -1));    // Rotate Left 
            delay(250);  
            obstacles=one.obstacleSensors();
            if (obstacles == 3) {
              one.move((speed * -1), speed);
              delay(500);
              obstacles=one.obstacleSensors();  
              if (obstacles == 3)  {
                one.move(speed, (speed * -1));
                delay(250);
              }
            }    
            break;
    }
    //delay(50);
}