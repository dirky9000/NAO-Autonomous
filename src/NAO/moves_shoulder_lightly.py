import os
import sys
import time
sys.path.append('C:/Users/dirky/AppData/Local/Programs/Python/Python27/Python_SDK/lib')
import naoqi
from naoqi import ALProxy

NAO_IP = "192.168.1.126"  # Replace here with your NaoQi's IP address.
PORT = 9559

names = list()
times = list()
keys = list()

names.append("RShoulderRoll")
times.append([0.36])
keys.append([[0.280203, [3, -0.133333, 0], [3, 0, 0]]])

try:
  motion = ALProxy("ALMotion", NAO_IP, PORT)
  motion.angleInterpolationBezier(names, times, keys)
except BaseException as err:
  print(err)

