#include <Time.h> // convert times (day, hours, minutes, seconds)
#include <UTFT.h> // Display
#include <UTouch.h> // Touchscreen
#include <SPI.h> // dunno
#include <SD.h> // SD Memory Card

// GAS MEASUREMENT MODULE 
// Arduino Mega2560 + TFT Touch Screen + O2 and CO2 sensors from co2meter
// MEASURES O2 and CO2 CONCENTRATION IN GAS

// TODO: implement calibration routine for CO2 probe 
//       (see Manual-GSS-Sensors.pdf)
// TODO: O2 values require correction PV=nRT 
//       (see Manual-CM-0201-UV-Flux-Oxygen.pdf)
// TODO: file management - check if card is full?
// TODO: sensor error management required?
// TODO: add total gas volume flux measurement module (e.g. Aalborg sensor)

/* 
  SENSORS-ARDUINO PIN CONNECTIONS
  
  O2 Sensor (UV FLUX) 
   
  Arduino Mega2560 --- O2 UV Sensor 
   GND ‐‐‐‐‐‐black‐‐‐‐‐‐‐‐ 1 (gnd) 
   5v ‐‐‐‐‐‐‐-red--‐‐‐‐‐‐‐ 3 (Vcc)  
   Tx1 ‐‐‐‐‐‐orange‐‐‐‐‐‐‐ 5 (Rx) 
   Rx1 ‐‐‐‐‐‐yellow‐‐‐‐‐‐‐ 7 (Tx) 
 
  CO2 Sensor (COZIR, GSS106603)
 
  Arduino Mega2560 --- COZIR
   GND ‐‐‐‐‐‐black‐‐‐‐‐‐‐‐ 1 (gnd) 
   3.3v ‐‐‐‐‐-red--‐‐‐‐‐‐‐ 3 (Vcc)  
   Tx2 ‐‐‐‐‐‐orange‐‐‐‐‐‐‐ 5 (Rx) 
   Rx2 ‐‐‐‐‐‐yellow‐‐‐‐‐‐‐ 7 (Tx) 
*/ 

// SD CARD
Sd2Card card;

// CO2 and O2 SENSOR VALUES
String val= ""; //holds the strings retrieved from the sensor
double co2=0;   // co2 in ppm
double multiplier=10; // probe-specific multiplier for CO2 - TODO get in setup
double o2=0;    // oxygen in bar
double P=0;     // pressure in bar
double T =0;    // temperature in °C

// TIME
time_t t; // time in milliseconds

// delay - time for proper sensor management 
// NOTE: currently not used, all works fine without
int dly=0; // delay between write and read operations
   
// TOUCH SCREEN
// The touch-screen Code is based on the UTouch_ButtonTest !
// Copyright (C)2015 Rinky-Dink Electronics, Henning Karlsen. 
// web: http://www.RinkyDinkElectronics.com/

#define SD_CS_PIN 53 // DEFINE SD CARD PIN
File myFile;  // File on the SD Card
bool RECORD = false; // record data on SD Card?
String clrLne = "                        "; // to clear complete lines

// Initialize display
// ------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Mega/Due shield            : <display model>,38,39,40,41
UTFT    myGLCD(SSD1289,38,39,40,41);

// Initialize touchscreen
// ----------------------
// Set the pins to the correct ones for your development board
// -----------------------------------------------------------
// Standard Arduino Mega/Due shield            :  6, 5, 4, 3, 2
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

// printing values and time
void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon 
  // and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
void printTime(time_t t) {
  //Serial.print(t);
  Serial.print(day(t));
  printDigits(hour(t));
  printDigits(minute(t));
  printDigits(second(t));
}

