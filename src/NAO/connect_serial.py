import sys
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')
import serial
import time
from naoqi import ALProxy

# Replace 'NAO_IP' and 'NAO_PORT' with the actual IP and port of your NAO robot
motion = ALProxy("ALMotion", "192.168.1.135", 9559)

ser = serial.Serial(port='COM7', baudrate=9600, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, bytesize=serial.EIGHTBITS, timeout=0)

def send_string(message):
    print(message)

def send_command(command):
    ser.write(command.encode())

try:
    ser.close()
except:
    pass

try:
    ser.open()
    send_string("Serial port is now open!")
    while True:
        command = input("Enter command (r/b): ")
        if command == 'r':
            send_string("Red")
            send_command("r")
        elif command == 'b':
            send_string("Blue")
            send_command("b")
        time.sleep(1)
except Exception as e:
    send_string("We found an exception!")
    print("Exception: " + str(e))
    ser.close()