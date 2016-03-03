
// code to drive 12V nema17 stepper motor via arduino motor shield
// http://forum.arduino.cc/index.php?topic=89468.0

#include <Stepper.h>

const int stepsPerRevolution = 200;  // change this to fit the number of steps per revolution
                          // for your motor

// initialize the stepper library on the motor shield
Stepper myStepper(stepsPerRevolution, 12,13);     

// give the motor control pins names:
const int pwmA = 3;
const int pwmB = 11;
const int brakeA = 9;
const int brakeB = 8;
const int dirA = 12;
const int dirB = 13;

int x = 0;
void setup() {
  Serial.begin(9600);
  // set the PWM and brake pins so that the direction pins  
  // can be used to control the motor:
  pinMode(pwmA, OUTPUT);
  pinMode(pwmB, OUTPUT);
  pinMode(brakeA, OUTPUT);
  pinMode(brakeB, OUTPUT);
  digitalWrite(pwmA, HIGH);
  digitalWrite(pwmB, HIGH);
  digitalWrite(brakeA, LOW);
  digitalWrite(brakeB, LOW);
  
  // initialize the serial port:
  Serial.begin(9600);
  // set the motor speed (for multiple steps only):
  myStepper.setSpeed(1); // rpm??
}


void loop() {
  
  myStepper.step(1);
  //myStepper.step(-2);
  
}