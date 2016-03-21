# LIQOMETER

A module for continuous culture (chemostat) or turbidostat, based on
a peristaltic pump and a scale.


## Scale - SEN003KGK

1) Download hx711.zip and import to arduino libraries

wget http://www.elecrow.com/wiki/images/2/25/Hx711.zip
(sketch > include library > add .zip library ...)

Or use more recent libraries:
https://github.com/Bodmer/TFT_HX8357
https://github.com/Bodmer/TFT_HX8357/archive/master.zip
https://github.com/aguegu/ardulibs/tree/master/hx711

2) Connect SEN003KGK to Arduino Mega

see http://www.elecrow.com/wiki/index.php?title=Weight_Sensor_Scales_Kit-_20KG

| SCALE | cable | MEGA |
|-------|-------|------|
| GND   | white | GND  |
| DT    | red   | A9   |
| SCK   | orange| A8   |
| VCC   | green | 5V   | 
from right to left on scale

TODO: make proper connections to 5V and Gnd pins of the motor shield

## Peristaltic Pump

For testing purposes: connect 12V 5000 rpm DC motor/peristaltic pump to 
motor shield channel A. Later we want to use a Nema17 stepper motor with
a proper pump head, see code/sampler/stepper/ for code and ... for
a 3D-printed pump head.

TODO: use Nema17 12 V stepper motor (act-motor 17HS3404; as used
in ultimaker2) and 3D print peristaltic pump head; OR get alternative
peristaltic pump 

## Sainsmart Touchscreen SSD1289 

same as used for code/gas/gasometer

RE-WIRING:

Pin 3 of the Mega is used by both touchscreen and motor shields.
Thus we need to connect the free pin 10 via an external cable
to pin 3 of the motor shield, and use another cable to connect
the DOUT pin of the touchscreen shield to pin 3 of the Arduino.
To connect the touchscreen shield to the Arduino Mega Board use
two 2x13 or one 2x20 pin stacking headers for Raspberry Pi (Model B+)
with extra long pins! The 2x13 option requires to file off a bit
of the plastic where the two stacking headers touch. The Touchscreen-Mega
connection requires 2x18 pins, so the 2x20 option is the best and
least work-intensive.

TODO:  get SD card


## OUTDATED: LCD Screen HX8357B 

NOT USED FOR MODULE - no touchscreen!


