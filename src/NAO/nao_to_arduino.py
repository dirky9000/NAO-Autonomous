# Python on NAO robot
import sys
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')
import serial
from naoqi import ALProxy

nao_ip = "192.168.1.135"
nao_port = 9559

tts = ALProxy("ALTextToSpeech", nao_ip, nao_port)

arduino = serial.Serial('COM4', 9600)

while True:
    data = arduino.readline().decode('utf-8').strip()
    if data == "Hello":
        tts.say("Hello")