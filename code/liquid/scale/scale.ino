
// TOUCHSCREEN
#include <Time.h> // convert times (day, hours, minutes, seconds)
#include <UTFT.h> // Display
#include <UTouch.h> // Touchscreen
#include <SPI.h> // dunno
#include <SD.h> // SD Memory Card

// HX711 SCALE
#include "hx711.h"
Hx711 scale(A9, A8); // scale on analog pins A8 (SCK) and A9 (DT/DOUT)

// 12V 5000 rpm DC MOTOR/PERISTALTIC PUMP
// PIN CONNECTIONS - channel A
const int pwmA = 3;   // motor speed via PWM pin 3
const int brakeA = 9; // motor brake  
const int dirA = 12;  // motor direction

void setup() {

  Serial.begin(9600);
  //Setup Channel A
  pinMode(dirA, OUTPUT);   //Initiates Motor Channel A pin
  pinMode(brakeA, OUTPUT); //Initiates Brake Channel A pin

 // get weight
  Serial.print(scale.getGram(), 1);
  Serial.println(" g");

  // run motor
  digitalWrite(dirA, HIGH);    //Establishes forward direction of Channel A
  digitalWrite(brakeA, LOW);   //Disengage the Brake for Channel A
  analogWrite(pwmA, 500);      //Spins the motor on Channel A at full speed
  delay(5000);
 // get weight
  Serial.print(scale.getGram(), 1);
  Serial.println(" g");
  analogWrite(pwmA, 150);      //Spins the motor on Channel A at full speed

}

void loop() {

  // get weight
  Serial.print(scale.getGram(), 1);
  Serial.println(" g");


  //delay(200);
}
