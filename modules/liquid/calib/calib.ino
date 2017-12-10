
#include "HX711.h" // scale
HX711 scale(A9, A8); // scale on analog pins A8 (SCK) and A9 (DT/DOUT)

void setup() {
  Serial.begin(9600);// Start Serial connection with host 

  Serial.print("Calibrating scale: ");
  scale.set_scale();
  //scale.set_scale(-40250/3);
  //scale.set_scale(22186/3);
  scale.tare();
  Serial.print("units? ");
  Serial.println(scale.get_units(10));
  Serial.print("weight? ");
  Serial.println(scale.get_value());

  Serial.println("ADD WEIGHT\n");
  scale.power_down();// put the ADC in sleep mode
  delay(5000);
  scale.power_up();

}
void loop() {

  Serial.print("units? ");
  Serial.println(scale.get_units(10));
  Serial.print("weight? ");
  Serial.println(scale.get_value());

  scale.power_down();			        // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
}
