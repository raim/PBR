#include <Time.h>

/* 
  COZIR CO2 Sensor  (Co2meter.com) 
  
  Arduino Mega2560 --- O2 UV Sensor 
   GND ‐‐‐‐‐‐black‐‐‐‐‐‐‐‐ 1 (gnd) 
   3.3v ‐‐‐‐‐-red--‐‐‐‐‐‐‐ 3 (Vcc)  
   Tx2 ‐‐‐‐‐‐orange‐‐‐‐‐‐‐ 5 (Rx) 
   Rx2 ‐‐‐‐‐‐yellow‐‐‐‐‐‐‐ 7 (Tx) 
 */ 
 
// SENSOR VALUES
String val= "";  //holds the string of the value 
double co2 =0;  // holds the actual value 
double multiplier = 10; // probe-specific multiplier - TODO get in setup


int ledPin=13; //use as error indicator
int dly=750; // delay between write and read operations
 
uint8_t buffer[25]; 
uint8_t ind =0; 

// TIMING
time_t t;


void setup() { 

  Serial.begin(9600);  //Start Serial connection with host 
  Serial.println("Co2Meter.com CO2 COZIR");    
  
  // setup CO2 probe
  setupCO2();  

  Serial.print("TIME: ");
  t = now();
  printTime(t);
  Serial.println(); 

  Serial.println("START"); 
  // final delay to let all settle
  delay(dly);
} 

void printDigits(int digits) {
  // utility function for digital clock display: prints preceding colon 
  // and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

void printTime(time_t t) {
  Serial.print(hour(t));
  printDigits(minute(t));
  printDigits(second(t));
}


void setupCO2() {

  //Start Serial connection with Sensor 
  Serial2.begin(9600); 
  
  // set sensor to control mode
  Serial2.write("K 0\r\n"); 
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.println(val);

  // TODO get multiplier for ppm 
  Serial2.write(".\r\n"); 
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.println(val);
  // multiplier = string2integer(val);
  
  // set sensor to streaming mode
  Serial2.write("K 1\r\n"); 
  delay(dly); 
  val = Serial2.readStringUntil('\n');
  Serial.println(val);
} 
void loop() {
 
  //streaming mode
  //So we read incoming bytes into a buffer until we get '0x0A' 
  // which is the ASCII value for new‐line 
  while(buffer[ind-1] != 0x0A ) { 
    if  (Serial2.available()) { 
      buffer[ind] = Serial2.read(); 
      ind++; 
    }
  }   
  // print out data
  
  t = now(); 
  printTime(t);
  Serial.print(" ");
  report();  //Once we get the '0x0A' we will report what is in the buffer 
  Serial.println("|");
} 
void report() { 
  // Cycle through the buffer and send out each byte including the 
  // final linefeed 
  // TODO: instead parse all requested values into a results
  // array/structure

  /* 
    each packet in the stream looks like "Z 00400 z 00360" 
    'Z' lets us know its a co2 reading. the first number is the filtered value 
    and the number after the 'z' is the raw value. 
    We are really only interested in the filtered value 
   
  */ 
   
  for(int i=0; i < ind+1; i++) { 
    if(buffer[i] == 'z') //once we hit the 'z' we can stop 
      break; 
       
    if((buffer[i] != 0x5A)&&(buffer[i] != 0x20)) { //ignore 'Z' and white space 
      val += buffer[i]-48;
      //because we break at 'z' the only bytes getting added are the numbers 
      // we subtract 48 to get to the actual numerical value 
      // example the character '9' has an ASCII value of 57. [57‐48=9]
    }  
  } 
   
  co2 = (multiplier * val.toInt());  //now we multiply the value by a factor specific ot the sensor. see the COZIR software guide 
 
  Serial.print("CO2 = "); 
  Serial.print(co2);
  Serial.print(" ppm"); 
    ind=0; //Reset the buffer index to overwrite the previous packet 
    val=""; //Reset the value string 
} 
 