// GETTING SENSOR DATA
// The co2meter sensors are used in polling mode:
// (1) values can be requested by sending a char (CMD), indicating the
// type of data requested, ended by "\r\n" 
// (2) then the incoming string is parsed, and numerical values retrieved
// TODO: catch errors here !?
double getValue(char CMD, HardwareSerial &sensor, double multiplier, 
		bool debug) { 

  String str="";  // the full string retrieved from the sensor
  String val="";  // str reduced to the actual value, but as string
  double flt=0.0; // the value as floating point number

  // sent command to sensor, e.g. "O\r\n"
  // this causes the sensors to answer with a string terminated by newline "\n"
  sensor.print(CMD);
  sensor.print("\r\n");

  // parse sensor stream until newline
  // e.g. sensor streams "O 0219\n" and the string str will hold "O 0219"
  str = sensor.readStringUntil('\n'); // str = "O 0219"
  if ( debug ) Serial.println(str);

  // parse string char by char, copy only the actual value 
  // into new string, i.e., ignore CMD and white space
  // e.g., str="O 0219" -> val="0219"
  for(int i=0; i < str.length()+1; i++) 
    if( (str[i] != CMD) && (str[i] != ' ') ) 
      val += str[i]; // C++ string concatenation
  if ( debug ) Serial.println(val);

  // convert to float, multiply and return the numerical value
  flt = multiplier * val.toFloat(); 
  if ( debug ) Serial.println(flt);
  return(flt);
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

void setupCO2() {

  String val= ""; // holds the string retrieved from the sensor
  double tmp=0.0; // holds the numerical value extracted from the string 

  Serial.println("Initializing CO2 Sensor!");

  //Start Serial connection with Sensor 
  Serial2.begin(9600); 
  
  // first set sensor to CONTROL MODE and retrieve/test configuration
  // NOTE: sensors are switched OFF during control mode
  //       and calibration does NOT work
  Serial2.write("K 0\r\n"); // K=1 is streaming mode, K=2 is polling mode
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.println(val);

  // TODO: get multiplier for ppm 
  Serial2.write(".\r\n"); 
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.println(val);
  Serial.print("MULTIPLIER: ");
  Serial.println(multiplier);
  // TODO: use this to retrieve the multiplier value from the sensor
  //       should work by now
  tmp =  getValue('.', Serial2, 1.0, true); 
  Serial.print("MULTIPLIER retrieved: ");
  Serial.println(tmp);
 
  // configuration information
  Serial2.write("*\r\n");
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.println(val);

  // set sensor to POLLING MODE
  Serial2.write("K 2\r\n"); 
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.print("VALUE: ");
  Serial.println(val);

  // CALIBRATE: set zero point calibration with air
  // TODO: TEMPORARY UNTIL PROPER CALIBRATION PROTOCOL EXISTS
  Serial2.write("G\r\n"); // G to calibrate to ambient air (440 ppm)
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.println(val);

  // testing data retrieval: compare string with parsed and multiplied value
  Serial2.write("Z\r\n"); // Z to retrieve filtered CO2 value in ppm
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.print("CO2 VALUE string: ");
  Serial.println(val);
  
  tmp =  getValue('Z', Serial2, multiplier, true); 
  Serial.print("CO2 VALUE parsed: ");
  Serial.println(tmp);

  Serial.println("... done");
} 


void setupO2() { 

  String val= ""; // holds the string retrieved from the sensor
  double tmp=0.0; // holds the numerical value extracted from the string 

  Serial.println("Initializing  O2 Sensor!");

  //Start Serial connection with Sensor 
  Serial1.begin(9600); 

  // set sensor to POLLING MODE 
  Serial1.write("M 1\r\n"); // M=0 is streaming mode
  val = Serial1.readStringUntil('\n');
  delay(dly);
  Serial.print("# O2 PROBE POLLING MODE: ");
  Serial.println(val);

  // RETRIEVE/TEST CONFIGURATION
  
  // request probe information status
  Serial1.write("# 2\r\n"); 
  val = Serial1.readStringUntil('\n');
  delay(dly);
  Serial.print("# O2 PROBE SOFTWARE: ");
  Serial.println(val);
  
  // request probe information 
  Serial1.write("# 1\r\n"); // S/N RATIO
  val = Serial1.readStringUntil('\n');
  delay(dly);
  Serial.print("# O2 PROBE S/N: ");
  Serial.println(val);
  
  // request error status
  Serial1.write("e\r\n"); // ERROR STATUS
  val = Serial1.readStringUntil('\n');
  delay(dly);
  Serial.print("# O2 PROBE ERROR STATUS: ");
  Serial.println(val);
  
  // request sensor values
  Serial1.write("T\r\n"); // T for temperature in °C
  val = Serial1.readStringUntil('\n');
  delay(dly);
  Serial.print("# T [C]: ");
  Serial.println(val);

  Serial1.write("P\r\n"); // P for total pressure in bar
  val = Serial1.readStringUntil('\n');
  delay(dly);
  Serial.print("# P [bar]: ");
  Serial.println(val);

  Serial1.write("O\r\n"); // O for O2 (partial) pressure in bar
  val = Serial1.readStringUntil('\n');
  delay(dly);
  Serial.print("# O2 [bar]: ");
  Serial.println(val);
  
  Serial1.write("%\r\n"); // O for O2 % 
  val = Serial1.readStringUntil('\n');
  delay(dly);
  Serial.print("# O2 %: ");
  Serial.println(val);
  
  // testing data retrieval: compare string with parsed value
  tmp =  getValue('O', Serial1, 1.0, true);  
  Serial.print("O2 VALUE parsed: ");
  Serial.println(tmp);

  Serial.println("... done");
} 



/***************************
** ARDUINO MAIN FUNCTIONS **
**    setup and loop      **
***************************/

// Arduino setup function: called upon reset/power-on
// and followed by loop()ing (below)
void setup() {
  
  // TODO: proper error handling

  Serial.begin(9600);  // Start Serial connection with host 
       
  // initializing the touch screen
  setupScreen(); 

  myGLCD.print("Initializing", CENTER, 32);
  myGLCD.print("SD Card", CENTER, 64);
  setupSDCard(); // NOTE: this also writes a header to the data file

  myGLCD.print("Initializing", CENTER, 32);
  myGLCD.print("CO2 Sensor", CENTER, 64);
  setupCO2(); // TODO: use setup for tests and error handling
  
  myGLCD.print("Initializing", CENTER, 32);
  myGLCD.print(" O2 Sensor", CENTER, 64);
  setupO2(); // TODO: use setup for tests and error handling

  // draw Record/Stop Buttons
  drawButtons();  
  // and clear text lines
  myGLCD.print(clrLne, LEFT, 16);
  myGLCD.print(clrLne, LEFT, 32);
  myGLCD.print(clrLne, LEFT, 48);
  myGLCD.print(clrLne, LEFT, 64);
  myGLCD.print(clrLne, LEFT, 80);
  myGLCD.print(clrLne, LEFT, 96);
}

// main Arduino looping function: this will run
// as long as the Arduino has power-supply
void loop() {

  // GET VALUES FROM THE SENSORS, PRINT TO SCREEN
  // AND OPTIONALLY (BUTTON) WRITE TO DATA.TXT ON SD CARD,
  // AND CHECK BUTTONS
  
  // get measurement time (init)
  t = millis(); //now(); // now() gives seconds

  // get CO2 sensor values (Serial2)
  co2 = getValue('Z', Serial2, multiplier, false); 

  // get O2 sensor values (Serial1)
  o2 = getValue('O', Serial1, 1.0, false);  
  T = getValue('T', Serial1, 1.0, false);  
  P = getValue('P', Serial1, 1.0, false);  

  // get average time
  // TODO: instead record actual times, e.g. directly in getValue?
  //       -> measure time passed
  t = (t+millis())/2; 

  // PRINT VALUES TO SCREEN
  myGLCD.print("Time [sec]:          ", LEFT, 16);
  myGLCD.printNumI(round(t/1000), RIGHT, 16);
  myGLCD.print("CO2 [ppm]:           ", LEFT, 32);    
  myGLCD.printNumI(co2, RIGHT, 32);
  myGLCD.print("O2 [bar]:            ", LEFT, 48);
  myGLCD.printNumF(o2, 1, RIGHT, 48);
  myGLCD.print("P [bar]:             ", LEFT, 64);
  myGLCD.printNumF(P, 0, RIGHT, 64);
  myGLCD.print("O2 [%]:              ", LEFT, 80);
  myGLCD.printNumF(100*o2/P, 2, RIGHT, 80);
  myGLCD.print("T [C]:               ", LEFT, 96);
  myGLCD.printNumF(T, 1, RIGHT, 96);
  
  // WRITE DATA TO FILE
  if ( RECORD ) {
    myFile = SD.open("data.txt", FILE_WRITE);
    if ( myFile ) {
      myFile.print(t);
      myFile.print(' ');
      myFile.print(co2);
      myFile.print(' ');
      myFile.print(o2);
      myFile.print(' ');
      myFile.print(P);
      myFile.print(' ');
      myFile.print(T);
      myFile.print('\n');
      myFile.close();
    } else {
      // if the file didn't open, print an error:
      Serial.println("error opening data.txt");
      myGLCD.setColor(255, 0, 0);// keep red font until "Stop" button is pressed
      myGLCD.print("ERROR WRITING FILE", CENTER, 192);
    }
  }
    
  // CHECK BUTTONS
  if ( myTouch.dataAvailable() ) {
    myTouch.read();
    x = myTouch.getX();
    y = myTouch.getY();
    if ( (y>=130) && (y<=180) ) { // Button row 
      if ( (x>=10) && (x<=150) ) { // Button: Record
	waitForButton(10, 130, 150, 180);
	RECORD = true;
	drawRecButtons(); // draw buttons in recording mode (red)
	myGLCD.setColor(255, 0, 0);
	myGLCD.print("RECORDING DATA", CENTER, 192);
	myGLCD.setBackColor(0, 0, 0);
	myGLCD.setColor(255, 255, 255);
      }
      if ( (x>=160) && (x<=300) ) { // Button: Stop
	waitForButton(160, 130, 300, 180);
	RECORD = false;
	myGLCD.setBackColor(0, 0, 0);
	myGLCD.setColor(255, 255, 255);
	myGLCD.print(clrLne, LEFT, 192); // clear error message line
	drawButtons(); // draw buttons in idle mode (white)
      } 
    }
  }
  // continue looping
  // TODO: should we time sensor response and functions
  //       and add appropriate delay()s ?
}


