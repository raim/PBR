
# GASOMETER

## Sainsmart Touchscreen SSD1289 

Download required libraries UTFT [1] and UTouch [2] 
and either unzip to your Arduino libraries folder
or import the .zip files

[1] http://www.rinkydinkelectronics.com/library.php?id=51
[2] http://www.rinkydinkelectronics.com/library.php?id=55

## COZIR - CO2 Sensor

see example code in folder CO2IR/ 

## UV FLUX - O2 Sensor

see example code in folder O2UV/

## AM2302 Temperature and Humidity Sensor

see example code in folder humid/

Download library and import .zip as Arduino library
wget http://www.elecrow.com/download/DHT-sensor-library-master.zip

Pin connections sensor to arduino

|AM2302|  MEGA |
|------|-------|
| 1    |  5V   |
| 2    |  PWM2 |
| 4    |  GND  |

NOTE: the test code says "connect a 10K resistor from pin 2 (data) to pin 1 
(power) of the sensor"

## Aalborg XFM Mass Flow Meter

TODO: uses RS485; buy TTL-to-RS485 Arduino module


