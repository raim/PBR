// Hx711.DOUT - pin #A1
// Hx711.SCK - pin #A0

#include "hx711.h"
Hx711 scale(A9, A8); // scale on analog pins A8 and A9

// 12V 5000 rpm DC motor/peristaltic pump
// PIN CONNECTIONS - channel A
const int pwmA = 3;   // motor speed via PWM pin 3
const int brakeA = 9; // motor brake  
const int dirA = 12;  // motor direction

void setup() {

  Serial.begin(9600);
  //Setup Channel A
  pinMode(dirA, OUTPUT);   //Initiates Motor Channel A pin
  pinMode(brakeA, OUTPUT); //Initiates Brake Channel A pin

}

void loop() {

  // get weight
  Serial.print(scale.getGram(), 1);
  Serial.println(" g");

  // run motor
  digitalWrite(dirA, HIGH);    //Establishes forward direction of Channel A
  digitalWrite(brakeA, LOW);   //Disengage the Brake for Channel A
  analogWrite(pwmA, 500);      //Spins the motor on Channel A at full speed

  //delay(200);
}
