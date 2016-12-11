#include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 9                             // Data wire is plugged into digital pin 3 on the Arduino
#define NumberOfDevices 2                          // Set maximum number of devices in order to dimension 
                                                   // Array holding all Device Address arrays.

OneWire oneWire(ONE_WIRE_BUS);                     // Setup a oneWire instance to communicate with any OneWire devices

DallasTemperature sensors(&oneWire);               // Pass our oneWire reference to Dallas Temperature. 

byte allAddress [NumberOfDevices][8];              // Device Addresses are 8-element byte arrays.
                                                   // we need one for each of our DS18B20 sensors.

byte totalDevices;                                 // Declare variable to store number of One Wire devices
                                                   // that are actually discovered.
void setup() {
  Serial.begin(9600);
  sensors.begin();
  totalDevices = discoverOneWireDevices();         // get addresses of our one wire devices into allAddress array 
  for (byte i=0; i < totalDevices; i++) 
    sensors.setResolution(allAddress[i], 10);      // and set the a to d conversion resolution of each.
}

void loop() {
  delay(4000);
  sensors.requestTemperatures();                // Initiate  temperature request to all devices
  for (byte i=0; i < totalDevices; i++) {
    Serial.print("Device ");
    Serial.print(i);
    Serial.print(": ");
    printTemperature(allAddress[i]);
    Serial.print("\n\r");
  }
  Serial.print("\n\r\n\r");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

byte discoverOneWireDevices() {
  byte j=0;                                        // search for one wire devices and
                                                   // copy to device address arrays.
  while ((j < NumberOfDevices) && (oneWire.search(allAddress[j]))) {        
    j++;
  }
  for (byte i=0; i < j; i++) {
    Serial.print("Device ");
    Serial.print(i);  
    Serial.print(": ");                          
    printAddress(allAddress[i]);                  // print address from each device address arry.
  }
  Serial.print("\r\n");
  return j                      ;                 // return total number of devices found.
}

void printAddress(DeviceAddress addr) {
  byte i;
  for( i=0; i < 8; i++) {                         // prefix the printout with 0x
      Serial.print("0x");
      if (addr[i] < 16) {
        Serial.print('0');                        // add a leading '0' if required.
      }
      Serial.print(addr[i], HEX);                 // print the actual value in HEX
      if (i < 7) {
        Serial.print(", ");
      }
    }
  Serial.print("\r\n");
}

void printTemperature(DeviceAddress addr) {
  float tempC = sensors.getTempC(addr);           // read the device at addr.
  if (tempC == -127.00) {
    Serial.print("Error getting temperature");
  } else {
    Serial.print(tempC);                          // and print its value.
    Serial.print(" C (");
    Serial.print(DallasTemperature::toFahrenheit(tempC));
    Serial.print(" F)");
  }
}
