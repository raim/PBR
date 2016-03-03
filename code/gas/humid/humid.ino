
// sample code for the AOSONG AM2302 Temperature & Humidity Sensor
// bought from elecrow; code from
// http://www.elecrow.com/download/DHT-sensor-library-master.zip

/* PIN CONNECTIONS: from left (top view) to right on the senor

   |AM2302|  MEGA |
   |------|-------|
   | 1    |  5V   |
   | 2    |  PWM2 |
   | 4    |  GND  |
   NOTE: Connect a 10K resistor from pin 2 (data) to pin 1 (power) of the sensor
 */

// Written by ladyada, public domain
#include "DHT.h"

#define DHTTYPE DHT22   // DHT 22  (AM2302) sensor type
#define DHTPIN 2        // the data pin the sensor is connected to

DHT dht(DHTPIN, DHTTYPE);

void setup() {

  Serial.begin(9600); 
  Serial.println("DHT22 test!");
 
  dht.begin();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();


  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h)) {
    Serial.println("Failed to read from DHT");
  } else {
    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C");
  }
}