
#include <SPI.h>
#include "RF24.h"

/****************** User Config ***************************/
/***      Set this radio as radio number 0 or 1         ***/
bool radioNumber = 0;

/* Hardware configuration: Set up nRF24L01 radio on SPI bus plus pins 7 & 8 */
RF24 radio(7,8);
/**********************************************************/


//byte pipe [6] = "2Node";
const uint64_t pipe = 0xE8E8F0F0E1LL;


void setup() {
  Serial.begin(115200);
  
  radio.begin();


    
    radio.openReadingPipe(1,pipe);
 
  
  // Start the radio listening for data
  radio.startListening();
}

void loop() 
{
  float temperature = 0 ;
  
  if( radio.available())
  {
      while (radio.available())                                // While there is data ready
      {
        radio.read( &temperature, sizeof(float) );             // Get the payload
      }
     
      Serial.print(F("Temperature received: "));
      Serial.println(temperature);  
  }
}


