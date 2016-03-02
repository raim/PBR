
# SCALE - SEN003KGK

1) Download Hx711.zip and import to Arduino libraries
(Sketch > Include Library > Add .ZIP Library ...)

wget http://www.elecrow.com/wiki/images/2/25/Hx711.zip

2) Connect elecrow SEN003KGK to Arduino Mega

see http://www.elecrow.com/wiki/index.php?title=Weight_Sensor_Scales_Kit-_20KG

| SCALE | cable | MEGA |
|-------|-------|------|
| GND   | brown | GND  |
| DT    | red   | A1   |
| SCK   | orange| A0   |
| VCC   | yellow| 5V   | 

3) upload code: scale/scale.ino
