# Code for A Modular PhotoBioreactor

Independent modules for control and measurement of gas, liquid,
light and heat flux through a bioreactor; additional modules
for automated sampling.

The modules should work as independent devices and are each controlled
via an Arduino Mega2560 with Touchscreen and SD Card.

The goal is to combine them into diverse bioreactor setups with
a control software that synchronizes and collects data from each
module via defined get/set interfaces.

## TODO 

* move common functions, e.g., for the Arduino Mega+Touchscreen,
into a separate Arduino library.



