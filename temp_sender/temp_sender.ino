#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

RF24 radio(7, 8);
const uint64_t pipe = 0xE8E8F0F0E1LL;
//byte pipe [6] = "2Node";


int RedLed = 3;
int GreenLed = 4;

void setup(void) {
  Serial.begin(115200);
  sensors.begin();
  radio.begin();
  //radio.openWritingPipe(pipe);

  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  radio.setPALevel(RF24_PA_MAX);

 
    //radio.openWritingPipe(addresses[1]);
    radio.openWritingPipe(pipe);

    pinMode(RedLed, OUTPUT);
    pinMode(GreenLed, OUTPUT);
}

void loop(void)
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  Serial.print(" Requesting temperatures...");
  sensors.requestTemperatures();  // Send the command to get temperatures
  Serial.print("DONE  ");
  
  float temperature = sensors.getTempCByIndex(0); // Why "byIndex"? 
                                                  // You can have more than one IC on the same bus. 
                                                  // 0 refers to the first IC on the wire
  Serial.print("Temperature is: ");
  Serial.println(temperature);

  radio.stopListening();                         // First, stop listening so we can talk.
    
  //Serial.println(F("Now sending"));
  //if (!radio.write()){
  //  Serial.println(F("failed"));
  //}
  
  Serial.println(F("Now sending"));
                            
   if (radio.write( &temperature, sizeof(float) ))
   {
     Serial.println(F("Temp Send"));
     digitalWrite(GreenLed, HIGH);
     delay(200);
     digitalWrite(GreenLed, LOW);
     
   }
   else
   {
     Serial.println(F("failed"));
     digitalWrite(RedLed, HIGH);
     delay(200);
     digitalWrite(RedLed, LOW);
     
   }
  delay(10000);
}
