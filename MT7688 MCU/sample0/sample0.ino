#include <OneWire.h> 
#include <DallasTemperature.h>
#include <Bridge.h>

// Data wire is plugged into pin 10 on the Arduino 
const int PIN_ONE_WIRE = 10;
const int PIN_LIGHT_SENSOR = A0;

// Setup a oneWire instance to communicate with any OneWire devices  
// (not just Maxim/Dallas temperature ICs) 
OneWire oneWire(PIN_ONE_WIRE); 

// Pass our oneWire reference to Dallas Temperature. 
DallasTemperature sensors(&oneWire);

void setup(void) 
{
  Serial.begin(9600);
  sensors.begin();
  Bridge.begin();
}

void loop(void) 
{ 
  // call sensors.requestTemperatures() to issue a global temperature 
  // request to all devices on the bus 
  
  Serial.print("\nRequesting temperatures..."); 
  sensors.requestTemperatures(); // Send the command to get temperature readings 
  Serial.println("DONE"); 
  
  Serial.print("Temperature is: "); 
  float temperatureValue = sensors.getTempCByIndex(0); // Why "byIndex"?
  // You can have more than one DS18B20 on the same bus.  
  // 0 refers to the first IC on the wire 
  Serial.println(temperatureValue);

  int brightnessValue = analogRead(PIN_LIGHT_SENSOR);
  Serial.print("Light sensor value = ");
  Serial.println(brightnessValue);

  // MCU to MPU
  Bridge.put("Temperature", String(temperatureValue));
  Bridge.put("Brightness", String(brightnessValue));
  
  delay(1000); 
}
