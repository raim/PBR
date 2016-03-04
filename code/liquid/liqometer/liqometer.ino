
// LIQUID PUMPING MODULE
// pump rate can be measured by placing the source or target
// bottle on the scale and recording the weight loss/gain;
// data can be recorded on SD card, and by integrating over
// time, the pump speed can be calibrated to g/h or, with
// additional volume of a reactor as dilution rate 1/h.

#include <Time.h> // convert times (day, hours, minutes, seconds)


// HX711 SCALE
#include "hx711.h"
Hx711 scale(A9, A8); // scale on analog pins A8 (SCK) and A9 (DT/DOUT)

// 12V 5000 rpm DC MOTOR/PERISTALTIC PUMP
// PIN CONNECTIONS - channel A
const int pwmA = 10;  // motor speed via PWM pin 10 (re-routed from 3!)
const int brkA = 9;   // motor brake  
const int dirA = 12;  // motor direction


// TOUCHSCREEN
#include <UTFT.h> // Display
#include <UTouch.h> // Touchscreen
#include <SPI.h> // dunno
#include <SD.h> // SD Memory Card
#define SD_CS_PIN 53 // DEFINE SD CARD PIN
File myFile;  // File on the SD Card
bool RECORD = false; // record data on SD Card?
String clrLne = "                        "; // to clear complete lines

// Initialize display
UTFT    myGLCD(SSD1289,38,39,40,41);
// Initialize touchscreen
UTouch  myTouch( 6, 5, 4, 3, 2);
// Declare which fonts we will be using
extern uint8_t BigFont[];

int x, y; // position on touch screen

// record and stop button coordinates
// TODO: define here
int rec_x1, rec_x2, rec_y1, rec_y2;
int stp_x1, stp_x2, stp_y1, stp_y2;

/*************************
**  UTILITY FUNCTIONS   **
*************************/

// buttons in idle mode (not recording)
void drawButtons() {
  // Record and Stop Buttons
  // TODO: define x,y positions of buttons as variables
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect(10, 130, 150, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(10, 130, 150, 180);
  myGLCD.print("Record", 40, 147);

  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect(160, 130, 300, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect(160, 130, 300, 180);
  myGLCD.print("Stop", 190, 147);
  myGLCD.setBackColor (0, 0, 0);
}
// buttons in recording mode
void drawRecButtons() {
  // Record and Stop Buttons; as above but simply "Record" in red
  myGLCD.setBackColor(0, 0, 255);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (10, 130, 150, 180);
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (10, 130, 150, 180);
  myGLCD.print("Record", 40, 147);
  myGLCD.setColor(0, 0, 255);
  myGLCD.fillRoundRect (160, 130, 300, 180);
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (160, 130, 300, 180);
  myGLCD.print("Stop", 190, 147);
  myGLCD.setBackColor (0, 0, 0);
}
// Draw a red frame while a button is touched
void waitForButton(int x1, int y1, int x2, int y2) {
  myGLCD.setColor(255, 0, 0);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
  while (myTouch.dataAvailable())
    myTouch.read();
  myGLCD.setColor(255, 255, 255);
  myGLCD.drawRoundRect (x1, y1, x2, y2);
}

/*************************
**   SETUP FUNCTIONS    **
*************************/

// NOTE: setup functions are the ideal playground to test new
//       functionality; the could also be used for proper error handling.

void setupScreen() {

  Serial.println("Initializing Screen!");

  // Initial setup
  myGLCD.InitLCD();
  myGLCD.clrScr();

  myTouch.InitTouch();
  myTouch.setPrecision(PREC_MEDIUM);

  myGLCD.setFont(BigFont);
  myGLCD.setBackColor(0, 0, 0);
  
  Serial.println("... done");
}

void setupSDCard() {

  Serial.println("Initializing SD Card!");

  if ( !card.init(SPI_HALF_SPEED, SD_CS_PIN) ) {
    Serial.println("SD initialization failed. Things to check:");
    Serial.println("* is a card inserted?");
    myGLCD.setColor(255, 0, 0);
    myGLCD.print("ERROR: NO SD CARD", CENTER, 192);
    myGLCD.setColor(255, 255, 255);
    return;
  } 
  //pinMode(SD_CS_PIN, OUTPUT);
  // TODO: what does this test, when can it fail?
  if ( !SD.begin(SD_CS_PIN) ) {
    Serial.println("SD initialization failed!");
    return;
  }

  // test by writing to a test file
  myFile = SD.open("test.txt", FILE_WRITE);
  if ( myFile ) {
    // if the file opened okay, write to it:
    Serial.print("Writing HELLO WORLD to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close and remove the test file:
    myFile.close();
    SD.remove("test.txt");
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    myGLCD.setColor(255, 0, 0);
    myGLCD.print("ERROR WRITING FILE", CENTER, 192);
    myGLCD.setColor(255, 255, 255);
  }
    
  Serial.println("Initializing Data File - writing header!");
  // write new header to data file!
  // NOTE: we currently always write to the end of an existing data.txt
  // a new header thus indicates a new measurement session
  // TODO: we could (optionally) delete existing files 
  myFile = SD.open("data.txt", FILE_WRITE);
  if ( myFile ) {
    myFile.print("Time[ms]");
    myFile.print(' ');
    myFile.print("CO2[ppm]");
    myFile.print(' ');
    myFile.print("O2[bar]");
    myFile.print(' ');
    myFile.print("P[bar]");
    myFile.print(' ');
    myFile.print("T[C]");
    myFile.print('\n');
    myFile.close();
  }
  Serial.println("... done");
}


/***************************
** ARDUINO MAIN FUNCTIONS **
**    setup and loop      **
***************************/

// Arduino setup function: called upon reset/power-on
// and followed by loop()ing (below)
void setup() {

  Serial.begin(9600);// Start Serial connection with host 
       
  // TOUCH SCREEN
  // setupScreen(); 

  // MOTOR - TODO: replace by code/sampler/stepper
  // setup Channel A
  pinMode(dirA, OUTPUT); //Initiates Motor Channel A pin
  pinMode(brkA, OUTPUT); //Initiates Brake Channel A pin

  // test run motor
  digitalWrite(dirA, HIGH);  //Establishes forward direction of Channel A
  digitalWrite(brkA, LOW);   //Disengage the Brake for Channel A
  analogWrite(pwmA, 500);    //Spins the motor on Channel A at full speed
  delay(5000);
  analogWrite(pwmA, 100);      //Spins the motor on Channel A at full speed

  // SCALE - simply get weight
  // TODO: tare routine?
  Serial.print(scale.getGram(), 1);
  Serial.println(" g");

  // TODO: show weight and relative pump speed
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
