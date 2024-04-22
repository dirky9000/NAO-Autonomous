from gpiozero import DistanceSensor
from time import sleep

TRIG_PIN = 17
ECHO_PIN = 27

sensor = DistanceSensor(trigger=TRIG_PIN, echo=ECHO_PIN)
while True:
    print(f"Distance in CM: {sensor.distance * 100}")
    sleep(1)