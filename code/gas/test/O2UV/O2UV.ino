#include <Time.h>

/* 
  O2 UV Sensor (Co2meter.com) 
   
  Arduino Mega2560 --- O2 UV Sensor 
   GND ‐‐‐‐‐‐black‐‐‐‐‐‐‐‐ 1 (gnd) 
   5v ‐‐‐‐‐‐‐-red--‐‐‐‐‐‐‐ 3 (Vcc)  prin
   Tx1 ‐‐‐‐‐‐orange‐‐‐‐‐‐‐ 5 (Rx) 
   Rx1 ‐‐‐‐‐‐yellow‐‐‐‐‐‐‐ 7 (Tx) 
 
 */ 

// SENSOR VALUES
String val= "";  //holds the string of the value 
double o2 =0;  // holds the actual value 

int ledPin=13; //use as error indicator
// TODO: instead of delay, read buffer, discard errors
// and catch values!
// [19:58:14] Dougie Murray: Oh little tip with the O2 sensor, put a
//delay of 50 ms before you clear the read buffer and request the data,
//then a 1000 ms delay in after the request data
//[19:58:30] Dougie Murray: was skipping every 10 datapoints before I did this
//[19:59:47] Dougie Murray: clear read buffer -> wait(50) -> request -> wait(1000) -> read buffer -> send to supervisor

int dly=750; // delay between write and read operations
 
uint8_t buffer[100]; 
uint8_t ind =0; 

// TIMING
time_t t;

void setup() { 

  Serial.begin(9600);  //Start Serial connection with host 
  Serial.println("# Co2Meter.com O2 UV FLUX");    

  // setup O2 probe
  setupO2();  

  Serial.print("# TIME: ");
  t = now(); 
  printTime(t);
  Serial.println(); 

  Serial.println("# START"); 
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
  Serial.print(t);
  //Serial.print(day(t));
  //printDigits(hour(t));
  //printDigits(minute(t));
  //printDigits(second(t));
}


void setupO2() {
  // setup probe, make sure it's in required
  // mode, either streaming or polling
  Serial1.begin(9600); //Start Serial connection with Sensor 
  
  // first set sensor to polling mode and get some basic info
  Serial.print("# O2 PROBE POLLING MODE:");
  Serial1.write("M 1\r\n"); // set sensor to polling mode
  delay(dly);
  val = Serial1.readStringUntil('\n');
  Serial.println(val);
  
  // request probe information status
  Serial.print("# O2 PROBE SOFTWARE:");
  Serial1.write("# 2\r\n"); 
  delay(dly);
  val = Serial1.readStringUntil('\n');
  Serial.println(val);
  
  // request probe information status
  Serial.print("# O2 PROBE S/N:");
  Serial1.write("# 1\r\n"); 
  delay(dly);
  val = Serial1.readStringUntil('\n');
  Serial.println(val);
  
  // request error status
  Serial.print("# O2 PROBE ERROR STATUS:");
  Serial1.write("e\r\n"); 
  delay(dly);
  val = Serial1.readStringUntil('\n');
  Serial.println(val);
  
  // set sensor to streaming mode 
  Serial.print("# O2 PROBE STREAMING MODE:"); 
  Serial1.write("M 0\r\n"); 
  delay(dly); 
  val = Serial1.readStringUntil('\n');
  Serial.println(val);
}
 
void loop() { 
  // TODO: this relies on streaming mode,
  // however CO2 and O2 probes use different intervals
  // better to set polling mode and ask each probe separately?
  
  // just read strings until new-line
  // TODO: catch errors or check error status?
  val = Serial1.readStringUntil('\n');
  t = now(); // get time - TODO: just use "millis" instead?
  
  // print out data
  Serial.print(millis());
  Serial.print(" ");
  printTime(t);
  Serial.print(" ");
  Serial.print(val);
  Serial.println("|");
} 


void report() { 
   
  //Cycle through the buffer and send out each byte including the 
  // final line feed
  // TODO: instead parse all requested values into a results
  // array/structure
   
  Serial.print( "O2 = "); 
  for ( int i=0; i<100; i++ ) {
    // printing the bytes as they come in
    // TODO: translate and catch O2,T,P values!
    Serial.print(buffer[i],HEX);
    Serial.print(".");    
  } 
  Serial.println(" %"); 
  ind=0; //Reset the buffer index to overwrite the previous packet 
  val=""; //Reset the value string 
} 


