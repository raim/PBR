#Python app to run a Cozir Sensor
import serial
import time
ser = serial.Serial("/dev/ttyAMA0")
print "Serial Connected!"
ser.write("K 2\r\n")
ser.flushInput()
time.sleep(1)

while True:
    ser.write("Z\r\n")
    time.sleep(.01)
    resp = ser.read(10)
    resp = resp[:8]
    print ""
    print ""
    fltCo2 = float(resp[2:])
    print "Co2 = " + str(fltCo2)
    time.sleep(1)