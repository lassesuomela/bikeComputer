# Readme

This is bike computer made with C++ and Qt5. It displays GPS data from Arduino Nano that has a GPS module attached to it. Data that is shown are speed, latitude, longitude, altitude and number of satellites. Also heading is displayed with red arrow that rotates accordingly. 

Satellite icon will blink if the GPS isn't locked.

On the right corner there will be a small circle that represents the HDOP(horizontal dilution of precision) value that comes from the GPS module. 
This is supposed to indicate the accuracy of the GPS lock with colors green(=GOOD), yellow(=OK) and red(=BAD).

---
## Screenshots below

Main window

!["Main"](/images/main.png)

Working demo

!["Demo"](/images/demo.png)

Arduino Nano + GPS module

!["Arduino"](/images/arduino_gps.png)
