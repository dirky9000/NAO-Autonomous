# Python on NAO robot
import sys
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')
import serial
import time

# Open a serial connection to the Arduino
ser = serial.Serial('/dev/ttyACM0', 9600)  # replace '/dev/ttyACM0' with the port where your Arduino is connected
time.sleep(2)  # wait for the serial connection to initialize

# Send a command to the Arduino
ser.write(b'1')  # replace '1' with the command you want to send