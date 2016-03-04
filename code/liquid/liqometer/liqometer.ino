
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
const int pwmA = 10;  // motor speed via PWM pin 10 (re-routed from 3!)
const int brkA = 9;   // motor brake  
const int dirA = 12;  // motor direction

void setup() {

  Serial.begin(9600);

  // MOTOR - TODO: replace by code/sampler/stepper
  // setup Channel A
  pinMode(dirA, OUTPUT); //Initiates Motor Channel A pin
  pinMode(brkA, OUTPUT); //Initiates Brake Channel A pin


  // run motor
  digitalWrite(dirA, HIGH);  //Establishes forward direction of Channel A
  digitalWrite(brkA, LOW);   //Disengage the Brake for Channel A
  analogWrite(pwmA, 500);    //Spins the motor on Channel A at full speed
  delay(5000);
  analogWrite(pwmA, 100);      //Spins the motor on Channel A at full speed

  // SCALE - simply get weight
  // TODO: tare routine?
  Serial.print(scale.getGram(), 1);
  Serial.println(" g");

  // INITIATE TOUCH-SCREEN AND SD-CARD
  // TODO: replicate code from code/gas/gasometer
  // show weight and relative pump speed
  // +/- buttons for pump speed
  // calculate current rate from data on SD-CARD
  // display pump speed depending on available calibrations
  

}

void loop() {

  // get weight
  Serial.print(scale.getGram(), 1);
  Serial.println(" g");

  // change motor speed
  Serial.println("fast"); 
  analogWrite(pwmA, 500);      //Spins the motor on Channel A at full speed
  delay(2000);
  Serial.println("slow"); 
  analogWrite(pwmA, 50);      //Spins the motor on Channel A at full speed
  delay(2000);

}
